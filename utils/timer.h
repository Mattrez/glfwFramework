#ifndef TIMER_H
#define TIMER_H

#include "utils/GLIncludes.h"

class Timer
{
public:
	Timer();

	void setDeltaTime();

	double getDeltaTime() const;
private:
	double currentTime;
	double lastTime;
	double deltaTime;
};

#endif
