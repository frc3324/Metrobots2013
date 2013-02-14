#include "vision.h"
#include "WPILib.h"

Vision::Vision() {
	NetworkTable::SetServerMode();
	NetworkTable::Initialize();
	net = NetworkTable::GetTable("net");
}

Vision* Vision::GetInstance() {
	if( instance == NULL ){
		instance = new Vision();
	}
	return instance;
}

bool Vision::HasTarget() {
	return true;
}

double Vision::GetAngleOffset() {
	
}

double Vision::GetDistance() {
	return net->GetNumber("test", 0);
}

void Vision::Update() {
	
}



