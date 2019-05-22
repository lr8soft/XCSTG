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
	/*          ���ȶ�(0~MAX)  ptr to XCEnemy�����ȶ�Խ��0��Խ�ȱ���Ⱦ*/
	std::multimap<int, xc_game::XCEnemyBase*> pEnemyMap;
	int render_priority = 0;//�����ȶ�0��ʼ��Ⱦ
	void AddEnemyToMap(int priority, xc_game::XCEnemyBase* ptr) {
		pEnemyMap.insert(std::make_pair(priority,ptr));
	}
	bool TaskPriorityRender(float nowframe) {
		bool no_same_priority_enemy=true,nothing_to_render=true;
		auto end_iter = pEnemyMap.end();
		for (auto iter = pEnemyMap.begin(); iter != end_iter; iter++)
		{
			if (iter->second->IsRendering()) {//����Ҫ��Ⱦ��
				nothing_to_render = false;//������û��Ҫ��Ⱦ��
				if (iter->first == render_priority) {//��ͬ���ȶ�
					iter->second->EnemyRender(nowframe);
					if (iter->second->GetEnemyType() == BOSS_ENEMY)
						pCollisonInfo->nowRenderBoss =static_cast<xc_game::XCBoss*>(iter->second);
					no_same_priority_enemy = false;//�������� �����ȶ� �ĵ��� ������Ⱦ
				}
			}
		}
		if (no_same_priority_enemy) {
			render_priority++;//��Ⱦ��һ���ȶ�
		}
		return nothing_to_render;
	}
public:
	XCEnemyTask() {
		taskType = EnemyType;
	}
	virtual void TaskInit() = 0;
	/*ȱʡ��Ⱦ����*/
	virtual void TaskRender(XCTaskRenderInfo * pInfo) override {
		task_should_delete = TaskPriorityRender(pInfo->nowFrame);//������ɣ��Զ�ɾ��
	}
	/*Ĭ����ӵ�EnamyGroup����*/
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