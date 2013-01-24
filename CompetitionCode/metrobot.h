#ifndef METROBOT_H
#define METROBOT_H

#include "WPILib.h"

#include "drive.h"

#include "util/gamepad.h"

class Metrobot : public IterativeRobot {

	public:
		enum AutonScripts {
			NO_SCRIPT,
			SCRIPT_1,
			SCRIPT_2
		};
	
		Metrobot();
		~Metrobot(){};
		void RobotInit();
		void AutonomousInit();
		void AutonomousPeriodic();
		void AutonomousContinuous();
		void TeleopInit();
		void TeleopPeriodic();
		void TeleopContinuous();
		void DisabledInit();
		void DisabledPeriodic();
		void DisabledContinuous();
		
		void Actuate();
		void Disable();
		void UpdateOI();
		void PrintToDS();
		
	private:
		Talon *flMotor, *blMotor, *frMotor, *brMotor;
		Encoder *flEncoder, *blEncoder, *frEncoder, *brEncoder; 
		Gyro *gyro;
		GamePad *gamePad;
		
		Drive *drive;
		
		DriverStationLCD *ds;
		
		Metrobot::AutonScripts autonScript;
		Timer *autonTimer;
		int autonStep;

};

#endif
