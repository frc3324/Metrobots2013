#ifndef DRIVE_H
#define DRIVE_H

#include "WPILib.h"
#include <Math.h>

class Drive {

	public:
		Drive( SpeedController *flMotor_, SpeedController *blMotor_, SpeedController *frMotor_, SpeedController *brMotor_);
		~Drive(){};
		void Actuate();
		void Disable();
		void SetLeftRight( double left, double right );
		void SetForwardTurn( double forward, double turn );
		bool IsSlowDrive();
		void SetSlowDrive( bool value );
		void SetInvertedMotors( bool fl, bool bl, bool fr, bool br );
		
		static const double SLOW_DRIVE_MULTIPLIER = 0.4;

	//private:
		void NormalizeMotorSpeeds();
	
		SpeedController *flMotor, *blMotor, *frMotor, *brMotor;
		
		double driverLeft, driverRight;
		int motorInverters[4];
		
		bool isSlowDrive;

};

#endif
