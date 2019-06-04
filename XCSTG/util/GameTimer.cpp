#include "GameTimer.h"
#include <glfw/glfw3.h>
void XCGameTimer::Tick()
{
	if (!FirstRun) {
		nowFrame = glfwGetTime();
		deltaFrame = (nowFrame - lastTime)*increaseRate;
		lastTime += deltaFrame;
	}
	else {
		nowFrame = glfwGetTime();
		deltaFrame = 0;
		lastTime = nowFrame;
		lastFpsUpdate = lastTime;
		FirstRun = false;
	}
	frameCounter++;
	if (lastTime - lastFpsUpdate >= 1) {
		lastFpsUpdate = lastTime;
		fpsNow = frameCounter;
		frameCounter = 0;
	}
	accumulateTime += deltaFrame;
}

void XCGameTimer::Tick(float update_nowFrame)
{
	if (!FirstRun) {
		nowFrame = update_nowFrame;
		deltaFrame = (nowFrame - lastTime)*increaseRate;
		lastTime += deltaFrame;
	}
	else {
		nowFrame = update_nowFrame;
		deltaFrame = 0;
		lastTime = nowFrame;
		lastFpsUpdate = lastTime;
		FirstRun = false;
	}
	frameCounter++;
	if (lastTime - lastFpsUpdate >= 1) {
		lastFpsUpdate = lastTime;
		fpsNow = frameCounter;
		frameCounter = 0;
	}
	accumulateTime += deltaFrame;
}

void XCGameTimer::SetIncreaseRate(float rate)
{
	increaseRate = rate;
}

void XCGameTimer::Clear()
{
	fpsNow = 0.0f;
	frameCounter = 0.0f;
	nowFrame = 0.0f;
	deltaFrame = 0.0f;
	lastTime = 0.0f;
	lastFpsUpdate = 0.0f;
	accumulateTime = 0.0;
	increaseRate = 1.0f;
	FirstRun = true;
}

float XCGameTimer::getNowFrame()
{
	return nowFrame;
}

float XCGameTimer::getDeltaFrame()
{
	return deltaFrame;
}

float XCGameTimer::getLastFrame()
{
	return lastTime;
}

float XCGameTimer::getFPS()
{
	return fpsNow;
}

double XCGameTimer::getAccumlateTime()
{
	return accumulateTime;
}
