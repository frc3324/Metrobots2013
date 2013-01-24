#include "AtkJoystick.h"
#include "controller.h"

AtkJoystick::AtkJoystick (int port) :
	Controller::Controller(port) {
}

double AtkJoystick::GetAxis( int axis ){

	if( axis == AtkJoystick::X ){

            return joystick_->GetRawAxis( axis );

        }
        else{

            return -joystick_->GetRawAxis( axis );

        }  

}
