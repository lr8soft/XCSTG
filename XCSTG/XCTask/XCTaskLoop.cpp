#include <string>
#include "XCTaskLoop.h"
using namespace std;
void XCTaskLoop::SetScreen(GLFWwindow * screen)
{
	RenderInfo.pScreen = static_cast<void*>(screen);
}

void XCTaskLoop::SetPlayer(PlayerRenderGroup * player)
{
	CollisionInfo.pPlayer = player;
}

void XCTaskLoop::AddTask(XCTask * task, std::string uuid)
{
	tasklist[uuid] = task;
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

void XCTaskLoop::TaskProcess()
{
	for (auto iter = tasklist.begin(); iter != tasklist.end();iter++) {
		auto uuid = iter->first;
		auto ptask = iter->second;
		if (ptask->TaskRunnable()) 
		{
			ptask->TaskRender(&RenderInfo);
			ptask->TaskCollisionCheck(&CollisionInfo);
			ptask->TaskKeyCheck(static_cast<GLFWwindow*>(RenderInfo.pScreen));
		}
	}
}
