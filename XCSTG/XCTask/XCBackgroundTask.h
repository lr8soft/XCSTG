#pragma once
#ifndef _XCBACKGROUNDTASK_H_
#define _XCBACKGROUNDTASK_H_
#include "XCTask.h"
#include "../XCBackground/XCBackground.h"
#include <vector>
class XCBackgroundTask :public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,have_resource_init=false; int taskType;*/
	/*default is STATIC_TYPE*/
	int backgroundType = STATIC_TYPE;
	std::vector<XCBackground*> backGroundGroup;
public:
	enum BGType {DYNAMIC_TYPE , STATIC_TYPE};
	XCBackgroundTask() {
		taskType = BackgroundType;
	}
	void SetRenderNext() 
	{
		switch (backgroundType) {
		case STATIC_TYPE:
			if (!backGroundGroup.empty()) 
			{
				if (backGroundGroup.size() > 1) {
					auto iter = backGroundGroup.begin();
					(*iter)->SetBackGroundRender(false);
				}
			}
			break;
		case DYNAMIC_TYPE:
			break;
		}
	}
	virtual void TaskInit() 
	{
		if (!have_resource_init&&have_abs_bored_set) {
			for (auto iter = backGroundGroup.begin(); iter != backGroundGroup.end(); iter++) {
				(*iter)->SetAbsWidthAndHeight(render_abs_width, render_abs_height);
				(*iter)->BackgroundInit();
			}
			have_resource_init = true;
		}
	}
	virtual void TaskRender(XCTaskRenderInfo* pInfo) 
	{
		for (auto iter = backGroundGroup.begin(); iter != backGroundGroup.end(); iter++) {
			if((*iter)->IsBackGroundRender()){
				(*iter)->BackgroundRender(pInfo->RenderTimer.getNowFrame()); break;//一次只渲染一个
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