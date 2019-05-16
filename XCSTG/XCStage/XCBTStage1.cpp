#include "XCBTStage1.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace xc_bullet;
void XCBTStage1::TaskInit()
{
	pBulletCount = 50;
	if (!have_resource_init)
	{
		pBullet = new xc_bullet::XCCircleBullet[pBulletCount];
		auto xfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
			float ret_x, sint = sin(glfwGetTime());
			float positive = sint / abs(sint);
			ret_x = NowX + positive * deltaTime*v / 3;
			return NowX;
		};
		auto yfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
			return NowY;// NowY- deltaTime /15.0f
		};
		for (int i = 0; i < pBulletCount; i++) {
			((XCCircleBullet*)pBullet)[i].SetRotateAngle(10.0f);
			((XCCircleBullet*)pBullet)[i].SetVelocity(0.5f);
			((XCCircleBullet*)pBullet)[i].SetMoveFunc(xfunc, yfunc);
			if (i % 2 == 0)
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
			else if (i % 3 == 0)
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
			else if (i % 5 == 0)
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
			else
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
			((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].HUGE);
			((XCCircleBullet*)pBullet)[i].BulletInit();
		}
		have_resource_init = true;
	}
}

void XCBTStage1::TaskRender(XCTaskRenderInfo * pInfo)
{
	for (int i = 0; i < pBulletCount; i++) {
	//	if(((XCCircleBullet*)pBullet)[i].ShouldAimToPlayer())
		((XCCircleBullet*)pBullet)[i].BulletRender(pInfo->nowFrame);
	}
}

void XCBTStage1::TaskCollisionCheck(XCTaskCollisionInfo * pInfo)
{
#pragma omp parallel for
	for (int i = 0; i < pBulletCount; i++) {
		((XCCircleBullet*)pBullet)[i].BulletCollisionWithPlayer(pInfo->pPlayer);
	}
}

void XCBTStage1::TaskKeyCheck(GLFWwindow * win)
{
}
