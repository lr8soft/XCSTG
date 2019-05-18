#include "XCEYStage1.h"
xc_game::XCEnemy *pEnemy;
void XCEYStage1::TaskInit()
{
	int pEnemyCount = 100;
	if (!have_resource_init) 
	{
		pEnemy = new xc_game::XCEnemy[pEnemyCount];//!!!!!这里没有delete的
		for (int i = 0; i < pEnemyCount; i++)
		{
			pEnemy[i].EnemyInit(pEnemy[i].SINGLE_COORD);
			if (i % 2 == 0) {
				pEnemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
				this->AddEnemyToMap(0,&pEnemy[i]);
			}	
			else if (i % 3 == 0) {
				pEnemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
				this->AddEnemyToMap(1, &pEnemy[i]);
			}
			
			else if (i % 5 == 0) {
				pEnemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
				this->AddEnemyToMap(2, &pEnemy[i]);
			}
			else {
				pEnemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
				this->AddEnemyToMap(3, &pEnemy[i]);
			}
		}
		have_resource_init = true;
	}
}

void XCEYStage1::TaskRender(XCTaskRenderInfo * pInfo)
{
	TaskInit();
	XCEnemyTask::TaskRender(pInfo);
}

void XCEYStage1::TaskCollisionCheck(XCTaskCollisionInfo * pInfo)
{
	;
}

void XCEYStage1::TaskKeyCheck(GLFWwindow * win)
{
	;
}

void XCEYStage1::TaskRelease()
{
	if (have_resource_init) {
		XCEnemyTask::TaskRelease();
		delete[] pEnemy;
		pEnemyMap.clear();
	}

}

