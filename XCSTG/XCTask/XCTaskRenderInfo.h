#pragma once
#ifndef _XCTASK_RENDER_INFO_
#define _XCTASK_RENDER_INFO_
#include <string>
#include "../util/GameTimer.h"
struct XCTaskRenderInfo {
	long count = 0;
	void* pScreen;
	XCGameTimer RenderTimer;
	float render_width, render_height;
	float render_abs_width=1.0f, render_abs_height=1.0f;
	std::string workBossUUID="";
};
#endif