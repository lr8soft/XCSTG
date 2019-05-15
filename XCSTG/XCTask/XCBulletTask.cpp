#include "XCBulletTask.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace xc_bullet;
XCBulletTask::XCBulletTask()
{
	taskType = BulletType;
	pBulletCount = 16;
}
void XCBulletTask::TaskInit()
{
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
			((XCCircleBullet*)pBullet)[i].SetVelocity(1.0f);
			((XCCircleBullet*)pBullet)[i].SetMoveFunc(xfunc, yfunc);
			((XCCircleBullet*)pBullet)[i].SetStartingPoint(0.0f, 0.1f*i, 0.0f);
			((XCCircleBullet*)pBullet)[i].BulletInit();
		}
		have_resource_init = true;
	}
}

void XCBulletTask::TaskRender(XCTaskRenderInfo * pInfo)
{
	for (int i = 0; i < pBulletCount; i++) {
		((XCCircleBullet*)pBullet)[i].BulletRender(pInfo->nowFrame);
	}
}

void XCBulletTask::TaskCollisionCheck(XCTaskCollisionInfo * pInfo)
{
#pragma omp parallel for
	for (int i = 0; i < pBulletCount; i++) {
		((XCCircleBullet*)pBullet)[i].BulletCollisionWithPlayer(pInfo->pPlayer);
	}
}

void XCBulletTask::TaskKeyCheck(GLFWwindow * win)
{
}
