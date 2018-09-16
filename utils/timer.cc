#include "utils/timer.h"

Timer::Timer() :
	currentTime(0.0),
	lastTime(0.0),
	deltaTime(0.0)
{ }

/* Calls glfwGetTime to get total run time, and parse it to dTime */
void Timer::setDeltaTime()
{
	currentTime = static_cast <float> (glfwGetTime());
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

/* Getter */
float Timer::getDeltaTime() const { return deltaTime; }
