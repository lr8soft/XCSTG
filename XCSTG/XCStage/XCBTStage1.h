#pragma once
#ifndef _XCBTSTAGE1_H_
#define _XCBTSTAGE1_H_
#include "../XCTask/XCBulletTask.h"
class XCBTStage1:public XCBulletTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
  int taskType= DefaultType;*/

public:
	void TaskInit() override;
	void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) override;
	void TaskKeyCheck(GLFWwindow* win) override;
};
#endif