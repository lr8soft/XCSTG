#pragma once
#ifndef _XCEYSTAGE1_H_
#define _XCEYSTAGE1_H_
#include "../XCTask/XCEnemyTask.h"
class XCEYStage1:public XCEnemyTask
{
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
	  int taskType= DefaultType;*/

public:
	~XCEYStage1();
	void TaskInit() override;
	void TaskRender(XCTaskRenderInfo* pInfo) override;
	void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) override;
	void TaskKeyCheck(GLFWwindow* win) override;
	/*Default function*/
	/*void AddEnemyToTaskLoop(XCTaskCollisionInfo* pInfo);*/
};
#endif