#include "XCBackgroundDynamic.h"

void XCBackgroundDynamic::ShaderInit()
{
	;
}

void XCBackgroundDynamic::TextureInit()
{
	;
}

void XCBackgroundDynamic::BufferInit()
{
	;
}

XCBackgroundDynamic::XCBackgroundDynamic()
{
	backgroundType = DYNAMIC_Background;
}

void XCBackgroundDynamic::SetBackGroundScene(XCScene * ptrs)
{
	pScene = ptrs;
}

void XCBackgroundDynamic::BackgroundInit()
{
	if (pScene!=nullptr) {
		pScene->SceneInit();
	}
	
}

void XCBackgroundDynamic::BackgroundRender(float nowFrame)
{
	if (pScene != nullptr) {
		pScene->SceneRender(nowFrame);
	}
}

void XCBackgroundDynamic::BackgroundRelease()
{
	if (pScene != nullptr) {
		pScene->SceneRelease();
		delete pScene;
	}
}
