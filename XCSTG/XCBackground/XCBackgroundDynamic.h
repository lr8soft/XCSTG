#pragma once
#ifndef _XCBACKGROUND_DYNAMIC_H_
#define _XCBACKGROUND_DYNAMIC_H_
#include "XCBackground.h"
#include "../XCScene/XCScene.h"
class XCBackgroundDynamic:public XCBackground {
protected:
	XCScene *pScene = nullptr;
	virtual void ShaderInit() override;
	virtual void TextureInit() override;
	virtual void BufferInit() override;
public:
	XCBackgroundDynamic();
	void SetBackGroundScene(XCScene *ptrs);
	virtual void BackgroundInit() override;
	virtual void BackgroundRender(float nowFrame) override;
	virtual void BackgroundRelease() override;
};
#endif