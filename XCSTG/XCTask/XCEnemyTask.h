#pragma once
#ifndef _XCENEMYTASK_H_
#define _XCENEMYTASK_H_
#include "XCTask.h"
#include "../XCGame/Enemy/XCNormalEnemy.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
class XCEnemyTask:public XCTask
{
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
	  int taskType= DefaultType;*/
	bool have_add_enemy_to_vec = false;
	xc_game::XCEnemy *pEnemy;
	long pEnemyCount = 0;
public:
	XCEnemyTask();
	~XCEnemyTask();
	void TaskInit() override;
	void TaskRender(XCTaskRenderInfo* pInfo) override;
	void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) override;
	void TaskKeyCheck(GLFWwindow* win) override;
	void AddEnemyToTaskLoop(XCTaskCollisionInfo* pInfo);
};
#endif