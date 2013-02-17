#ifndef SHOOTER_H
#define SHOOTER_H

#include "WPILib.h"
#include "util/dualrelay.h"
#include "util/metropidcontroller.h"

class Shooter {
	
	public:
		Shooter( SpeedController *motor_, DualRelay *loader_, Counter *counter_ );
		~Shooter(){};
		void SetShooterSpeed( double value );
		void SetLoaderDirection( Relay::Value value );
		void ShootWhenSpunUp();
		bool IsSpunUp();
		void SetPID( bool value );
		bool IsPID();
		double GetSetpoint();
		double GetActualSpeed();
		void Actuate();
		void Disable();
		
		static const double PID_P = 0.0;
		static const double PID_I = 0.0;
		static const double PID_D = 0.0;

		static const double MAX_RPM = 3800.0;
		static const double SPUN_UP_TOLERENCE = 200.0;
		static const double SETPOINT_RPM = 3500.0;
		static const double SETPOINT_VOLTAGE = 1.0;
		
	private:
		SpeedController *motor;
		DualRelay *loader;
		Counter *counter;
		MetroPIDController *shooterPID;
		
		bool isPID;
		double shooterSpeed;
		double actualSpeed;
		Relay::Value loaderDirection;
	
};

#endif
