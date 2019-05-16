#include "XCBTStage1.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace xc_bullet;
void XCBTStage1::TaskInit()
{
	pBulletCount = 500;
	if (!have_resource_init)
	{
		pBullet = new xc_bullet::XCCircleBullet[pBulletCount];
		auto xfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
			float ret_x, sint = sin(glfwGetTime());
			float positive = sint / abs(sint);
			ret_x = NowX + positive * deltaTime*v / 3;
			return ret_x;
		};
		auto yfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
			return NowY;
		};
		for (int i = 0; i < pBulletCount; i++) {
			((XCCircleBullet*)pBullet)[i].SetRotateAngle(1440.0f);
			((XCCircleBullet*)pBullet)[i].SetVelocity(0.5f);
			((XCCircleBullet*)pBullet)[i].SetMoveFunc(xfunc, yfunc);
			((XCCircleBullet*)pBullet)[i].SetStartingPoint( 0.001*i-0.5, 0.6f, 0.0f);
			//((XCCircleBullet*)pBullet)[i].SetAimToPlayer(true);
			if (i % 2 == 0)
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].LARGEISH);
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
