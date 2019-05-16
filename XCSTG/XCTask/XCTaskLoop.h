#pragma once
#ifndef _XCTASK_LOOP_H_
#define _XCTASK_LOOP_H_
#include<map>
#include<vector>
#include<iostream>
#include "XCTask.h"
class XCTaskLoop {
protected:	/*UUID   Task*/
	std::map<std::string, XCTask*> tasklist;
	std::vector<int> taskCommandList;
	size_t taskCount=0;
	XCTaskCollisionInfo CollisionInfo;
	XCTaskRenderInfo RenderInfo;
	XCTask* pPlayerTask=nullptr,*pEnemyTask=nullptr;
	void SetPlayer(XCTask* ptask);
	void SetEnemy(XCTask* ptask);
	void SetBullet(XCTask* ptask);
public:
	enum TaskCommand {COMMAND_NONE,CLEAN_ENEMY,CLEAN_BULLET,STAGE_INIT,STAGE_RENDER,STAGE_END};

	void SetScreen(GLFWwindow* screen);
	void AddTask(XCTask* task,std::string uuid);
	void DeleteTask(std::string uuid);
	void ActiveTask(std::string uuid);
	void TaskProcess(float nowFrame);
	void TaskProcessCommand(int command);
};
#endif