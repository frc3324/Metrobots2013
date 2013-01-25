#include "WPILib.h"
#include <DriverStationLCD.h>
#include <math.h>
#include <string.h>
using namespace std;

DriverStationLCD *text;

class RobotDemo : public IterativeRobot
{
	
	Jaguar fl, bl, fr, br;
	Joystick gamePad;
	Gyro gyro;
	double currcos;
	
public:
	RobotDemo(void):
		fl( 1 ),
		bl( 2 ),
		fr( 3 ),
		br( 4 ),
		gamePad( 1 ),
		gyro( 1 )
	{
	
		text = DriverStationLCD::GetInstance();
		gyro.Reset();
		currcos = 0.0;
	}
	
	void AutonomousInit(){
			
			
			
	}
	
	void AutonomousPeriodic(){
			
			
			
	}
		
	void AutonomousContinuous(){
			
		Wait( 0.020 );
			
	}
	
	void TeleopInit(){
			
		//gyro.Reset();
			
	}
	
	void TeleopPeriodic(){
			
		//MecanumDrive( gamePad.GetRawAxis( 1 ), -gamePad.GetRawAxis( 2 ), -gamePad.GetRawAxis( 4 ) );
					
		if( gamePad.GetRawButton( 1 ) ){
			
			gyro.Reset();
			
		}
		
		if( gamePad.GetRawButton( 2 ) ){
			
			MecanumDriveStraight( 0.0, 0.5, (double)gyro.GetAngle() );
			
		}
		
		else if( gamePad.GetRawButton( 3 ) ){
			
			MecanumDriveStraight( gamePad.GetRawAxis( 1 ), -gamePad.GetRawAxis( 2 ), (double)gyro.GetAngle() );
			
		}
		
		/*else if( gamePad.GetRawButton( 4 ) ){
			
			MecanumDriveStraight( gamePad.GetRawAxis( 1 ), -gamePad.GetRawAxis( 2 ), (double)gyro.GetAngle()- gamePad.GetDirectionDegrees() );
			
		}*/
		
		else{
			
			MecanumFieldOriented( gamePad.GetRawAxis( 1 ), -gamePad.GetRawAxis( 2 ), -gamePad.GetRawAxis( 4 ), gyro.GetAngle() );
			
		}
		
		text->Clear();
		text->Printf(DriverStationLCD::kUser_Line1, 1, "2013 Competition Chassis with Gyro");	
		text->Printf(DriverStationLCD::kUser_Line2, 1, "%f", gyro.GetAngle() );	
		//text->Printf(DriverStationLCD::kUser_Line3, 1, "%f", currcos );	
		text->UpdateLCD();
		
	}
		
	void TeleopContinuous(){
			
		Wait( 0.020 );
			
	}
	
	void DisabledInit(){
			
			
			
	}
	
	void DisabledPeriodic(){
			
			
			
	}
		
	void DisabledContinuous(){
			
		Wait( 0.020 );
			
	}
	
	void MecanumDriveStraight( double x, double y, double angleIn ){
		
		double angle =  fmod( angleIn, 360.0 );
		
		if( angle > 180 ){
			
			angle = -( 180 - ( angle - 180 ) );
		
		}
		
		MecanumDrive( x, y, 1/45.0 * angle );
	}
	
	void MecanumFieldOriented( double x, double y, double turn, double angle ){
		
		/*double radius = sqrt( x * x + y * y );
		double theta = atan( y / x );
		if( x < 0 ){ theta += 3.14159; }
		
		theta = theta - ( angle * 3.14159 / 180 );
		
		double xOut = radius * cos( theta );
		currcos = theta;
		double yOut = radius * sin( theta );	
		*/

		double cosA = cos( angle * 3.14159 / 180 );
		double sinA = sin( angle * 3.14159 / 180 );
		
		double xOut = x * cosA - y * sinA;
		double yOut = x * sinA + y * cosA;
		
		MecanumDrive( xOut, yOut, turn );
		
	}
	
	void MecanumDrive( double x, double y, double turn ){

		fl.Set( -( x + y + turn ) );
		bl.Set( -( -x + y + turn ) );
		fr.Set( -x + y - turn );
		br.Set( x + y - turn );
		
	}
	
};

START_ROBOT_CLASS(RobotDemo);