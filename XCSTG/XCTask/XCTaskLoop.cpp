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
	((XCPlayerTask*)ptask)->TaskInit();
	CollisionInfo.pPlayer = ((XCPlayerTask*)ptask)->GetPlayerPointer();
}

void XCTaskLoop::SetEnemy(XCTask * ptask)
{
	pEnemyTask = ptask;
}

void XCTaskLoop::SetBullet(XCTask * ptask)
{
	ptask->TaskInit();
	pBulletTask = ptask;
}

void XCTaskLoop::TaskProcessCommand(int command)
{
	taskCommandList.push_back(command);
}

void XCTaskLoop::AddTask(XCTask * task, std::string uuid)
{
	tasklist.insert(std::make_pair(uuid,task));//Add task to tasklist
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
std::map<std::string, XCTask*>::iterator
XCTaskLoop::DoTaskCommmand(int command,std::map<std::string, XCTask*>::iterator &iter)
{
	if (COMMAND_NONE == command) return iter;//default的滚
	auto ptask = iter->second;
	switch (command) 
	{
		case CLEAN_ENEMY: 
			if (ptask->GetTaskType() == ptask->EnemyType) {
				if (next(iter) == tasklist.end())//您尾部就别++了亲
				{
					tasklist.erase(iter);
					iter = tasklist.begin();
				}
				else {
					tasklist.erase(iter++);
				}
			}
			break;
		case CLEAN_BULLET:
			if (ptask->GetTaskType() == ptask->BulletType) {
				if(next(iter)== tasklist.end())//同上
				{
					tasklist.erase(iter);
					iter = tasklist.begin();
				}
				else {
					tasklist.erase(iter++);
				}
			}
			break;
		case STAGE_INIT:
			if (!ptask->IsTaskInit()) {
				ptask->TaskInit();
				if(ptask->GetTaskType()==ptask->EnemyType)
					((XCEnemyTask*)ptask)->AddEnemyToTaskLoop(&CollisionInfo);
			}
			break;
		case STAGE_RENDER:
			ptask->TaskActive();
			break;
		case STAGE_END: 
			break;
		default:
			break;
	}
	return iter;
}
void XCTaskLoop::TaskProcess(float nowFrame)
{
	RenderInfo.nowFrame = nowFrame;
	RenderInfo.deltaTime = RenderInfo.nowFrame - RenderInfo.lastFrame;
	RenderInfo.lastFrame = RenderInfo.nowFrame;
	int temp_command = COMMAND_NONE;
	//////////////Time manager finish////////////////////////////
	if (!taskCommandList.empty())
	{
		auto command_iter = taskCommandList.begin();
		temp_command = (*command_iter);
		taskCommandList.erase(command_iter);
	}
	/////////////Command Manager finish///////////
	for (auto iter = tasklist.begin(); iter != tasklist.end();) {
		auto ret_iter=DoTaskCommmand(temp_command,iter);
		auto uuid = ret_iter->first;auto ptask = ret_iter->second;
		if (ptask->TaskRunnable()) 
		{
			if (ptask->IsTaskInit()) {
				ptask->TaskCollisionCheck(&CollisionInfo);
				ptask->TaskKeyCheck(static_cast<GLFWwindow*>(RenderInfo.pScreen));
				ptask->TaskRender(&RenderInfo);
				if (ptask->TaskDeletable())
				{
					if (next(iter) == tasklist.end())
					{
						tasklist.erase(iter);
						iter = tasklist.begin();
					}
					else {
						tasklist.erase(iter++);
					}
					continue;
				}
			}
		}
		iter++;
	}
	//////////////Sub running task finish////////////
}
