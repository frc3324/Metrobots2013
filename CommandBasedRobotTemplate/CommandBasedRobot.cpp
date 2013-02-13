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
	Timer *timer;
	
	Talon *flMotor, *blMotor, *frMotor, *brMotor;
	Victor *shooterMotor;
	DualRelay *loaderRelay;
	Counter *shooterCounter;
	Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder; 
	Gyro *gyro;
	GamePad *driverGamePad;
	GamePad *shooterGamePad;
	
	Drive *drive;
	Shooter *shooter;
	
	DriverStationLCD *ds;
		
	virtual void RobotInit() {
		
		flMotor = new Talon( 1 );
		blMotor = new Talon( 2 );
		frMotor = new Talon( 3 );
		brMotor = new Talon( 4 );
		
		shooterMotor = new Victor( 5 );
		loaderRelay = new DualRelay( 1, 2 );
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
		
		script = ShootScript;
		step = 0;
		timer->Start();
		
	}
	
	virtual void AutonomousInit() {
		Disable();
		step = 0;
		timer->Reset();
	}
	
	virtual void AutonomousPeriodic() {
		PrintToDS();
		
		switch (script){
		case ShootScript:
			switch (step){
			case 0:
				shooter->SetPID( true );
				shooter->SetShooterSpeed( Shooter::SETPOINT_RPM );
				if( timer->Get() >= 0.0 ){ step++; timer->Reset(); }
				break;
			case 1:
				shooter->ShootWhenSpunUp();
				if( timer->Get() >= 15.0 ){ step++; timer->Reset(); }
				break;
			}
			break;
		case DriveScript:
			switch (step){
			case 0:
				drive->SetPIDControl( false );
				drive->SetFieldOriented( false );
				drive->SetTargetAngle( drive->GetGyroAngle() + 90.0 );
				if( timer->Get() >= 0.0 ){ step++; timer->Reset(); }
				break;
			case 1:
				drive->SetHoldAngle( true );
				if( timer->Get() >= 5.0 || fabs(drive->GetGyroAngle()-drive->targetAngle) < 5.0 ){ step++; timer->Reset(); }
				break;
			case 2:
				drive->ResetEncoders();
				if( timer->Get() >= 2.0 ){ step++; timer->Reset(); }
			case 3:
				drive->SetMecanumXYTurn( 0.0, 0.4, 0.0 );
				if( timer->Get() >= 5.0 || drive->GetDistMoved() < -1000 ){ step++; timer->Reset(); }
			case 4:
				drive->SetPIDControl( true );
				drive->SetMecanumXYTurn( 0.0, 0.4, 0.0 );
			}
			break;
		case NoScript:
			break;
		}
		
		Actuate();
	}
	
	virtual void TeleopInit() {
		
		
		
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
		 * B: Hold to hold vision target angle (not implemented yet)
		 */
		if( driverGamePad->GetButtonDown( GamePad::RIGHT_JS ) ){	
			drive->SetTargetAngle( drive->GetGyroAngle() );			
		}
		if( driverGamePad->GetButtonDown( GamePad::B ) ){	
			drive->SetTargetAngle( drive->GetGyroAngle() /*Insert Vision angle here*/ );			
		}
		drive->SetHoldAngle( driverGamePad->GetButton( GamePad::RIGHT_JS ) || driverGamePad->GetButton( GamePad::B ) );
							

		/*
		 * Loader Control
		 * RB: Hold to run Forward
		 * LB: Hold to run Reverse
		 */
		shooter->SetLoaderDirection( shooterGamePad->GetButton( GamePad::RB ) ? Relay::kForward : ( shooterGamePad->GetButton( GamePad::LB ) ? Relay::kReverse : Relay::kOff ) );
		
		/*
		 * Shooter Setpoint with Speed Control
		 * A: Press to enable
		 * Y: Press to enable
		 */
		if( shooterGamePad->GetButtonDown( GamePad::A ) || shooterGamePad->GetButtonDown( GamePad::Y ) ){
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
		 * Y: Press once to enable shooter ( See above )
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
		
	}
	
	void PrintToDS(){
		
		ds->Clear();
		ds->Printf(DriverStationLCD::kUser_Line1, 1, "Auton: %s", script == ShootScript ? "Shoot" : ( script == NoScript ? "None" : "YOU BROKE IT" ) );
		ds->Printf(DriverStationLCD::kUser_Line2, 1, "Drive Gyro: %f", /*drive->GetGyroAngle()*/drive->GetDistMoved() );
		ds->Printf(DriverStationLCD::kUser_Line3, 1, "PID: %s, FO: %s", drive->IsPIDControl() ? "On" : "Off", drive->IsFieldOriented() ? "On" : "Off" );
		ds->Printf(DriverStationLCD::kUser_Line4, 1, "Shooter PID: %s", shooter->IsPID() ? "On" : "Off");
		ds->Printf(DriverStationLCD::kUser_Line5, 1, "Shooter SET: %f", shooter->GetSetpoint() );
		ds->Printf(DriverStationLCD::kUser_Line6, 1, "Shooter REAL: %f", shooter->GetActualSpeed() );
		ds->UpdateLCD();
		
	}
	
};

START_ROBOT_CLASS(CommandBasedRobot);

