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
		bool GetBangBang();
		void SetBangBang(bool BangBang);
		void Actuate();
		void Disable();
		
		static const double PID_P = 1.0 / 4000.0;
		static const double PID_I = 0.0;
		static const double PID_D = 1.0 / 4000.0;

		static const double MAX_RPM = 3800.0;
		static const double SPUN_UP_TOLERENCE = 50.0;
		static const double SPIN_UP_RPM = 3500.0;
		static const double SETPOINT_RPM = 3500.0;
		static const double SETPOINT_VOLTAGE = 1.0;
		static const double RAMP_TIPPING_POINT = 1500.0;
		static const double RAMP_VOLTAGE_CAP = 0.5;
		
	//private:
		SpeedController *motor;
		DualRelay *loader;
		Counter *counter;
		MetroPIDController *shooterPID;
		
		bool isPID;
		bool isBangBang;
		double shooterSpeed;
		double actualSpeed;
		Relay::Value loaderDirection;
	
};

#endif
