#include "WPILib.h"

#include "util/atk3.h"
#include "util/metropidcontroller.h"
#include "util/dualrelay.h"
#include "drive.h"
#include <stdio.h>
#include <Math.h>

class CommandBasedRobot : public IterativeRobot {
private:
	
	typedef enum {NoScript, TwoPointScript} AutonScript;
	AutonScript script;
	int step;
	Timer *timer, *freshness;
	
	Victor *flMotor, *blMotor, *frMotor, *brMotor;
	DualRelay *wallRelay;
	Atk3 *leftJoystick;
	Atk3 *rightJoystick;
	
	Drive *drive;
	
	DriverStationLCD *ds;
	//NetworkTable *table;
	
	virtual void RobotInit() {
		
		flMotor = new Victor( 1 );
		blMotor = new Victor( 2 );
		frMotor = new Victor( 3 );
		brMotor = new Victor( 4 );
		
		timer = new Timer();
		
		wallRelay = new DualRelay( 1, 2 );

		leftJoystick = new Atk3( 1 );
		rightJoystick = new Atk3( 2 );
		
		drive = new Drive( flMotor, blMotor, frMotor, brMotor );
		drive->SetInvertedMotors( false, false, true, true );
		
		ds = DriverStationLCD::GetInstance();

		//table = NetworkTable::GetTable("net");
		////net->PutNumber("angle", 0.0);
		////net->PutBoolean("hasAngle", 0.0);
		
		script = NoScript;
		step = 0;
		timer->Reset();
		timer->Start();
		
	}
	
	virtual void AutonomousInit() {
		Disable();
		step = 0;
		timer->Reset();
	}
	
	virtual void AutonomousPeriodic() {
		PrintToDS();
		drive->Disable();

		flMotor->Set(0.0);
		blMotor->Set(0.0);
		frMotor->Set(0.0);
		brMotor->Set(0.0);
		
		Actuate();
	}
	
	virtual void TeleopInit() {
	}
	
	virtual void TeleopPeriodic() {
		UpdateOI();
		
		/*
		 * Slow Drive
		 * LEFT_BUTTON_3 or RIGHT_BUTTON_3
		 */
		drive->SetSlowDrive( leftJoystick->GetButton(Atk3::BUTTON_3) || rightJoystick->GetButton(Atk3::BUTTON_3) );
		
		/*
		 * Tank Drive
		 * LEFT_Y_AXIS: Left side
		 * RIGHT_Y_AXIS: Right side
		 */
		drive->SetLeftRight( leftJoystick->GetAxis( Atk3::Y ), rightJoystick->GetAxis( Atk3::Y ));

		/*
		 * Wall Control
		 * LEFT_BUTTON_5 or RIGHT_BUTTON_5: Hold to raise
		 * LEFT_BUTTON_4 or RIGHT_BUTTON_4: Hold to lower
		 */
		wallRelay->Set(
			(leftJoystick->GetButton(Atk3::BUTTON_5) || rightJoystick->GetButton(Atk3::BUTTON_5)) ? Relay::kForward :
			(leftJoystick->GetButton(Atk3::BUTTON_4) || rightJoystick->GetButton(Atk3::BUTTON_4)) ? Relay::kReverse :
			Relay::kOff);
		
		Actuate();
		PrintToDS();
		
	}
	
	virtual void DisabledInit() {
		
		Disable();
		
	}
	
	virtual void DisabledPeriodic() {
		
		UpdateOI();
		
		if( leftJoystick->GetButtonDown( Atk3::BUTTON_8 ) || rightJoystick->GetButtonDown( Atk3::BUTTON_8 ) ){
			script = NoScript;
		}
		
		if( leftJoystick->GetButtonDown( Atk3::BUTTON_9 ) || rightJoystick->GetButtonDown( Atk3::BUTTON_9 ) ){
			script = TwoPointScript;
		}
				
		PrintToDS();
		
	}
	
	void Actuate(){
		
		drive->Actuate();
		
	}
	
	void Disable(){
		
		drive->Disable();
		
	}
	
	void UpdateOI(){

		leftJoystick->Update();
		rightJoystick->Update();
		
	}
	
	void PrintToDS(){
		
		/*ds->Clear();
		ds->Printf(DriverStationLCD::kUser_Line1, 1, "Auto: %s", script == ShootScript ? "Shoot" : ( script == DriveScript ? "Drive(test)" : ( script == NoScript ? "None" : "YOU BROKE IT" ) ) );
		ds->Printf(DriverStationLCD::kUser_Line2, 1, "Dr: %s%s%f", drive->IsPIDControl() ? "PID, " : "", drive->IsFieldOriented() ? "FO, " : "", drive->GetGyroAngle() );
		ds->Printf(DriverStationLCD::kUser_Line3, 1, "Vi: %s, Fresh: %f", HasTarget() ? "Y" : "N", freshness->Get() );
		ds->Printf(DriverStationLCD::kUser_Line4, 1, "" );
		ds->Printf(DriverStationLCD::kUser_Line5, 1, "Sh: %sSET: %f", shooter->IsPID() ? "P, " : "", shooter->GetSetpoint() );
		ds->Printf(DriverStationLCD::kUser_Line6, 1, "Sh REAL: %f", shooter->GetActualSpeed() );
		ds->UpdateLCD();*/
		
	}
	
};

START_ROBOT_CLASS(CommandBasedRobot);
