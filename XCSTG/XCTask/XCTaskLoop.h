#pragma once
#ifndef _XCTASK_LOOP_H_
#define _XCTASK_LOOP_H_
#include<map>
#include<iostream>
#include "XCTask.h"
class XCTaskLoop {
protected:	/*UUID   Task*/
	std::map<std::string, XCTask*> tasklist;
	size_t taskCount=0;
	XCTaskCollisionInfo CollisionInfo;
	XCTaskRenderInfo RenderInfo;
public:
	enum TaskCommand {COMMAND_NONE,CLEAN_ENEMY,CLEAN_BULLET};

	void SetScreen(GLFWwindow* screen);
	void SetPlayer(PlayerRenderGroup* player);
	void AddTask(XCTask* task,std::string uuid);
	void DeleteTask(std::string uuid);
	void ActiveTask(std::string uuid);
	void TaskProcess();
};
#endif