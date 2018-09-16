#ifndef TIMER_H
#define TIMER_H

#include "utils/GLIncludes.h"

class Timer
{
public:
	Timer();

	void setDeltaTime();

	float getDeltaTime() const;
private:
	float currentTime;
	float lastTime;
	float deltaTime;
};

#endif
