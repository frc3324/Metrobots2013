#include "drive.h"
#include <Math.h>

Drive::Drive( SpeedController *flMotor_, SpeedController *blMotor_, SpeedController *frMotor_, SpeedController *brMotor_) {

	flMotor = flMotor_;
	blMotor = blMotor_;
	frMotor = frMotor_;
	brMotor = brMotor_;
	
	motorInverters[0] = 1;
	motorInverters[1] = 1;
	motorInverters[2] = 1;
	motorInverters[3] = 1;
	
	
	isSlowDrive = false;
	
	driverLeft = 0.0;
	driverRight = 0.0;
}

void Drive::Actuate(){
	
	float multiplier = (isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0);
	flMotor->Set(driverLeft * multiplier * motorInverters[0]);
	blMotor->Set(driverLeft * multiplier * motorInverters[1]);
	frMotor->Set(driverRight * multiplier * motorInverters[2]);
	brMotor->Set(driverRight * multiplier * motorInverters[3]);

}

void Drive::Disable(){

	flMotor->Set( 0.0 );
	blMotor->Set( 0.0 );
	frMotor->Set( 0.0 );
	brMotor->Set( 0.0 );

	driverLeft = 0.0;
	driverRight = 0.0;
}

void Drive::SetLeftRight( double left, double right ){
	
	driverLeft = left;
	driverRight = right;

}

void Drive::SetForwardTurn( double forward, double turn ){

	driverLeft = forward - turn;
	driverRight = forward + turn;

}


bool Drive::IsSlowDrive(){

	return isSlowDrive;

}

void Drive::SetSlowDrive( bool value ){

	isSlowDrive = value;

}

void Drive::SetInvertedMotors( bool fl, bool bl, bool fr, bool br ){

	motorInverters[0] = fl ? -1 : 1;
	motorInverters[1] = bl ? -1 : 1;
	motorInverters[2] = fr ? -1 : 1;
	motorInverters[3] = br ? -1 : 1;

}

void Drive::NormalizeMotorSpeeds(){
	
	/*double maxValue = 1.0;
	        
	if(fabs( flSpeed ) > maxValue ){
		maxValue = fabs( flSpeed );
	}
	if( fabs( blSpeed ) > maxValue ){
		maxValue = fabs( blSpeed );
	}
	if( fabs( frSpeed ) > maxValue ){
		maxValue = fabs( frSpeed );
	}
	if( fabs( brSpeed ) > maxValue ){
		maxValue = fabs( brSpeed );
	}
	
	flSpeed = flSpeed / maxValue;
	blSpeed = blSpeed / maxValue;
	frSpeed = frSpeed / maxValue;
	brSpeed = brSpeed / maxValue;
	*/
}
