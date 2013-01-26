#include "WPILib.h"

#include "util/gamepad.h"
#include "util/metropidcontroller.h"
#include "drive.h"
#include <stdio.h>
#include <Math.h>

class CommandBasedRobot : public IterativeRobot {
private:
	
	enum AutonScripts {
		NO_SCRIPT,
		SCRIPT_1,
		SCRIPT_2
	};
	
	Talon *flMotor, *blMotor, *frMotor, *brMotor;
	Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder; 
	Gyro *gyro;
	GamePad *gamePad;
	
	Drive *drive;
	
	DriverStationLCD *ds;
	
	CommandBasedRobot::AutonScripts autonScript;
	Timer *autonTimer;
	int autonStep;
	int driveControls;
	
	virtual void RobotInit() {
		
		flMotor = new Talon( 1 );
		blMotor = new Talon( 2 );
		frMotor = new Talon( 3 );
		brMotor = new Talon( 4 );
		
		flEncoder = new Encoder( 9, 10 );
		blEncoder = new Encoder( 11, 12 );
		frEncoder = new Encoder( 5, 6 );
		brEncoder = new Encoder( 7, 8 );
		
		gyro = new Gyro( 1 );
		gyro->Reset();

		gamePad = new GamePad( 1 );
		
		drive = new Drive( flMotor, blMotor, frMotor, brMotor, 
							flEncoder, blEncoder, frEncoder, brEncoder, gyro );
		drive->SetInvertedMotors( false, false, true, true );
		
		ds = DriverStationLCD::GetInstance();
		
		autonScript = NO_SCRIPT;
		autonStep = 0;
		
		driveControls = 0;
		// 0 for XYTurn
		// 1 for RL Strafe
		
	}
	
	virtual void AutonomousInit() {
	
		
		
	}
	
	virtual void AutonomousPeriodic() {
		
		
		
	}
	
	virtual void TeleopInit() {
		
		drive->SetFieldOriented( true );
		
	}
	
	virtual void TeleopPeriodic() {

		UpdateOI();

		if( gamePad->GetButtonDown( GamePad::X ) ){
			driveControls = 0; //XYTurn
		}
		if( gamePad->GetButtonDown( GamePad::Y ) ){
			driveControls = 1; //RLStrafe
		}
		
		if( gamePad->GetButtonDown( GamePad::START ) ){
			drive->SetFieldOriented( true );
		}
		if( gamePad->GetButtonDown( GamePad::BACK ) ){
			drive->SetFieldOriented( false );
		}
						
		drive->SetSlowDrive( gamePad->GetButton( GamePad::LB ) || gamePad->GetButton( GamePad::RB ) );
		
		if( driveControls == 0 ){
			drive->SetMecanumXYTurn( gamePad->GetAxis( GamePad::LEFT_X ), gamePad->GetAxis( GamePad::LEFT_Y ), gamePad->GetAxis( GamePad::RIGHT_X ) );
		}
		if( driveControls == 1 ){
			drive->SetMecanumRLStrafe( gamePad->GetAxis( GamePad::RIGHT_Y ), gamePad->GetAxis( GamePad::LEFT_Y ), gamePad->GetAxis( GamePad::TRIGGER ) );
		}
				
			
		if( gamePad->GetButtonDown( GamePad::RIGHT_JS ) ){
					
			drive->SetHoldAngle( true );
			drive->SetTargetAngle( fmod( drive->GetGyroAngle(), 360.0 ) );
			
		}
		if( gamePad->GetButtonUp( GamePad::RIGHT_JS ) ){
					
			drive->SetHoldAngle( false );
			
		}
							
		drive->SetPIDControl( gamePad->GetButton( GamePad::B ) );
		
		if( gamePad->GetButton( GamePad::A ) ){
					
					drive->ResetGyro();
					
		}
				
		fprintf(stderr, "fl: %f", flEncoder->Get());
				
		
		Actuate();
		
		ds->Clear();
		ds->Printf(DriverStationLCD::kUser_Line1, 1, "Team 3324, v3.0");
		//ds->Printf(DriverStationLCD::kUser_Line2, 1, "Auton: %s, Step: %d, Time: %f", autonScript == NO_SCRIPT ? "None" : ( autonScript == SCRIPT_1 ? "1" : "2" ), autonStep, autonTimer->Get() );
		ds->Printf(DriverStationLCD::kUser_Line3, 1, "Gyro: %f", drive->GetGyroAngle() );
		ds->Printf(DriverStationLCD::kUser_Line4, 1, "Drive PID: %s", drive->IsPIDControl() ? "Enabled" : "Disabled" );
		ds->Printf(DriverStationLCD::kUser_Line5, 1, "fr: %i, br: %i", drive->frEncoder->Get(), drive->brEncoder->Get() );
		ds->Printf(DriverStationLCD::kUser_Line6, 1, "fl: %i, bl: %i", drive->flEncoder->Get(), drive->blEncoder->Get() );
		ds->UpdateLCD();
		
	}
	
	virtual void TestPeriodic() {
		
		
		
	}
	
	void Actuate(){
		
		drive->Actuate();
		
	}
	
	void UpdateOI(){
		
		gamePad->Update();
		
	}
	
};

START_ROBOT_CLASS(CommandBasedRobot);

