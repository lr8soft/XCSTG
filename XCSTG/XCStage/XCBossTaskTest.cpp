#include "XCBossTaskTest.h"
#include "../XCBullet/XCCircleBullet.h"
#include "../XCStage/XCTestSC.h"
#include "../XCGame/Enemy/Boss/XCTestBoss.h"
using namespace xc_bullet;
void TestBossTask::TaskInit()
{
	if (!have_resource_init) 
	{
		bossTaskUUID = "TESTBOSS0";
		XCTestSC *pSpellCard = new XCTestSC;
		pSpellCard->SetBorder(render_abs_height, -render_abs_height, -render_abs_width, render_abs_width);
		pSpellCard->SpellCardInit();
		XCTestSC *pSpellCard2 = new XCTestSC;
		pSpellCard2->SetBorder(render_abs_height, -render_abs_height, -render_abs_width, render_abs_width);
		pSpellCard2->SpellCardInit();
		AddSpellCardToTask(pSpellCard2, 50);
		AddSpellCardToTask(pSpellCard, 50);
		auto xfunc = [](float NowX, float NowY, XCGameTimer timer, float v, float b) {
			return NowX;
		};
		auto yfunc = [](float NowX, float NowY, XCGameTimer timer, float v, float b) {
			return NowY;
		};
		pTaskBoss = new TestBoss;
		((TestBoss*)pTaskBoss)->SetBoundingBox(render_abs_height, -render_abs_height, -render_abs_width, render_abs_width);
		((TestBoss*)pTaskBoss)->SetMoveFunc(xfunc, yfunc);
		((TestBoss*)pTaskBoss)->SetStartPoint(0.0f, 0.5f, 0.0f);
		((TestBoss*)pTaskBoss)->SetVelocity(3.0f);
		((TestBoss*)pTaskBoss)->EnemyInit(((TestBoss*)pTaskBoss)->FUNCTION_PATH);
		AddEnemyToMap(0, pTaskBoss);
		have_resource_init = true;
	}

}

void TestBossTask::TaskKeyCheck(GLFWwindow * win)
{
}

void TestBossTask::TaskRender(XCTaskRenderInfo * pInfo)
{
	if (have_resource_init) {
		XCBossTask::TaskRender(pInfo);
	}
}
