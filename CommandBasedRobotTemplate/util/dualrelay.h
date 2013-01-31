#ifndef DUAL_RELAY_H
#define DUAL_RELAY_H

#include "WPILib.h"

class DualRelay {
	public:
		DualRelay( UINT8 forwardPort, UINT8 reversePort );
		~DualRelay(){};
		
		void Set( Relay::Value value );
	private:
		Relay *forward;
		Relay *reverse;
};


#endif
