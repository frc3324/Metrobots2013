#include "drive.h"

Drive::Drive( Talon *flMotor_, Talon *blMotor_, Talon *frMotor_, Talon *brMotor_, 
				Encoder *flEncoder_, Encoder *blEncoder_, Encoder *frEncoder_, Encoder *brEncoder_, 
				Gyro *gyro_ ){

	flMotor = flMotor_;
	blMotor = blMotor_;
	frMotor = frMotor_;
	brMotor = brMotor_;
	
	flEncoder = flEncoder_;
	blEncoder = blEncoder_;
	frEncoder = frEncoder_;
	brEncoder = brEncoder_;
	
	gyro = gyro_;
	
	flPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
	blPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
	frPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
	brPID = new MetroPIDController( Drive::PID_P, Drive::PID_I, Drive::PID_D, MetroPIDController::PID, true );
	
	flPID->Disable();
	blPID->Disable();
	frPID->Disable();
	brPID->Disable();
	
	flSpeed = 0.0;
	blSpeed = 0.0;
	frSpeed = 0.0;
	brSpeed = 0.0;
	
	motorInverters[0] = 1;
	motorInverters[1] = 1;
	motorInverters[2] = 1;
	motorInverters[3] = 1;
	
	isPIDControl = false;
	isSlowDrive = false;

}

void Drive::Actuate(){

	flPID->SetSource( 1 / flEncoder->GetPeriod() );
	blPID->SetSource( 1 / flEncoder->GetPeriod() );
	frPID->SetSource( 1 / flEncoder->GetPeriod() );
	brPID->SetSource( 1 / flEncoder->GetPeriod() );

	double fl = flSpeed * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );
	double bl = blSpeed * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );
	double fr = frSpeed * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );
	double br = brSpeed * ( isSlowDrive ? Drive::SLOW_DRIVE_MULTIPLIER : 1.0 );

	if( isPIDControl ){
	
		flPID->SetSetpoint( fl * Drive::VEL_PID_MULTIPLIER );
		blPID->SetSetpoint( bl * Drive::VEL_PID_MULTIPLIER );
		frPID->SetSetpoint( fr * Drive::VEL_PID_MULTIPLIER );
		brPID->SetSetpoint( br * Drive::VEL_PID_MULTIPLIER );
	
		fl = flPID->GetOutput();
		bl = blPID->GetOutput();
		fr = frPID->GetOutput();
		br = brPID->GetOutput();
	
	}
	
	flMotor->Set( fl * motorInverters[0] );
	blMotor->Set( bl * motorInverters[1] );
	frMotor->Set( fr * motorInverters[2] );
	brMotor->Set( br * motorInverters[3] );

}

void Drive::Disable(){

	SetPIDControl( false );
	SetSlowDrive( false );

	flMotor->Set( 0.0 );
	blMotor->Set( 0.0 );
	frMotor->Set( 0.0 );
	brMotor->Set( 0.0 );

}

void Drive::SetMecanumXYTurn( double x, double y, double turn ){

	flSpeed = y + x + turn;
	blSpeed = y - x + turn;
	frSpeed = y - x - turn;
	brSpeed = y + x - turn;

}

void Drive::SetMecanumRLStrafe( double r, double l, double strafe ){

	flSpeed = l + strafe;
	blSpeed = l - strafe;
	frSpeed = r - strafe;
	brSpeed = r + strafe;

}

void Drive::SetMecanumFieldOriented( double x, double y, double turn ){
    
	double angle = GetGyroAngle();

	double cosA = cos( angle * 3.14159 / 180 );
	double sinA = sin( angle * 3.14159 / 180 );
	
    double xOut = x*cosA - y*sinA;
    double yOut = x*sinA + y*cosA;
        
	SetMecanumXYTurn( xOut, yOut, turn );
        
}

//TODO: Make it work for angles other than 0
void Drive::SetMecanumHoldAngle( double x, double y, double angle ){
	
	double gyroAngle = fmod( GetGyroAngle(), 360.0 );
	
	if( angle > 180 ){
		
		angle = -( 180 - ( angle - 180 ) );
		
	}
	
	SetMecanumXYTurn( x, y, Drive::ANGLE_P * ( gyroAngle - angle ) );
	
}

void Drive::ResetEncoders(){

	flEncoder->Reset();
	blEncoder->Reset();
	frEncoder->Reset();
	brEncoder->Reset();

}

double Drive::GetDistMoved(){

	return ( flEncoder->Get() + blEncoder->Get() + frEncoder->Get() + brEncoder->Get() ) / 4;

}

void Drive::ResetGyro(){

	gyro->Reset();

}

double Drive::GetGyroAngle(){

	return gyro->GetAngle();

}

bool Drive::IsPIDControl(){

	return isPIDControl;

}

void Drive::SetPIDControl( bool value ){

	isPIDControl = value;
	
	if( isPIDControl ){
	
		flPID->Enable();
		blPID->Enable();
		frPID->Enable();
		brPID->Enable();
	
	}
	else{
	
		flPID->Disable();
		blPID->Disable();
		frPID->Disable();
		brPID->Disable();
	
	}

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
	
	double maxValue = 1.0;
	        
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
	
}