#pragma once
#ifndef _XCTASK_H_
#define _XCTASK_H_
#include "XCTaskCollisonInfo.h"
#include "XCTaskRenderInfo.h"
#include <GLFW/glfw3.h>
class XCTask {
protected:
	bool task_should_run = false;
public:
	enum TaskType { BulletType, PlayerType, EnemyType, AttackType };
	virtual void TaskInit() = 0;
	virtual void TaskRender(XCTaskRenderInfo* pInfo) = 0;
	virtual void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) = 0;
	virtual void TaskKeyCheck(GLFWwindow* win) = 0;
	void TaskActive() 
	{
		task_should_run = true;
	}
	bool TaskRunnable() 
	{
		return task_should_run;
	}
};
#endif