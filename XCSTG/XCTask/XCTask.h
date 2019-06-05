#pragma once
#ifndef _XCTASK_H_
#define _XCTASK_H_
#include "XCTaskCollisonInfo.h"
#include "XCTaskRenderInfo.h"
#include <GLFW/glfw3.h>
class XCTask {
protected:
	bool task_should_run = false,task_should_delete=false,have_resource_init=false,is_replay_mode=false;
	float render_abs_height, render_abs_width;
	int taskType,command_extra= COMMAND_NONE;
public:
	enum TaskType { DefaultType,BulletType, PlayerType, EnemyType, BossType, BackgroundType };
	enum ExtraCommand {COMMAND_NONE,NEXT_BACKGROUND };
	virtual void TaskInit() = 0;
	virtual void TaskRender(XCTaskRenderInfo* pInfo) = 0;
	virtual void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) = 0;
	virtual void TaskKeyCheck(GLFWwindow* win) = 0;
	virtual void TaskRelease() = 0;
	void TaskActive() 
	{
		task_should_run = true;
	}
	bool TaskRunnable() 
	{
		return task_should_run;
	}
	bool TaskDeletable() 
	{
		return task_should_delete;
	}
	bool IsTaskInit() 
	{
		return have_resource_init;
	}
	int GetTaskType() 
	{
		return taskType;
	}
	int GetCommandExtra() 
	{
		return command_extra;
	}
	void SetIsReplay(bool is) {
		is_replay_mode = is;
	}
	void SetAbsWidthAndHeight(float absH,float absW) {
		render_abs_height = absH;
		render_abs_width = absW;
	}
};

#endif