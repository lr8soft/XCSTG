#include <string>
#include "XCTaskLoop.h"
#include "XCPlayerTask.h"
#include "XCEnemyTask.h"
#include "XCBulletTask.h"
using namespace std;
void XCTaskLoop::SetScreen(GLFWwindow * screen)
{
	RenderInfo.pScreen = static_cast<void*>(screen);
}

void XCTaskLoop::SetPlayer(XCTask* ptask)
{
	pPlayerTask = ptask;
	CollisionInfo.pPlayer = ((XCPlayerTask*)ptask)->GetPlayerPointer();
}

void XCTaskLoop::SetEnemy(XCTask * ptask)
{
	pEnemyTask = ptask;
	((XCEnemyTask*)ptask)->TaskInit();
	((XCEnemyTask*)ptask)->AddEnemyToTaskLoop(&CollisionInfo);
	//CollisionInfo.AllEnemyInfo
}

void XCTaskLoop::SetBullet(XCTask * ptask)
{
	((XCBulletTask*)ptask)->TaskInit();
}

void XCTaskLoop::TaskProcessCommand(int command)
{

}

void XCTaskLoop::AddTask(XCTask * task, std::string uuid)
{
	tasklist[uuid] = task;
	switch (task->GetTaskType())
	{
	case task->PlayerType:
		SetPlayer(task);
		break;
	case task->AttackType:
		break;
	case task->BulletType:
		SetBullet(task);
		break;
	case task->EnemyType:
		SetEnemy(task);
		break;
	}
	taskCount++;
}

void XCTaskLoop::DeleteTask(std::string uuid)
{
	tasklist.erase(uuid);
}

void XCTaskLoop::ActiveTask(std::string uuid)
{
	auto taskIter = tasklist.find(uuid);
	if (taskIter != tasklist.end()) 
	{
		taskIter->second->TaskInit();
		taskIter->second->TaskActive();
	}

}

void XCTaskLoop::TaskProcess(float nowFrame)
{
	RenderInfo.nowFrame = nowFrame;
	RenderInfo.deltaTime = RenderInfo.nowFrame - RenderInfo.lastFrame;
	RenderInfo.lastFrame = RenderInfo.nowFrame;
	for (auto iter = tasklist.begin(); iter != tasklist.end();) {
		auto uuid = iter->first;
		auto ptask = iter->second;
		if (ptask->TaskRunnable()) 
		{
			ptask->TaskCollisionCheck(&CollisionInfo);
			ptask->TaskKeyCheck(static_cast<GLFWwindow*>(RenderInfo.pScreen));
			ptask->TaskRender(&RenderInfo);
			if (ptask->TaskDeletable()) 
			{
				tasklist.erase(iter++);
				continue;
			}
		}
		iter++;
	}
}
