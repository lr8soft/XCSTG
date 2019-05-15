#include "XCEnemyTask.h"

XCEnemyTask::XCEnemyTask()
{
	taskType = EnemyType;
	pEnemyCount = 32;//default
}

XCEnemyTask::~XCEnemyTask()
{

}
void XCEnemyTask::TaskInit()
{
	if (!have_resource_init) 
	{
		pEnemy = new xc_game::XCEnemy[pEnemyCount];
		for (int i = 0; i < pEnemyCount; i++)
		{
			pEnemy[i].EnemyInit(pEnemy[i].SINGLE_COORD);
			if (i % 2 == 0)
				pEnemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			else if (i % 3 == 0)
				pEnemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			else if (i % 5 == 0)
				pEnemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			else
				pEnemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		}
		have_resource_init = true;
	}
}

void XCEnemyTask::TaskRender(XCTaskRenderInfo * pInfo)
{
	TaskInit();
	for (int i=0;i<pEnemyCount;i++) 
	{
		pEnemy[i].EnemyRender(pInfo->nowFrame);
	}
}

void XCEnemyTask::TaskCollisionCheck(XCTaskCollisionInfo * pInfo)
{
	;
}

void XCEnemyTask::TaskKeyCheck(GLFWwindow * win)
{
	;
}

void XCEnemyTask::AddEnemyToTaskLoop(XCTaskCollisionInfo * pInfo)
{
	if (!have_add_enemy_to_vec) {
		for (int i = 0; i < pEnemyCount; i++)
		{
			pInfo->EnemyInfoGroup.AddEnemyToVector(&pEnemy[i]);
		}
		have_add_enemy_to_vec = true;
	}
}
