#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"

class Shooter {
	
	public:
		Shooter( SpeedController Motor_, DualRelay Loader_ );
		~Shooter(){};
		void SetShooterSpeed( float speed_ );
		void SetLoaderDirection( Relay::Value value_ );
		void ShootWhenSpunUp();
		
		
		
	private:
		SpeedController *Motor;
		DualRelay *Loader;
	
};

#endif
