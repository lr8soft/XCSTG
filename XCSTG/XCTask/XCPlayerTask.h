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
	void TaskInit() override;
	void TaskRender(XCTaskRenderInfo* pInfo) override;
	void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) override;
	void TaskKeyCheck(GLFWwindow* win) override;
	void TaskRelease() override;
	PlayerEntity * GetPlayerPointer();
};
#endif