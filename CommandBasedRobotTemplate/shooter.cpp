#include "shooter.h"
#include <Math.h>

Shooter::Shooter( SpeedController *motor_, DualRelay *loader_, Counter *counter_ ){
	
	motor = motor_;
	loader = loader_;
	counter = counter_;
	
	shooterSpeed = 0.0;
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
	
	bool isSpunUp = shooterSpeed <= ( 60.0 / counter->GetPeriod() );
	loader->Set( isSpunUp ? Relay::kForward : Relay::kOff );
	
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

void Shooter::Actuate(){
	
	shooterPID->SetSource( 60.0 / counter->GetPeriod() );
	shooterPID->SetSetpoint( shooterSpeed );
	
	double setSpeed = shooterSpeed;
	
	if( isPID ){
		
		setSpeed = shooterPID->GetOutput();
		
	}
	
	motor->Set( setSpeed );
	
	loader->Set( loaderDirection );
	
}

void Shooter::Disable(){
	
	motor->Set( 0.0 );
	loader->Set( Relay::kOff );
	
}
