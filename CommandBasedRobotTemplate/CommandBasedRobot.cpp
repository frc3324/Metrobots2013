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
	
	//DriverStationLCD *ds;
	
	CommandBasedRobot::AutonScripts autonScript;
	Timer *autonTimer;
	int autonStep;
	
	virtual void RobotInit() {
		
		flMotor = new Talon( 1 );
		blMotor = new Talon( 2 );
		frMotor = new Talon( 3 );
		brMotor = new Talon( 4 );
		
		flEncoder = new Encoder( 1, 2 );
		blEncoder = new Encoder( 3, 4 );
		frEncoder = new Encoder( 5, 6 );
		brEncoder = new Encoder( 7, 8 );
		
		gyro = new Gyro( 1 );
		gyro->Reset();

		gamePad = new GamePad( 1 );
		
		drive = new Drive( flMotor, blMotor, frMotor, brMotor, 
							flEncoder, blEncoder, frEncoder, brEncoder, gyro );
		drive->SetInvertedMotors( false, false, true, true );
		
		//ds = DriverStationLCD::GetInstance();
		
		autonScript = NO_SCRIPT;
		autonStep = 0;
		
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
		
		drive->SetMecanumXYTurn( gamePad->GetAxis( GamePad::LEFT_X ), gamePad->GetAxis( GamePad::LEFT_Y ), gamePad->GetAxis( GamePad::RIGHT_X ) );

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
		
		/*ds->Clear();
		ds->Printf(DriverStationLCD::kUser_Line1, 1, "Team 3324, v1.0");
		ds->Printf(DriverStationLCD::kUser_Line2, 1, "Auton: %s, Step: %d, Time: %f", autonScript == NO_SCRIPT ? "None" : ( autonScript == SCRIPT_1 ? "1" : "2" ), autonStep, autonTimer->Get() );
		ds->Printf(DriverStationLCD::kUser_Line3, 1, "Gyro: %f", drive->GetGyroAngle() );
		ds->Printf(DriverStationLCD::kUser_Line4, 1, "Drive PID: %s", drive->IsPIDControl() ? "Enabled" : "Disabled" );
		ds->Printf(DriverStationLCD::kUser_Line5, 1, "fl: %f, bl: %f", drive->flEncoder->Get(), drive->blEncoder->Get() );
		ds->Printf(DriverStationLCD::kUser_Line6, 1, "fr: %f, br: %f", drive->frEncoder->Get(), drive->brEncoder->Get() );
		ds->UpdateLCD();*/
		
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

