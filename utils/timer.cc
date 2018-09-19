#include "utils/timer.h"

/* Calls glfwGetTime to get total run time, and parse it to dTime */
void Timer::setDeltaTime()
{
	currentTime = static_cast <float> (glfwGetTime());
	deltaTime = currentTime - lastTime;
	lastTime = currentTime;
}

/* Getter */
float Timer::getDeltaTime() const { return deltaTime; }
