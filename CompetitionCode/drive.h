#ifndef DRIVE_H
#define DRIVE_H

#include "WPILib.h"
#include <Math.h>
#include "util/metropidcontroller.h"

class Drive {

	public:
		Drive( Jaguar *flMotor_, Jaguar *blMotor_, Jaguar *frMotor_, Jaguar *brMotor_, 
				Encoder *flEncoder_, Encoder *blEncoder_, Encoder *frEncoder_, Encoder *brEncoder_, 
				Gyro *gyro_ );
		~Drive(){};
		void Actuate();
		void Disable();
		void SetMecanumXYTurn( double x, double y, double turn );
		void SetMecanumRLStrafe( double leftSide, double rightSide, double strafe );
		void SetMecanumFieldOriented( double x, double y, double turn );
		void SetMecanumHoldAngle( double x, double y );
		double GetDistMoved();
		void ResetEncoders();
		void ResetGyro();
		double GetGyroAngle();
		void SetPIDControl( bool value );
		bool IsPIDControl();
		void SetReversedFront( bool value );
		bool IsReversedFront();
		bool IsSlowDrive();
		void SetSlowDrive( bool value );
		void SetInvertedMotors( bool fl, bool bl, bool fr, bool br );
		
		static const double PID_P = 1.0;
		static const double PID_I = 0.0;
		static const double PID_D = 1.0;
		static const double VEL_PID_MULTIPLIER = 1600;
		
		static const double ANGLE_P = 1.0/45.0; 
		
		static const double SLOW_DRIVE_MULTIPLIER = 0.4;
			
	private:
		void NormalizeMotorSpeeds();
		double SquareAndPreserveSign( double input );
	
		Jaguar *flMotor, *blMotor, *frMotor, *brMotor;
		Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder;
		Gyro *gyro;
		MetroPIDController *flPID, *blPID, *frPID, *brPID;
		
		double flSpeed, blSpeed, frSpeed, brSpeed;
		int motorInverters[4];
		
		bool isPIDControl;
		bool isSlowDrive;
		bool isReversedFront;

};

#endif
