#pragma once
#ifndef _XCBOSSTASK_H_
#define _XCBOSSTASK_H_
#include "XCTask.h"
#include "../XCGame/Enemy/XCBoss.h"
#include "../XCSpellCard/XCSpellCard.h"
#include <vector>
#include <map>
class XCBossTask :public XCTask {
protected:
	/*bool task_should_run = false,task_should_delete=false,have_resource_init=false; int taskType;*/
	bool have_add_boss_to_vec=false;
	xc_game::XCBoss* pTaskBoss=nullptr;
	/*Boss所使用的符卡*/
	std::vector<XCSpellCard*> spellCardGroup;
	/*每张符卡所对应的boss血量*/
	std::vector<float> bossSpellCardHP;
	/*Boss指针*/
	xc_game::XCBoss* ptrBoss;
	XCSpellCard* nowWorkingSC=nullptr;
	std::string bossTaskUUID;
	XCTaskRenderInfo* pRenderInfo=nullptr;
	XCTaskCollisionInfo* pCollisionInfo = nullptr;
	void AddEnemyToMap(int priority, xc_game::XCBoss* ptr) {
		ptrBoss = ptr;
	}
	void WorkSpellCardRender(float nowFrame)
	{
		if (spellCardGroup.empty()) task_should_delete = true;
		pTaskBoss->EnemyRender(nowFrame);

		auto now_hp_iter = bossSpellCardHP.begin();
		for (auto iter = spellCardGroup.begin(); iter != spellCardGroup.end(),now_hp_iter!= bossSpellCardHP.end();) {
			if (!(*iter)->GetIsActive()) {
				ptrBoss->SetInfo((*now_hp_iter), (*now_hp_iter));
			}
			(*iter)->SpellCardRun(nowFrame);
			nowWorkingSC = (*iter);
			if (pTaskBoss->IsDead()) {
				(*iter)->SpellCardRelease();
				if (next(iter) != spellCardGroup.end()) {
					iter=spellCardGroup.erase(iter);
					now_hp_iter = bossSpellCardHP.erase(now_hp_iter);
				}
				else {
					spellCardGroup.erase(iter);
					bossSpellCardHP.erase(now_hp_iter);
					break;//没了还做啥
				}
			}
			else {
				iter++;
				now_hp_iter++;
			}
			break;
		}
	}
public:
	XCBossTask() 
	{
		taskType = BossType;
	}
	virtual void TaskKeyCheck(GLFWwindow* win) {
		;
	}
	virtual void TaskInit() = 0;
	virtual void TaskRender(XCTaskRenderInfo* pInfo) {
		pRenderInfo = pInfo;
		if (pRenderInfo->workBossUUID == bossTaskUUID)
		{
			WorkSpellCardRender(pInfo->nowFrame);
		}
	}
	virtual void TaskRelease()
	{
		spellCardGroup.clear();
	}
	virtual void TaskCollisionCheck(XCTaskCollisionInfo * pInfo) override {
		if (nowWorkingSC == nullptr) return;
		pCollisionInfo = pInfo;
		nowWorkingSC->SpellCardCollisonCheck(pInfo);
	}
	void AddSpellCardToTask(XCSpellCard* psc,float hp) {
		spellCardGroup.push_back(psc);
		bossSpellCardHP.push_back(hp);
	}
	void AddEnemyToTaskLoop(XCTaskCollisionInfo* pInfo) {
		if (!have_add_boss_to_vec) {
			pCollisionInfo = pInfo;
			pInfo->EnemyInfoGroup.AddEnemyToVector(ptrBoss);
			have_add_boss_to_vec = true;
		}
	}
};
#endif