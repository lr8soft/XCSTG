#pragma once
#ifndef _XCTESTBG_H_
#define _XCTESTBG_H_
#include "../XCTask/XCBackgroundTask.h"
#include "../XCBackground/XCBackgroundStatic.h"
#include "../XCBackground/XCBackgroundDynamic.h"
#include "../XCScene/XCMountainScene.h"
#include <iostream>
class XCTestBG :public XCBackgroundTask {
protected:
	XCBackgroundStatic *pBG;
	XCBackgroundDynamic *pMountains;
public:
	XCTestBG() {
		pMountains = new XCBackgroundDynamic;
		pMountains->SetBackGroundScene(new XCMountainScene);
		pBG = new XCBackgroundStatic;
		pBG->LoadBackGround("Image/bg/eff06.png");
		backGroundGroup.push_back(pMountains);
		backGroundGroup.push_back(pBG);
	}
	virtual void TaskKeyCheck(GLFWwindow* win) override {
		;
	}
	virtual void TaskRelease() override {
		XCBackgroundTask::TaskRelease();
		delete pBG, pMountains;
	}
};
#endif