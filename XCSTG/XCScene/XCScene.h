#pragma once
#ifndef _XCSCENE_H_
#define _XCSCENE_H_
#include "XCCamera.h"
#include "XCModel/XCModel.h"
#include "../util/GameTimer.h"
class XCScene {
protected:
	XCCamera *pCamera = nullptr;
	XCModel *sceneModel = nullptr;
	XCGameTimer sceneTimer;
public:
	virtual void SceneInit() = 0;
	virtual void SceneRender(XCCamera *camera, float nowFrame) = 0;
	virtual void SceneRelease() = 0;
};
#endif