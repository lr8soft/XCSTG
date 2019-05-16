#pragma once
#ifndef _XCENEMYTASK_H_
#define _XCENEMYTASK_H_
#include "XCTask.h"
#include "../XCGame/Enemy/XCNormalEnemy.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
class XCEnemyTask:public XCTask
{
protected:
	/*bool task_should_run = false,task_should_delete=false,,have_resource_init=false;
	  int taskType= DefaultType;*/
	bool have_add_enemy_to_vec = false;
	xc_game::XCEnemy *pEnemy;
	long pEnemyCount = 0;
public:
	XCEnemyTask() {
		taskType = EnemyType;
	}
	virtual void TaskInit() = 0;
	/*缺省渲染方法*/
	virtual void TaskRender(XCTaskRenderInfo * pInfo) override {
		bool should_task_delete_temp = true;
		for (int i = 0; i < pEnemyCount; i++)
		{
			pEnemy[i].EnemyRender(pInfo->nowFrame);
			if(pEnemy[i].IsRendering())
				should_task_delete_temp = false;
		}
		task_should_delete = should_task_delete_temp;//任务完成，自动删除
	}
	/*默认添加到EnamyGroup方法*/
	virtual void AddEnemyToTaskLoop(XCTaskCollisionInfo* pInfo) {
		if (!have_add_enemy_to_vec) {
			for (int i = 0; i < pEnemyCount; i++)
			{
				pInfo->EnemyInfoGroup.AddEnemyToVector(&pEnemy[i]);
			}
			have_add_enemy_to_vec = true;
		}
	}
};
#endif