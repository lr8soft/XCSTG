#include <string>
#include "XCTaskLoop.h"
#include "XCPlayerTask.h"
#include "XCEnemyTask.h"
#include "XCBulletTask.h"
#include "XCBossTask.h"
#include "XCBackgroundTask.h"
#include <gl3/gl3w.h>
using namespace std;
bool XCTaskLoop::IsProcessing()
{
	return ShouldProcessRun;
}
void XCTaskLoop::SetIsReplay(bool isreplay)
{
	IsReplayMode = isreplay;
}
void XCTaskLoop::SetScreen(GLFWwindow * screen)
{
	RenderInfo.pScreen = static_cast<void*>(screen);
}

void XCTaskLoop::SetWidthHeight(float w, float h)
{
	RenderInfo.render_width = w;
	RenderInfo.render_height = h;

	RenderInfo.render_abs_width = game_width/w;
	RenderInfo.render_abs_height = game_height/h;
}

void XCTaskLoop::BeforeProcess()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void XCTaskLoop::SetPlayer(XCTask* ptask)
{
	pPlayerTask = ptask;
	CollisionInfo.pPlayer = ((XCPlayerTask*)ptask)->GetPlayerPointer();
}

void XCTaskLoop::SetEnemy(XCTask * ptask)
{
	pEnemyTask = ptask;
}

void XCTaskLoop::SetBullet(XCTask * ptask)
{
	pBulletTask = ptask;
}

void XCTaskLoop::SetBackground(XCTask * ptask)
{
	ptask->TaskInit();
}
void XCTaskLoop::TaskProcessCommand(int command)
{
	taskCommandList.push_back(command);
}

void XCTaskLoop::AddTask(XCTask * task, std::string priority)
{
	tasklist.insert(std::make_pair(priority,task));//Add task to tasklist
	switch (task->GetTaskType())
	{
	case task->PlayerType:
		SetPlayer(task);
		break;
	case task->BulletType:
		SetBullet(task);
		break;
	case task->EnemyType:
		SetEnemy(task);
		break;
	case task->BossType:
		break;
	case task->BackgroundType:
		SetBackground(task);
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
XCTaskLoop::DoTaskCommand(int command,std::map<std::string, XCTask*>::iterator &iter)
{
	if (COMMAND_NONE == command) return iter;//default的滚
	auto ptask = iter->second;
	switch (command) 
	{
		case CLEAN_ENEMY: 
			if (ptask->GetTaskType() == ptask->EnemyType) {
				iter->second->TaskRelease();
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
				iter->second->TaskRelease();
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
			renderGroup.CoveredPlaneInit();
			if (!ptask->IsTaskInit()) {
				ptask->SetIsReplay(IsReplayMode);
				ptask->SetAbsWidthAndHeight(RenderInfo.render_abs_height, RenderInfo.render_abs_width);
				ptask->TaskInit();
				switch (ptask->GetTaskType()) {
				case ptask->EnemyType:
					((XCEnemyTask*)ptask)->AddEnemyToTaskLoop(&CollisionInfo); break;
				case ptask->BossType:
					((XCBossTask*)ptask)->AddEnemyToTaskLoop(&CollisionInfo); break;
				}
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
void XCTaskLoop::DoExtraCommand(int command, std::map<std::string, XCTask*>::iterator &iter)
{
	if (command == (*iter).second->COMMAND_NONE) return;
	auto ptask = (*iter).second;
	switch (ptask->GetCommandExtra()) 
	{
	case ptask->NEXT_BACKGROUND:
		if (pBackgroundTask != nullptr) 
		{
			((XCBackgroundTask*)pBackgroundTask)->SetRenderNext();
		}
		break;
	}
	return;
}
void XCTaskLoop::TaskProcess(float nowFrame)
{
	RenderInfo.RenderTimer.Tick(nowFrame);
	int temp_command = COMMAND_NONE,last_core_command= COMMAND_NONE;
	//////////////Time manager finish////////////////////////////
	if (!taskCommandList.empty())
	{
		auto command_iter = taskCommandList.begin();
		temp_command = (*command_iter);
		taskCommandList.erase(command_iter);//delete old command
		//////Process core command/////
		last_core_command = temp_command;
		switch (temp_command) {
		case PROCESS_PAUSE:
			RenderInfo.RenderTimer.Pause();
			ShouldProcessRun = false;
			temp_command = COMMAND_NONE;
			break;
		case PROCESS_RESUME:
			RenderInfo.RenderTimer.Resume();
			ShouldProcessRun = true;
			have_font_show = false;
			temp_command = COMMAND_NONE;
			break;
		case PROCESS_CLEAN:
			tasklist.clear();
			temp_command = COMMAND_NONE;
			break;
		}
		//////Process core finish/////
	}
	/////////////Command Manager finish///////////
	if (ShouldProcessRun)
	{
		BeforeProcess();
		for (auto iter = tasklist.begin(); iter != tasklist.end();) {
			auto ret_iter = DoTaskCommand(temp_command, iter);
			auto uuid = ret_iter->first; auto ptask = ret_iter->second;
			if (ptask->TaskRunnable())
			{
				if (ptask->IsTaskInit()) {
					ptask->TaskCollisionCheck(&CollisionInfo);
					ptask->TaskKeyCheck(static_cast<GLFWwindow*>(RenderInfo.pScreen));
					ptask->TaskRender(&RenderInfo);
					DoExtraCommand(ptask->GetCommandExtra(), iter);
					if (ptask->GetTaskType() == ptask->BackgroundType) 
					{
						pBackgroundTask = ptask;
					}
					if (ptask->TaskDeletable())
					{
						iter->second->TaskRelease();//当场释放
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
		renderGroup.CoveredPlaneRender(RenderInfo.render_abs_width, RenderInfo.render_abs_height);
		if (last_core_command == PROCESS_RESUME) 
		{
			RenderInfo.RenderTimer.AfterResume();
		}
		
	}
	else {
		if (!have_font_show) {
			taskFont.FontUnicodeDirectRender(L"暂停",
				0.45f,
				0.5f,
				0.7f,
				glm::vec4(0.5f, 0.5f, 1.0f, 1.0f)
			);
			have_font_show = true;
		}

	}
	//////////////Sub running task finish////////////
}
