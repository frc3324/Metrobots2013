#include "GamePad.h"
#include "WPILib.h"

GamePad::GamePad(int port) :
	Controller::Controller(port) {
}

double GamePad::GetAxis( int axis ){

	if( axis == GamePad::LEFT_X || axis == GamePad::RIGHT_X ){

	    return joystick_->GetRawAxis( axis );

    }
    else{

        return -joystick_->GetRawAxis( axis );

    }

}








