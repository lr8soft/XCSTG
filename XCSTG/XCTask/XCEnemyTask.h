#pragma once
#ifndef _XCENEMYTASK_H_
#define _XCENEMYTASK_H_
#include "XCTask.h"
#include "../XCGame/Enemy/XCEnemyBase.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
#include <map>
class XCEnemyTask:public XCTask
{
protected:
	/*bool task_should_run = false,task_should_delete=false,have_resource_init=false;
	  int taskType= DefaultType;*/

	XCTaskCollisionInfo* pCollisonInfo=nullptr;//
	bool have_add_enemy_to_vec = false;
	/*          优先度(0~MAX)  ptr to XCEnemy，优先度越趋0，越先被渲染*/
	std::multimap<int, xc_game::XCEnemyBase*> pEnemyMap;
	int render_priority = 0;//从优先度0开始渲染
	void AddEnemyToMap(int priority, xc_game::XCEnemyBase* ptr) {
		pEnemyMap.insert(std::make_pair(priority,ptr));
	}
	bool TaskPriorityRender(float nowframe) {
		bool no_same_priority_enemy=true,nothing_to_render=true;
		auto end_iter = pEnemyMap.end();
		for (auto iter = pEnemyMap.begin(); iter != end_iter; iter++)
		{
			if (iter->second->IsRendering()) {//仍有要渲染的
				nothing_to_render = false;//并不是没有要渲染的
				if (iter->first == render_priority) {//相同优先度
					iter->second->EnemyRender(nowframe);
					if (iter->second->GetEnemyType() == BOSS_ENEMY)
						pCollisonInfo->nowRenderBoss =static_cast<xc_game::XCBoss*>(iter->second);
					no_same_priority_enemy = false;//即：仍有 该优先度 的敌人 正被渲染
				}
			}
		}
		if (no_same_priority_enemy) {
			render_priority++;//渲染后一优先度
		}
		return nothing_to_render;
	}
public:
	XCEnemyTask() {
		taskType = EnemyType;
	}
	virtual void TaskInit() = 0;
	/*缺省渲染方法*/
	virtual void TaskRender(XCTaskRenderInfo * pInfo) override {
		task_should_delete = TaskPriorityRender(pInfo->nowFrame);//任务完成，自动删除
	}
	/*默认添加到EnamyGroup方法*/
	virtual void AddEnemyToTaskLoop(XCTaskCollisionInfo* pInfo) {
		if (!have_add_enemy_to_vec) {
			pCollisonInfo = pInfo;
			for(auto iter= pEnemyMap.begin();iter!= pEnemyMap.end();iter++)
			{
				pInfo->EnemyInfoGroup.AddEnemyToVector(iter->second);
			}
			have_add_enemy_to_vec = true;
		}
	}
	virtual void TaskRelease() {
		auto end_iter = pEnemyMap.end();
		for (auto iter = pEnemyMap.begin(); iter != end_iter; iter++) {
			iter->second->SetDead();
			if (have_add_enemy_to_vec) {
				pCollisonInfo->EnemyInfoGroup.RemoveEnemyFromVector(iter->second);
				if (iter->second->GetEnemyType() == BOSS_ENEMY)
					pCollisonInfo->nowRenderBoss = nullptr;
			}
			iter->second->ReleaseResource();
		}
		have_add_enemy_to_vec = false;
	}
};
#endif