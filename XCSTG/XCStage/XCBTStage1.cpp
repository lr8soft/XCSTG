#include "XCBTStage1.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace xc_bullet;
void XCBTStage1::TaskInit()
{
	pBulletCount = 100;
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
			((XCCircleBullet*)pBullet)[i].SetRotateAngle(30.0f);
			((XCCircleBullet*)pBullet)[i].SetVelocity(0.5f);
			((XCCircleBullet*)pBullet)[i].SetMoveFunc(xfunc, yfunc);
			if (i % 2 == 0) {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].HUGE);
			}	
			else if (i % 3 == 0) {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].NORMAL);
			}
			else if (i % 5 == 0) {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].LARGEISH);
			}
			else {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].TINY);
			}
			((XCCircleBullet*)pBullet)[i].BulletInit();
		}
		have_resource_init = true;
	}
}

void XCBTStage1::TaskRender(XCTaskRenderInfo * pInfo)
{
	bool should_task_delete_temp = true;
	for (int i = 0; i < pBulletCount; i++) {
		((XCCircleBullet*)pBullet)[i].BulletRender(pInfo->nowFrame);
		if (((XCCircleBullet*)pBullet)[i].IsBulletRender())
			should_task_delete_temp = false;
	}
	task_should_delete = should_task_delete_temp;
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
