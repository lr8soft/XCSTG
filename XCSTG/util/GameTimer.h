#pragma once
#ifndef _XCGAME_TIMER_H_
#define _XCGAME_TIMER_H_
class XCGameTimer {
private:
	float nowFrame = 0.0f, deltaFrame = 0.0f, lastTime = 0.0f;
	long double accumulateTime = 0.0;
	bool FirstRun = true;
public:
	void Tick();
	void Tick(float nowFrame);
	void Clear();
	float getNowFrame();
	float getDeltaFrame();
	float getLastFrame();
	double getAccumlateTime();
};
#endif