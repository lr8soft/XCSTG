#pragma once
#ifndef _XCMOUNTAINSSCENE_H_
#define _XCMOUNTAINSSCENE_H_
#include "XCScene.h"
class XCMountainScene: public XCScene {
protected:
	/*
	XCCamera *pCamera = nullptr;
	XCModel *sceneModel = nullptr;
	XCGameTimer sceneTimer;
	*/
	
public:
	XCMountainScene();
	virtual void SceneInit();
	virtual void SceneRender(float nowFrame);
	virtual void SceneRelease();
};
#endif