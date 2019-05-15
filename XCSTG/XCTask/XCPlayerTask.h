#pragma once
#ifndef _XCPLAYERTASK_H_
#define _XCPLAYERTASK_H_
#include "XCTask.h"
#include "../RenderGroup/PlayerEntity.h"
class XCPlayerTask :public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
	int taskType= DefaultType;*/
	PlayerEntity *pPlayer;
public:
	XCPlayerTask();
	~XCPlayerTask();
	void TaskInit();
	void TaskRender(XCTaskRenderInfo* pInfo);
	void TaskCollisionCheck(XCTaskCollisionInfo* pInfo);
	void TaskKeyCheck(GLFWwindow* win);
	PlayerEntity * GetPlayerPointer();
};
#endif