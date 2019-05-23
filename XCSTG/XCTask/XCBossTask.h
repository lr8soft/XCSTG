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
	std::vector<XCSpellCard*> spellCardGroup;
	std::map<int,xc_game::XCBoss*> pBossMap;
	XCSpellCard* nowWorkingSC=nullptr;
	std::string bossTaskUUID;
	XCTaskRenderInfo* pRenderInfo=nullptr;
	XCTaskCollisionInfo* pCollisionInfo = nullptr;
	void AddEnemyToMap(int priority, xc_game::XCBoss* ptr) {
		pBossMap.insert(std::make_pair(priority, ptr));
	}
	void WorkSpellCardRender(float nowFrame)
	{
		if (spellCardGroup.empty()&&!pTaskBoss->IsRendering()) task_should_delete = true;
		if (!pTaskBoss->IsRendering()) task_should_delete = true;
		pTaskBoss->EnemyRender(nowFrame);
		for (auto iter = spellCardGroup.begin(); iter != spellCardGroup.end();) {
			(*iter)->SpellCardRun(nowFrame);
			nowWorkingSC = (*iter);
			if ((*iter)->IsFinish()) {
				(*iter)->SpellCardRelease();
				if (next(iter) != spellCardGroup.end()) {
					iter=spellCardGroup.erase(iter);
				}
				else {
					spellCardGroup.erase(iter);
					break;//没了还做啥
				}
			}
			else {
				iter++;
			}
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
	void AddEnemyToTaskLoop(XCTaskCollisionInfo* pInfo) {
		if (!have_add_boss_to_vec) {
			pCollisionInfo = pInfo;
			for (auto iter = pBossMap.begin(); iter != pBossMap.end(); iter++)
			{
				pInfo->EnemyInfoGroup.AddEnemyToVector(iter->second);
			}
			have_add_boss_to_vec = true;
		}
	}
};
#endif