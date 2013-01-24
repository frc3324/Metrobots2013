#include "metrobot.h"
#include "gamepad.h"

/*
 *All hardware initialization goes in constructor (anything with a port number)
 *Victors, Jaguars, sensors, joysticks, etc
 *
 *Wiring ports can be changed here and will be affected throughout the program
 */
Metrobot::Metrobot(){

	flMotor = new Talon( 1 );
	blMotor = new Talon( 2 );
	frMotor = new Talon( 3 );
	brMotor = new Talon( 4 );
	
	flEncoder = new Encoder( 1, 2 );
	blEncoder = new Encoder( 3, 4 );
	frEncoder = new Encoder( 5, 6 );
	brEncoder = new Encoder( 7, 8 );
	
	gyro = new Gyro( 1 );

	gamePad = new GamePad( 1 );

}

void Metrobot::RobotInit(){

	drive = new Drive( flMotor, blMotor, frMotor, brMotor, 
						flEncoder, blEncoder, frEncoder, brEncoder, gyro );
	drive->SetInvertedMotors( false, false, false, false );
	
	ds = DriverStationLCD::GetInstance();
	
	autonScript = NO_SCRIPT;
	autonStep = 0;
	
	GetWatchdog().SetExpiration( 0.1 );
	GetWatchdog().SetEnabled( true );
	
}

void Metrobot::AutonomousInit(){ 
	
	Disable();
	
	autonTimer->Start();
	autonTimer->Reset();
	autonStep = 0;

}

void Metrobot::AutonomousPeriodic(){

	UpdateOI();
	
	switch( autonScript ){
	
	case SCRIPT_1:
		switch( autonStep ){
		
				case 0:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 1:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 2:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 3:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 4:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				default:
					break;
				
		}
		break;
		
	case SCRIPT_2:
		switch( autonStep ){

				case 0:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 1:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 2:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 3:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				case 4:
					if( true || autonTimer->Get() >= 1.0 ){ autonTimer->Reset(); autonStep++; }
					break;
				default:
					break;
				
		}
		break;
	default:
		break;
	
	}
	
	Actuate();
	PrintToDS();
	GetWatchdog().Feed();
	
}

void Metrobot::AutonomousContinuous(){ Wait( 0.020 ); }

void Metrobot::TeleopInit(){

	Disable();
	
	//Set states for tele-op control
	drive->SetPIDControl( false );
	drive->SetReversedFront( false );

}

void Metrobot::TeleopPeriodic(){
	UpdateOI();
	
	
	if( gamePad->GetButtonDown( GamePad::A ) ){
		drive->ResetGyro();
	}
	drive->SetMecanumFieldOriented( gamePad->GetAxis( GamePad::LEFT_X), gamePad->GetAxis( GamePad::LEFT_Y ), gamePad->GetAxis( GamePad::RIGHT_X ) );
	
	
	Actuate();
	PrintToDS();
	GetWatchdog().Feed();
	
}

void Metrobot::TeleopContinuous(){ Wait( 0.020 ); }

void Metrobot::DisabledInit(){

	Disable();

}

void Metrobot::DisabledPeriodic(){

	UpdateOI();
	
	Disable();
	GetWatchdog().Feed();

}

void Metrobot::DisabledContinuous(){ Wait( 0.020 ); }

void Metrobot::Actuate(){

	drive->Actuate();

}

void Metrobot::Disable(){

	drive->Disable();

}

void Metrobot::UpdateOI(){

	//gamePad->Update();

}

void Metrobot::PrintToDS(){

	ds->Clear();
	ds->Printf(DriverStationLCD::kUser_Line1, 1, "Team 3324, v1.0");
	ds->Printf(DriverStationLCD::kUser_Line2, 1, "Auton: %s, Step: %d, Time: %f", autonScript == NO_SCRIPT ? "None" : ( autonScript == SCRIPT_1 ? "1" : "2" ), autonStep, autonTimer->Get() );
	ds->Printf(DriverStationLCD::kUser_Line3, 1, "Gyro: %f", drive->GetGyroAngle() );
	ds->Printf(DriverStationLCD::kUser_Line4, 1, "Drive PID: %s", drive->IsPIDControl() ? "Enabled" : "Disabled" );
	ds->Printf(DriverStationLCD::kUser_Line5, 1, "" );
	ds->Printf(DriverStationLCD::kUser_Line6, 1, "" );
	ds->UpdateLCD();

}

START_ROBOT_CLASS( Metrobot );
