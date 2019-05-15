#pragma once
#ifndef _XCTASK_RENDER_INFO_
#define _XCTASK_RENDER_INFO_
class XCTaskRenderInfo {
public:
	long count = 0;
	float deltaTime,lastFrame,nowFrame;
	void* pScreen;
};
#endif