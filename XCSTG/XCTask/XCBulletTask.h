#pragma once
#ifndef _XCBULLETTASK_H_
#define _XCBULLETTASK_H_
#include "XCTask.h"
#include "../XCBullet/XCBullet.h"
#include <map>
class XCBulletTask:public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
  int taskType= DefaultType;*/
  /*          优先度(0~MAX)  ptr to XCEnemy，优先度越趋0，越先被渲染*/
	std::multimap<int, xc_bullet::XCBullet*> pBulletMap;
	int render_priority = 0;//从优先度0开始渲染
	void AddBulletToMap(int priority, xc_bullet::XCBullet* ptr) {
		pBulletMap.insert(std::make_pair(priority, ptr));
	}
	bool TaskPriorityRender(float nowframe) {
		bool no_same_priority_bullet = true, nothing_to_render = true;
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++)
		{
			if (iter->second->IsBulletRender()) {//仍有要渲染的
				nothing_to_render = false;//并不是没有要渲染的
				if (iter->first == render_priority) {//相同优先度
					iter->second->BulletRender(nowframe);
					no_same_priority_bullet = false;//即：仍有 该优先度 的弹幕 正被渲染
				}
			}
		}
		if (no_same_priority_bullet) {
			render_priority++;//渲染后一优先度
		}
		return nothing_to_render;
	}
public:
	XCBulletTask() {
		taskType = BulletType;
	}
	/*缺省渲染方法*/
	virtual void TaskRender(XCTaskRenderInfo * pInfo) override {
		task_should_delete = TaskPriorityRender(pInfo->nowFrame);//任务完成，自动删除
	}
	virtual void TaskRelease() {
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++) {
			iter->second->StopBulletWork();
			iter->second->BulletRelease();
		}
	}
	virtual void TaskCollisionCheck(XCTaskCollisionInfo * pInfo) override{
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++)
		{
			if (iter->second->IsBulletRender()) {
				if (iter->first == render_priority) {//正在渲染的该优先级弹幕，才能进行碰撞检测
					iter->second->BulletCollisionWithPlayer(pInfo->pPlayer);
				}
			}
		}
	}
};
#endif