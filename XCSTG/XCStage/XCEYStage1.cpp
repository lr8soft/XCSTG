#include "XCEYStage1.h"
#include "../XCGame/Enemy/XCNormalEnemy.h"
#include "../XCGame/Enemy/Boss/XCTestBoss.h"
xc_game::XCNormalEnemy *pEnemy;
void XCEYStage1::TaskInit()
{
	int pEnemyCount = 4;
	auto xfunc = [](float NowX,float NowY,XCGameTimer timer,float v,float b) {
		return sin(timer.getAccumlateTime());
	};
	auto yfunc = [](float NowX, float NowY,XCGameTimer timer, float v, float b) {
		return cos(timer.getAccumlateTime());
	};
	if (!have_resource_init) 
	{
		pEnemy = new xc_game::XCNormalEnemy[pEnemyCount];//!!!!!这里没有delete的
		for (int i = 0; i < pEnemyCount; i++)
		{
			/*pEnemy[i].EnemyInit(pEnemy[i].SINGLE_COORD);
			if (i % 2 == 0) {
				pEnemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.03f);
				this->AddEnemyToMap(0,&pEnemy[i]);
			}	
			else if (i % 3 == 0) {
				pEnemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.03f);
				this->AddEnemyToMap(1, &pEnemy[i]);
			}
			
			else if (i % 5 == 0) {
				pEnemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.03f);
				this->AddEnemyToMap(2, &pEnemy[i]);
			}
			else {
				pEnemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f,0.03f);
				this->AddEnemyToMap(3, &pEnemy[i]);
			}*/
			pEnemy[i].SetVelocity(0.3f);
			pEnemy[i].SetMoveFunc(xfunc, yfunc);
			if (i % 2 == 0) {
				pEnemy[i].SetStartPoint(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
				this->AddEnemyToMap(0, &pEnemy[i]);
			}
			else if (i % 3 == 0) {
				pEnemy[i].SetStartPoint(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
				this->AddEnemyToMap(1, &pEnemy[i]);
			}

			else if (i % 5 == 0) {
				pEnemy[i].SetStartPoint(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
				this->AddEnemyToMap(2, &pEnemy[i]);
			}
			else {
				pEnemy[i].SetStartPoint(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
				this->AddEnemyToMap(3, &pEnemy[i]);
			}
			pEnemy[i].EnemyInit(pEnemy[i].FUNCTION_PATH);
		}
		have_resource_init = true;
	}
}

void XCEYStage1::TaskRender(XCTaskRenderInfo * pInfo)
{
	TaskInit();
	XCEnemyTask::TaskRender(pInfo);
	if (task_should_delete)
		pInfo->workBossUUID = "TESTBOSS0";
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

