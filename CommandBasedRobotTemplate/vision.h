#ifndef VISION_H
#define VISION_H

#include "WPILib.h"

class Vision{
  public:
	bool HasTarget();
	double GetAngleOffset();
	double GetDistance();
	void Update();
	static Vision GetInstance();
  private:
	NetworkTable *net;
	Vision *instance;
  protected:
	Vision();
};

#endif
