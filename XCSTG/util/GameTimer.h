#pragma once
#ifndef _XCGAME_TIMER_H_
#define _XCGAME_TIMER_H_
class XCGameTimer {
private:
	float nowFrame=0.0f,deltaFrame=0.0f,lastTime=0.0f;
	bool FirstRun = true;
public:
	void Tick();
	void Tick(float nowFrame);
	float getNowFrame();
	float getDeltaFrame();
	float getLastFrame();
};
#endif