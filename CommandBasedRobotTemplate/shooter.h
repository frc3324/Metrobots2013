#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "util/dualrelay.h"

class Shooter {
	
	public:
		Shooter( SpeedController *motor_, DualRelay *loader_ );
		~Shooter(){};
		void SetShooterSpeed( double value );
		void SetLoaderDirection( Relay::Value value );
		void ShootWhenSpunUp();
		void Actuate();
		void Disable();
		
		
	private:
		SpeedController *motor;
		DualRelay *loader;
		
		double shooterSpeed;
		Relay::Value loaderDirection;
	
};

#endif
