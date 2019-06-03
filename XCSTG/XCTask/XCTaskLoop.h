#pragma once
#ifndef _XCTASK_LOOP_H_
#define _XCTASK_LOOP_H_
#include<map>
#include<vector>
#include<iostream>
#include "XCTask.h"
class XCTaskLoop {
protected:	/*UUID   Task*/
	bool IsReplayMode = false;
	std::map<std::string, XCTask*> tasklist;
	std::vector<int> taskCommandList;
	XCTaskCollisionInfo CollisionInfo;
	XCTaskRenderInfo RenderInfo;
	XCTask* pPlayerTask=nullptr,*pEnemyTask=nullptr,*pBulletTask=nullptr;
	void SetPlayer(XCTask* ptask);
	void SetEnemy(XCTask* ptask);
	void SetBullet(XCTask* ptask);
	std::map<std::string, XCTask*>::iterator DoTaskCommmand(int command,std::map<std::string, XCTask*>::iterator &iter);
public:
	enum TaskCommand {COMMAND_NONE,CLEAN_ENEMY,CLEAN_BULLET,STAGE_INIT,STAGE_RENDER,STAGE_END};
	void SetIsReplay(bool isreplay);
	void SetScreen(GLFWwindow* screen);
	void AddTask(XCTask* task,std::string uuid);
	void DeleteTask(std::string uuid);
	void ActiveTask(std::string uuid);
	void TaskProcess(float nowFrame);
	void TaskProcessCommand(int command);
};
#endif