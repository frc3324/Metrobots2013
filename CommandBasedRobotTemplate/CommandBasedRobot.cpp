#include "WPILib.h"

#include "util/gamepad.h"
#include "util/metropidcontroller.h"
#include "util/dualrelay.h"
#include "drive.h"
#include "shooter.h"
#include <stdio.h>
#include <Math.h>

class CommandBasedRobot : public IterativeRobot {
private:
	
	typedef enum {NoScript, ShootScript, DriveScript} AutonScript;
	AutonScript script;
	int step;
	Timer *timer, *freshness;
	
	Talon *flMotor, *blMotor, *frMotor, *brMotor;
	Victor *shooterMotor;
	DualRelay *loaderRelay;
	DualRelay *netRelay;
	DigitalInput *netLimit;
	Counter *shooterCounter;
	Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder; 
	Gyro *gyro;
	GamePad *driverGamePad;
	GamePad *shooterGamePad;
	
	Drive *drive;
	Shooter *shooter;
	
	DriverStationLCD *ds;
	NetworkTable *table;
	
	virtual void RobotInit() {
		
		flMotor = new Talon( 1 );
		blMotor = new Talon( 2 );
		frMotor = new Talon( 3 );
		brMotor = new Talon( 4 );
		
		timer = new Timer();
		freshness = new Timer();
		
		shooterMotor = new Victor( 5 );
		loaderRelay = new DualRelay( 1, 2 );
		netRelay = new DualRelay( 3, 4 );
		netLimit = new DigitalInput( 2 );
		shooterCounter = new Counter( 1 /*Insert Actual port here*/ );
		
		flEncoder = new Encoder( 9, 10 );
		blEncoder = new Encoder( 11, 12 );
		frEncoder = new Encoder( 5, 6 );
		brEncoder = new Encoder( 7, 8 );
		
		gyro = new Gyro( 1 );
		gyro->Reset();

		driverGamePad = new GamePad( 1 );
		shooterGamePad = new GamePad( 2 );
		
		
		drive = new Drive( flMotor, blMotor, frMotor, brMotor, flEncoder, blEncoder, frEncoder, brEncoder, gyro );
		drive->SetInvertedMotors( false, false, true, true );

		shooter = new Shooter( shooterMotor, loaderRelay, shooterCounter );
		
		ds = DriverStationLCD::GetInstance();

		table = NetworkTable::GetTable("net");
		//net->PutNumber("angle", 0.0);
		//net->PutBoolean("hasAngle", 0.0);
		
		script = ShootScript;
		step = 0;
		timer->Reset();
		timer->Start();
		
		freshness->Reset();
		freshness->Start();
		
	}
	
	virtual void AutonomousInit() {
		Disable();
		step = 0;
		timer->Reset();
		drive->ResetGyro();
	}
	
	virtual void AutonomousPeriodic() {
		PrintToDS();
		
		switch (script){
		case ShootScript:
			switch (step){
			case 0:
				drive->ResetGyro( 270.0 );
				shooter->SetPID( false );
				shooter->SetShooterSpeed( Shooter::SETPOINT_VOLTAGE );
				if( timer->Get() >= 0.0 ){ step++; timer->Reset(); }
				break;
			case 1:
				shooter->ShootWhenSpunUp();
				if( timer->Get() >= 15.0 ){ step++; timer->Reset(); }
				break;
			case 2:
				shooter->Disable();
			}
			break;
		case DriveScript:
			switch (step){
			case 0:
				drive->SetPIDControl(false);
				drive->SetFieldOriented(false);
				drive->SetTargetAngle( drive->GetGyroAngle() + 90.0 );
				drive->SetHoldAngle(true);
				timer->Reset();
				step++;
				break;
			case 1:
				if( timer->Get() > 2.0 || AngleDiff(drive->GetGyroAngle(), drive->targetAngle) < 5.0 ){ timer->Reset(); step++; }
				break;
			case 2:
				drive->SetMecanumXYTurn( 0.0, 0.4, 0.0 );
				if( drive->GetDistMoved() > 300 ){ timer->Reset(); step++; }
				break;
			case 3:
				drive->SetPIDControl( true );
				drive->SetHoldAngle( false );
				drive->SetMecanumXYTurn( 0.0, 0.0, 0.0 );
				step++;
				break;
			}
		case NoScript:
			break;
		}
		
		Actuate();
	}
	
	virtual void TeleopInit() {
		
		drive->SetFieldOriented(true);
		
	}
	
	virtual void TeleopPeriodic() {

		UpdateOI();
		
		/*
		 * Reset Gyro
		 * A: Press to reset gyro
		 */
		if( driverGamePad->GetButton( GamePad::A ) ){
			drive->ResetGyro();
		}
		
		/*
		 * Slow Drive
		 * LB or RB: Hold to toggle ON, Release to toggle OFF
		 */
		drive->SetSlowDrive( driverGamePad->GetButton( GamePad::LB ) || driverGamePad->GetButton( GamePad::RB ) );
		
		/*
		 * Field Oriented
		 * START: Press to toggle ON
		 * BACK: Press to toggle OFF
		 */
		drive->SetFieldOriented( driverGamePad->GetButtonDown( GamePad::START ) ? true : ( driverGamePad->GetButtonDown( GamePad::BACK ) ? false : drive->IsFieldOriented() ) );
		
		/*
		 * PID Control
		 * X: Press to toggle ON
		 * Y: Press to toggle OFF
		 */
		drive->SetPIDControl( driverGamePad->GetButtonDown( GamePad::X ) ? true : ( driverGamePad->GetButtonDown( GamePad::Y ) ? false : drive->IsPIDControl() ) );
		
		/*
		 * Mecanum Drive
		 * LEFT_X_AXIS: Strafe Left/Right
		 * LEFT_Y_AXIS: Forward/Reverse
		 * RIGHT_X_AXIS: Turn
		 */
		drive->SetMecanumXYTurn( driverGamePad->GetAxis( GamePad::LEFT_X ), driverGamePad->GetAxis( GamePad::LEFT_Y ), driverGamePad->GetAxis( GamePad::RIGHT_X ) );
			
		/*
		 * Hold Angle
		 * RIGHT_JS_BUTTON: Hold to hold current angle
		 * B: Hold to hold vision target angle
		 */
		if( driverGamePad->GetButtonDown( GamePad::RIGHT_JS ) ){	
			drive->SetTargetAngle( drive->GetGyroAngle() );			
		}
		if( driverGamePad->GetButton/*Down*/( GamePad::B ) ){	
			drive->SetTargetAngle( HasTarget() ? GetAbsoluteAngle() : drive->GetGyroAngle() );			
		}
		drive->SetHoldAngle( driverGamePad->GetButton( GamePad::RIGHT_JS ) || driverGamePad->GetButton( GamePad::B ) );					

		if(driverGamePad->GetDPadLeftDown()){
			drive->SetAimBias(drive->GetAimBias() - Drive::AIM_BIAS_INCREMENT);
		}
		if(driverGamePad->GetDPadRightDown()){
			drive->SetAimBias(drive->GetAimBias() + Drive::AIM_BIAS_INCREMENT);
		}
		
		/*
		 * Loader Control
		 * RB: Hold to run Forward
		 * LB: Hold to run Reverse
		 */
		shooter->SetLoaderDirection( shooterGamePad->GetButton( GamePad::RB ) ? Relay::kForward : ( shooterGamePad->GetButton( GamePad::LB ) ? Relay::kReverse : Relay::kOff ) );
		netRelay->Set( (shooterGamePad->GetButton( GamePad::START ) && netLimit->Get()) ? Relay::kForward : ( shooterGamePad->GetButton( GamePad::BACK ) ? Relay::kReverse : Relay::kOff ) );

		
		/*
		 * Shooter Setpoint with Speed Control
		 * A: Press to enable
		 */
		if( shooterGamePad->GetButtonDown( GamePad::A ) ){
			shooter->SetPID( true );
			shooter->SetShooterSpeed( Shooter::SETPOINT_RPM );
		}
		
		/*
		 * Stop Shooter
		 * B: Press to Stop Shooter
		 */
		if( shooterGamePad->GetButtonDown( GamePad::B ) ){
			shooter->SetShooterSpeed( 0.0 );
		}
		
		/*
		 * Shooter Setpoint with Straight Voltage
		 * X: Press to enable
		 */
		if( shooterGamePad->GetButtonDown( GamePad::X ) ){
			shooter->SetPID( false );
			shooter->SetShooterSpeed( Shooter::SETPOINT_VOLTAGE );
		}
		
		/*
		 * Shoot when Spun Up
		 * Y: Hold to Shoot when spun up
		 */
		if( shooterGamePad->GetButton( GamePad::Y ) ){
			shooter->ShootWhenSpunUp();
		}

		/*
		 * Manual Setpoint with Speed Control
		 * LEFT_JS_BUTTON: Hold to enable
		 * LEFT_JS_BUTTON: Release to maintain current setpoint
		 * LEFT_Y_AXIS: manualy set setpoint
		 */
		if( shooterGamePad->GetButton( GamePad::LEFT_JS ) ){
			shooter->SetPID( true );
			shooter->SetShooterSpeed( shooterGamePad->GetAxis( GamePad::LEFT_Y ) * Shooter::MAX_RPM );
		}
		
		/*
		 * Manual Setpoint with Straight Voltage
		 * RIGHT_JS_BUTTON: Hold to enable
		 * RIGHT_JS_BUTTON: Release to maintain current setpoint
		 * RIGHT_Y_AXIS: manualy set setpoint
		 */
		if( shooterGamePad->GetButton( GamePad::RIGHT_JS ) ){
			shooter->SetPID( false );
			shooter->SetShooterSpeed( shooterGamePad->GetAxis( GamePad::RIGHT_Y ) );
		}
		
		Actuate();
		PrintToDS();
		
	}
	
	virtual void DisabledInit() {
		
		Disable();
		
	}
	
	virtual void DisabledPeriodic() {
		
		UpdateOI();
		
		if( shooterGamePad->GetButtonDown( GamePad::A ) ){
			script = ShootScript;
		}
		
		if( shooterGamePad->GetButtonDown( GamePad::B ) ){
			script = NoScript;
		}
		
		if( shooterGamePad->GetButtonDown( GamePad::X ) ){
			script = DriveScript;
		}
		
		PrintToDS();
		
	}
	
	void Actuate(){
		
		drive->Actuate();
		shooter->Actuate();
		
	}
	
	void Disable(){
		
		drive->Disable();
		shooter->Disable();
		
	}
	
	void UpdateOI(){

		driverGamePad->Update();
		shooterGamePad->Update();
		IsFreshTarget();
		
	}
	
	void PrintToDS(){
		
		ds->Clear();
		ds->Printf(DriverStationLCD::kUser_Line1, 1, "Auto: %s", script == ShootScript ? "Shoot" : ( script == DriveScript ? "Drive(test)" : ( script == NoScript ? "None" : "YOU BROKE IT" ) ) );
		ds->Printf(DriverStationLCD::kUser_Line2, 1, "Dr: %s%s%f", drive->IsPIDControl() ? "PID, " : "", drive->IsFieldOriented() ? "FO" : "", drive->GetGyroAngle() );
		ds->Printf(DriverStationLCD::kUser_Line3, 1, "Vi: %s, Fresh:%f", HasTarget() ? "Y" : "N", freshness->Get() );
		ds->Printf(DriverStationLCD::kUser_Line4, 1, "Bias: %f", drive->GetAimBias() );
		ds->Printf(DriverStationLCD::kUser_Line5, 1, "Sh: %sSET: %f", shooter->IsPID() ? "P, " : "", shooter->GetSetpoint() );
		ds->Printf(DriverStationLCD::kUser_Line6, 1, "Sh REAL: %f", shooter->GetActualSpeed() );
		ds->UpdateLCD();
		
	}
	
	double GetAbsoluteAngle() {
		return table->GetNumber("angle", 0.0) + drive->GetGyroAngle();
	}
	
	double GetRelativeAngle() {
		return table->GetNumber("angle", 0.0);
	}
	
	bool HasTarget(){
		return table->GetBoolean("hasTarget", false);
	}
	
	bool IsFreshTarget() {
		bool isFresh = table->GetBoolean("isFresh", false);
		if(isFresh) {
			freshness->Reset();
		}
		table->PutBoolean("isFresh", false);
		return isFresh;
	}
	
	double AngleDiff( double angle1, double angle2 ){
		return fmod(angle1 - angle2 + 180.0, 360.0) - 180.0;
	}
	
};

START_ROBOT_CLASS(CommandBasedRobot);

