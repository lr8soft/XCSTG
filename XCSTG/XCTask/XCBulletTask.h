#pragma once
#ifndef _XCBULLETTASK_H_
#define _XCBULLETTASK_H_
#include "XCTask.h"
#include "../XCBullet/XCBullet.h"
class XCBulletTask:public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
  int taskType= DefaultType;*/

	xc_bullet::XCBullet *pBullet;
	long pBulletCount = 0;
public:
	XCBulletTask();
	void TaskInit() override;
	void TaskRender(XCTaskRenderInfo* pInfo) override;
	void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) override;
	void TaskKeyCheck(GLFWwindow* win) override;
};
#endif