#pragma once
#ifndef _XCTESTBG_H_
#define _XCTESTBG_H_
#include "../XCTask/XCBackgroundTask.h"
#include "../XCBackground/XCBackgroundStatic.h"
#include <iostream>
class XCTestBG :public XCBackgroundTask {
protected:
	XCBackgroundStatic *pBG0,*pBG1;
public:
	XCTestBG() {
		pBG0 = new XCBackgroundStatic;
		pBG0->LoadBackGround("Image/bg/eff05.png");
		pBG1 = new XCBackgroundStatic;
		pBG1->LoadBackGround("Image/bg/eff06.png");
		backGroundGroup.push_back(pBG0);
		backGroundGroup.push_back(pBG1);
	}
	virtual void TaskKeyCheck(GLFWwindow* win) override {
		;
	}
	virtual void TaskRelease() override {
		XCBackgroundTask::TaskRelease();
		delete pBG0, pBG1;
	}
};
#endif