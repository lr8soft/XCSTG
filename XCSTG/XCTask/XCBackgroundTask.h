#pragma once
#ifndef _XCBACKGROUNDTASK_H_
#define _XCBACKGROUNDTASK_H_
#include "XCTask.h"
#include "../XCBackground/XCBackground.h"
#include <vector>
class XCBackgroundTask :public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,have_resource_init=false; int taskType;*/
	std::vector<XCBackground*> backGroundGroup;
public:
	XCBackgroundTask() {
		taskType = BackgroundType;
	}
	virtual void TaskInit() 
	{
		if (!have_resource_init) {
			for (auto iter = backGroundGroup.begin(); iter != backGroundGroup.end(); iter++) {
				(*iter)->BackgroundInit();
			}
			have_resource_init = true;
		}
	}
	virtual void TaskRender(XCTaskRenderInfo* pInfo) 
	{
		for (auto iter = backGroundGroup.begin(); iter != backGroundGroup.end(); iter++) {
			if((*iter)->IsBackGroundRender()){
				(*iter)->BackgroundRender(); break;//一次只渲染一个
			}
			else {
				if (std::next(iter)!= backGroundGroup.end()) {
					(*iter)->BackgroundRelease();
					iter=backGroundGroup.erase(iter);
				}
				else {
					(*iter)->BackgroundRelease();
					backGroundGroup.erase(iter);
					break;
				}
			}
		}
	}
	virtual void TaskCollisionCheck(XCTaskCollisionInfo* pInfo) {
		;//None
	}
	virtual void TaskKeyCheck(GLFWwindow* win) {
		;//None
	}
	virtual void TaskRelease() {
		if(!backGroundGroup.empty())
			for (auto iter = backGroundGroup.begin(); iter != backGroundGroup.end(); iter++) 
			{
				if (std::next(iter) != backGroundGroup.end()) {
					(*iter)->BackgroundRelease();
					iter = backGroundGroup.erase(iter);
				}
				else {
					(*iter)->BackgroundRelease();
					backGroundGroup.erase(iter);
					break;
				}
			}
	}
};
#endif