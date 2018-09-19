#ifndef TIMER_H
#define TIMER_H

#include "utils/GLIncludes.h"

class Timer
{
public:
	Timer() = default;

	void setDeltaTime();

	float getDeltaTime() const;
private:
	float currentTime = 0.0f;
	float lastTime = 0.0f;
	float deltaTime = 0.0f;
};

#endif
