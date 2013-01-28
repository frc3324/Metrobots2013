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

	double output;
	
	if( axis == GamePad::LEFT_X || axis == GamePad::RIGHT_X ){

	    output = joystick_->GetRawAxis( axis );

    }
    else{

        output = -joystick_->GetRawAxis( axis );

    }
	
	if( ( output > 0.0 && output < 0.05 ) || ( output < 0.0 && output > -0.05 ) ){
		output = 0.0;
	}

	return output;
		
}

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





