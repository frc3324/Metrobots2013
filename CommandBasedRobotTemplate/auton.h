#include "drive.h"
#include "shooter.h"

#include "WPILib.h"

struct StepCondition {
	double time;
	double xDist, yDist, angle;
};

struct ScriptStep{
	double shooterSetpoint;
	bool shooterPID;
	bool shootWhenSpunUp;
	bool loading;
	StepCondition condition;
};

struct Script{
	const ScriptStep *steps;
	int length;
};

static const ScriptStep shootScriptArray[] = {
	{Shooter::SETPOINT_RPM, true, true, false, {15.0, 0.0, 0.0, 0.0}}
};
Script shootScript = {&(shootScriptArray[0]), 1};
