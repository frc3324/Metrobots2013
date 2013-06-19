#include "shooter.h"
#include <Math.h>

Shooter::Shooter( SpeedController *motor_, DualRelay *loader_, Counter *counter_ ){
	
	motor = motor_;
	loader = loader_;
	counter = counter_;
	
	shooterSpeed = 0.0;
	actualSpeed = 0.0;
	loaderDirection = Relay::kOff;
	isPID = false;
	
	counter->Start();
	
	shooterPID = new MetroPIDController( Shooter::PID_P, Shooter::PID_I, Shooter::PID_D, MetroPIDController::BANG_BANG, true );
	shooterPID->Disable();
	
}

void Shooter::SetShooterSpeed( double value ){
	
	shooterSpeed = value;
	
}

void Shooter::SetLoaderDirection( Relay::Value value ){
	
	loaderDirection = value;
	
}

void Shooter::ShootWhenSpunUp(){
	SetLoaderDirection( IsSpunUp() ? Relay::kForward : Relay::kOff );
}

bool Shooter::IsSpunUp(){
	if (isPID) {
		return actualSpeed >= shooterSpeed - Shooter::SPUN_UP_TOLERENCE;
	} else {
		return actualSpeed >= Shooter::SPIN_UP_RPM - Shooter::SPUN_UP_TOLERENCE;
	}
}

bool shooter::GetBangBang() {
	return isBangBang;
}

void shooter::SetBangBang(bool BangBang) {
	isBangBang = BangBang;
}

void Shooter::SetPID( bool value ){
	
	isPID = value;
	
	if( isPID ){
		shooterPID->Enable();
	}
	else{
		shooterPID->Disable();
	}
	
}

bool Shooter::IsPID(){
	return isPID;
}

double Shooter::GetSetpoint(){
	return shooterSpeed;
}

double Shooter::GetActualSpeed(){
	return actualSpeed;
}

void Shooter::Actuate(){
	
	actualSpeed = 60.0 / counter->GetPeriod();
	shooterPID->SetSource( actualSpeed );
	shooterPID->SetSetpoint( shooterSpeed );
	
	double setSpeed = shooterSpeed;
	
	if( isPID ){
		
		setSpeed = shooterPID->GetOutput();
		
	} else if (isBangBang) {
		setSpeed = (actualSpeed >= shooterSpeed ? 0.0 : 1.0);
	}
	
	if(actualSpeed < Shooter::RAMP_TIPPING_POINT){
		//setSpeed = min(setSpeed, Shooter::RAMP_VOLTAGE_CAP);
	}
	
	motor->Set( setSpeed );
	
	loader->Set( loaderDirection );
	
}

void Shooter::Disable(){
	
	shooterSpeed = 0.0;
	loaderDirection = Relay::kOff;
	motor->Set( 0.0 );
	loader->Set( Relay::kOff );
	
}
