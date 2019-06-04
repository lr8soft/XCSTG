#pragma once
#ifndef _XCTASK_RENDER_INFO_
#define _XCTASK_RENDER_INFO_
#include <string>
struct XCTaskRenderInfo {
	long count = 0;
	void* pScreen;
	float deltaTime,lastFrame,nowFrame;
	float render_width, render_height;
	std::string workBossUUID="";
};
#endif