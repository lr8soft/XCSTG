#include "XCBTStage1.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace xc_bullet;
xc_bullet::XCCircleBullet* pBullet;
void XCBTStage1::TaskInit()
{
	int pBulletCount = 100;
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
				this->AddBulletToMap(0,&pBullet[i]);
			}	
			else if (i % 3 == 0) {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].NORMAL);
				this->AddBulletToMap(1, &pBullet[i]);
			}
			else if (i % 5 == 0) {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].LARGEISH);
				this->AddBulletToMap(2, &pBullet[i]);
			}
			else {
				((XCCircleBullet*)pBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
				((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].TINY);
				this->AddBulletToMap(3, &pBullet[i]);
			}
			((XCCircleBullet*)pBullet)[i].BulletInit();
		}
		have_resource_init = true;
	}
}

void XCBTStage1::TaskCollisionCheck(XCTaskCollisionInfo * pInfo)
{
	auto end_iter = pBulletMap.end();
	for (auto iter = pBulletMap.begin(); iter != end_iter; iter++)
	{
		if (iter->second->IsBulletRender()) {
			if (iter->first == render_priority) {//正在渲染的该优先级弹幕，才能进行碰撞检测
				iter->second->BulletCollisionWithPlayer(pInfo->pPlayer);
			}
		}
	}
}

void XCBTStage1::TaskKeyCheck(GLFWwindow * win)
{
}

void XCBTStage1::TaskRelease()
{
	if (have_resource_init) {
		auto end_iter = pBulletMap.end();
		for (auto iter = pBulletMap.begin(); iter != end_iter; iter++) {
			iter->second->StopBulletWork();
		}
		delete[] pBullet;
		pBulletMap.clear();
		have_resource_init = false;
	}
	
}
