#pragma once
#ifndef _XCTASK_RENDER_INFO_
#define _XCTASK_RENDER_INFO_
#include <string>
class XCTaskRenderInfo {
public:
	long count = 0;
	float deltaTime,lastFrame,nowFrame;
	void* pScreen;
	std::string workBossUUID="";
};
#endif