#include "GamePad.h"
#include <WPILib.h>

GamePad::GamePad(int port){
	
	joystick_ = new Joystick( port );
		
	for( int i = 0; i < MAX_NUM_BUTTONS; i++ ){
			
		oldBtnStates[i] = false;
		newBtnStates[i] = false;

		upEventStates[i] = false;
		downEventStates[i] = false;
			
	}
	
}

double GamePad::GetAxis( int axis ){

	if( axis == GamePad::LEFT_X || axis == GamePad::RIGHT_X ){

	    return /*AxisDeadband( */joystick_->GetRawAxis( axis ) /*)*/;

    }
    else{

        return /*AxisDeadband(*/ -joystick_->GetRawAxis( axis ) /*)*/;

    }

}
/*double AxisDeadband( double input ){
	
	double output = input;

	output = ( output > 0 && output < GamePad::AXIS_DEADBAND ) ? 0.0 : output;
	output = ( output < 0 && output > -GamePad::AXIS_DEADBAND ) ? 0.0 : output;
	
	return output;
	
}*/

void GamePad::Update(){

	for( int i = 1; i < MAX_NUM_BUTTONS + 1; i++ ){
            
        newBtnStates[i] = joystick_->GetRawButton(i);
            
        upEventStates[i] = !newBtnStates[i] && oldBtnStates[i];
            
        downEventStates[i] = newBtnStates[i] && !oldBtnStates[i];
        
        oldBtnStates[i] = newBtnStates[i];

            
    }

}

bool GamePad::GetButton( int button ){

	return newBtnStates[ button ];

}

bool GamePad::GetButtonDown( int button ){

	return downEventStates[ button ];

}

bool GamePad::GetButtonUp( int button ){

	return upEventStates[ button ];

}






