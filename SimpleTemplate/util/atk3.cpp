#include "Atk3.h"
#include <WPILib.h>

Atk3::Atk3(int port){
	
	joystick_ = new Joystick( port );
		
	for( int i = 0; i < MAX_NUM_BUTTONS; i++ ){
			
		oldBtnStates[i] = false;
		newBtnStates[i] = false;

		upEventStates[i] = false;
		downEventStates[i] = false;
			
	}
	
}

double Atk3::GetAxis( int axis ){

	double output;
	
	if( axis == Atk3::X ){

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

void Atk3::Update(){

	for( int i = 1; i < MAX_NUM_BUTTONS + 1; i++ ){
            
        newBtnStates[i] = joystick_->GetRawButton(i);
            
        upEventStates[i] = !newBtnStates[i] && oldBtnStates[i];
            
        downEventStates[i] = newBtnStates[i] && !oldBtnStates[i];
        
        oldBtnStates[i] = newBtnStates[i];
            
    }
}

bool Atk3::GetButton( int button ){

	return newBtnStates[ button ];

}

bool Atk3::GetButtonDown( int button ){

	return downEventStates[ button ];

}

bool Atk3::GetButtonUp( int button ){

	return upEventStates[ button ];

}
