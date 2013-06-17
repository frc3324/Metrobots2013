#ifndef ATK3_H
#define ATK3_H

#include "WPILib.h"
#define MAX_NUM_BUTTONS 12

class Atk3 {

	public:
		Atk3( int port );
		double GetAxis( int axis );
		void Update();
		bool GetButton( int button );
		bool GetButtonDown( int button );
		bool GetButtonUp( int button );

		static const double AXIS_DEADBAND = 0.10;
		
		static const int TRIGGER = 1;
		static const int BUTTON_2 = 2;
		static const int BUTTON_3 = 3;
		static const int BUTTON_4 = 4;
		static const int BUTTON_5 = 5;
		static const int BUTTON_6 = 6;
		static const int BUTTON_7 = 7;
		static const int BUTTON_8 = 8;
		static const int BUTTON_9 = 9;
		static const int BUTTON_10 = 10;
		static const int BUTTON_11 = 11;
		
		static const int X = 1;
		static const int Y = 2;
		static const int DIAL = 3;
		
	private:
		Joystick *joystick_;
				
		bool oldBtnStates[ MAX_NUM_BUTTONS ];
		bool newBtnStates[ MAX_NUM_BUTTONS ];
		bool upEventStates[ MAX_NUM_BUTTONS ];
		bool downEventStates[ MAX_NUM_BUTTONS ];

};

#endif

