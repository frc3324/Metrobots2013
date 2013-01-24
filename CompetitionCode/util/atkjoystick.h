#ifndef ATK_JOYSTICK_H
#define ATK_JOYSTICK_H

#include "controller.h"
#include "WPILib.h"

class AtkJoystick : public Controller{

	public:
		AtkJoystick( int port );
		double GetAxis( int Axis );
		
		static const int X = 1;
		static const int Y = 2;
		static const int THROTTLE = 3;

};

#endif
