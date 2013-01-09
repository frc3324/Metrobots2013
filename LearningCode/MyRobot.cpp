#include "WPILib.h"
#include <Dashboard.h>
#include <DriverStationLCD.h>
#include <nivision.h>  //For image code
#include "Timer.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <Vision/AxisCamera.h>
#include <Vision/RGBImage.h>
#include <math.h>
#include <string.h>
using namespace std;

DriverStationLCD *text;

class RobotDemo : public SimpleRobot
{
	
	Jaguar motor;
	Joystick stick;
	
public:
	RobotDemo(void):
		motor(4),
		stick(1)
	{
		text = DriverStationLCD::GetInstance();
	}
	
	void Autonomous(void)
	{
			
			
	}
	
	void OperatorControl(void)
	{
				
		while (IsOperatorControl() && ! IsDisabled())
		{
							
			motor.Set( stick.GetRawAxis( 1 ) );

			text->Clear();
			text->Printf( DriverStationLCD::kUser_Line1, 1, "%f", stick.GetRawAxis( 1 ) );
			text->UpdateLCD();
			
			Wait(0.005);
		
		}
	}
	
	void Disabled(void)
	{
	}
	
};

START_ROBOT_CLASS(RobotDemo);
