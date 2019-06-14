#pragma once
#ifndef _XCMOUNTAINSSCENE_H_
#define _XCMOUNTAINSSCENE_H_
#include "XCScene.h"
class XCMountainScene: public XCScene {
protected:
	float NowX = 0.0f, NowY = 80.0f, NowZ = 10.0f;
	/*
	XCCamera *pCamera = nullptr;
	XCModel *sceneModel = nullptr;
	XCGameTimer sceneTimer;
	*/
public:
	virtual void SceneInit();
	virtual void SceneRender(float nowFrame);
	virtual void SceneRelease();
};
#endif