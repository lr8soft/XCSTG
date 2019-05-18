#include "XCPlayerTask.h"

XCPlayerTask::XCPlayerTask()
{
	taskType = PlayerType;
	pPlayer = new PlayerEntity;
}

XCPlayerTask::~XCPlayerTask()
{
	delete pPlayer;
}

void XCPlayerTask::TaskInit()
{
	if (!have_resource_init)
	{
		pPlayer->GroupInit();
		have_resource_init = true;
	}
}

void XCPlayerTask::TaskRender(XCTaskRenderInfo * pInfo)
{
	TaskInit();
	pPlayer->GroupRender(pInfo->nowFrame);
	
}

void XCPlayerTask::TaskCollisionCheck(XCTaskCollisionInfo * pInfo)
{
	pPlayer->PlayerCollisonEvent(&(pInfo->EnemyInfoGroup));
}

void XCPlayerTask::TaskKeyCheck(GLFWwindow * win)
{
	pPlayer->GroupKeyCheck(win);
}

void XCPlayerTask::TaskRelease()
{
	; 
}

PlayerEntity * XCPlayerTask::GetPlayerPointer()
{
	return pPlayer;
}
