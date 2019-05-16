#include "XCEYStage1.h"

XCEYStage1::~XCEYStage1()
{

}
void XCEYStage1::TaskInit()
{
	pEnemyCount = 64;
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

