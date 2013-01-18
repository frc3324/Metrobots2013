import sys
sys.path.append('/users/sujit/libs/libfreenect/wrappers/python/')

import freenect
import cv2
import numpy as np

use_webcam = False
if use_webcam:
	c = cv2.VideoCapture(0)
	c.open(0)

huel = 0
hueh = 255
satl = 0
sath = 255
luml = 0
lumh = 255

def getimg_webcam():
	_, img = c.read()
	return img

def getimg_irkinect():
	raw_data, _ = freenect.sync_get_video(0, freenect.VIDEO_IR_8BIT)
	return np.array(raw_data)

def sobelmag(img):
	sobel_ksize = 7
	sobel_scale = 2 ** -(sobel_ksize * 2 - 1 - 1 - 2)
	blurred = cv2.GaussianBlur(img, (11, 11), 1)

	grad_x = cv2.Sobel(blurred, cv2.CV_16S, 1, 0, ksize=sobel_ksize, scale=sobel_scale)
	grad_y = cv2.Sobel(blurred, cv2.CV_16S, 0, 1, ksize=sobel_ksize, scale=sobel_scale)
	abs_grad_x = cv2.convertScaleAbs(grad_x)
	abs_grad_y = cv2.convertScaleAbs(grad_y)
	magnitude = cv2.addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0)

	return cv2.normalize(magnitude, alpha=2 ** 15)

def donothing(img):
	return img

def hsvthreshold(img):
	hsv = cv2.cvtColor(img, cv2.CV_RGB2HSV)
	planes = cv2.split(hsv)
	return img

def brightnessthreshold(img):
	_, ret = cv2.threshold(img, 200, 255, cv2.THRESH_TOZERO)
	return ret

def process(img):
	return brightnessthreshold(sobelmag(img))

def onchange(x):
	pass

def loop(processimg):
	ctx = freenect.init()
	dev = freenect.open_device(ctx, 0)
	freenect.set_tilt_degs(dev, 10)
	freenect.close_device(dev)
	while True:
		#img = processimg(np.array(getimg_webcam()))
		#gotimg, img = c.read()
		img = getimg_irkinect()
		#gotimg = True
		#if not gotimg:
		#	print 'stopped'
		#	break

		cv2.imshow('processing', processimg(img))
		if cv2.waitKey(10) == 27:
			break
	cv2.destroyAllWindows()

loop(process)
