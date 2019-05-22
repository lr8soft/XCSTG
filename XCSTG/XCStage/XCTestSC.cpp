#include "XCTestSC.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace xc_bullet;
void XCTestSC::SpellCardInit()
{
	XCCircleBullet *ptrBullet = new XCCircleBullet[256];
	auto xfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
		return NowX;
	};
	auto yfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
		if (NowY > -1.0)
			return NowY - v / 100;
		else
			return 1.0;
	};
	for (int i = 0; i < 128;i++) {
		ptrBullet[i].SetBulletType(ptrBullet[i].TINY);
		ptrBullet[i].SetMoveFunc(xfunc, yfunc);
		ptrBullet[i].SetRotateAngle(rand());
		ptrBullet[i].SetVelocity(0.5f);
		if (i % 2 == 0) {
			((XCCircleBullet*)ptrBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
		}
		else if (i % 3 == 0) {
			((XCCircleBullet*)ptrBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
		}
		else if (i % 5 == 0) {
			((XCCircleBullet*)ptrBullet)[i].SetStartingPoint(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
		}
		else {
			((XCCircleBullet*)ptrBullet)[i].SetStartingPoint(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
		}
		((XCCircleBullet*)ptrBullet)[i].BulletInit();
		pBullet.push_back(&ptrBullet[i]);
	}
}

void XCTestSC::SpellCardRun(float nowFrame)
{
	for (auto iter = pBullet.begin(); iter != pBullet.end(); iter++) {
		if (((XCCircleBullet*)*iter)->IsBulletRender())
			((XCCircleBullet*)*iter)->BulletRender(nowFrame);

	}
}

void XCTestSC::SpellCardRelease()
{
	XCSpellCard::SpellCardRelease();
}

void XCTestSC::SpellCardCollisonCheck(XCTaskCollisionInfo * pInfo)
{
	if (pInfo == nullptr) return;
	for (auto iter = pBullet.begin(); iter != pBullet.end(); iter++) {
		if (((XCCircleBullet*)*iter)->IsBulletRender())
			((XCCircleBullet*)*iter)->BulletCollisionWithPlayer(pInfo->pPlayer);

	}
}
