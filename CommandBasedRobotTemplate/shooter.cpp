#include "shooter.h"
#include <Math.h>

Shooter::Shooter( SpeedController *motor_, DualRelay *loader_ ){
	
	motor = motor_;
	loader = loader_;
	
	shooterSpeed = 0.0;
	loaderDirection = Relay::kOff;
	
}

void Shooter::SetShooterSpeed( double value ){
	
	shooterSpeed = value;
	
}

void Shooter::SetLoaderDirection( Relay::Value value ){
	
	loaderDirection = value;
	
}

void Shooter::ShootWhenSpunUp(){
	
	
	
}

void Shooter::Actuate(){
	
	//TODO: Add PID control or Bang Bang
	motor->Set( shooterSpeed );
	
	loader->Set( loaderDirection );
	
}

void Shooter::Disable(){
	
	motor->Set( 0.0 );
	loader->Set( Relay::kOff );
	
}