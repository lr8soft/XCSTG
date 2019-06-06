#include "XCTestSC.h"
using namespace xc_bullet;
void XCTestSC::SpellCardInit()
{
	int init_count = 100;
	ptrCBullet = new XCCircleBullet[init_count];
	auto xfunc = [](float NowX, float NowY, XCGameTimer timer, float v, float w,float h)->float {
		return NowX;
	};
	auto yfunc = [](float NowX, float NowY, XCGameTimer timer, float v, float w, float h)->float {
		if (NowY > -h)
			return NowY - v / 100;
		else
			return h;
	};
	for (int i = 0; i < init_count;i++) {
		ptrCBullet[i].SetBoundingBox(top, bottom, left, right);
		ptrCBullet[i].SetMoveFunc(xfunc, yfunc);
		ptrCBullet[i].SetRotateAngle(rand());
		ptrCBullet[i].SetVelocity(0.5f);
		if (i % 2 == 0) {
			ptrCBullet[i].SetStartingPoint(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
			ptrCBullet[i].SetBulletType(ptrCBullet[i].TINY);
		}
		else if (i % 3 == 0) {
			ptrCBullet[i].SetStartingPoint(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f);
			ptrCBullet[i].SetBulletType(ptrCBullet[i].NORMAL);
		}
		else if (i % 5 == 0) {
			ptrCBullet[i].SetStartingPoint(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
			ptrCBullet[i].SetBulletType(ptrCBullet[i].LARGEISH);
		}
		else {
			ptrCBullet[i].SetStartingPoint(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f);
			ptrCBullet[i].SetBulletType(ptrCBullet[i].LARGEISH);
		}
		ptrCBullet[i].BulletInit();
		pBullet.push_back(&ptrCBullet[i]);
	}
}

void XCTestSC::SpellCardRelease()
{
	delete[] ptrCBullet;
	XCSpellCard::SpellCardRelease();
	//
}

void XCTestSC::SpellCardCollisonCheck(XCTaskCollisionInfo * pInfo)
{
	if (pInfo == nullptr) return;
	for (auto iter = pBullet.begin(); iter != pBullet.end(); iter++) {
		if (((XCCircleBullet*)*iter)->IsBulletRender())
			((XCCircleBullet*)*iter)->BulletCollisionWithPlayer(pInfo->pPlayer);

	}
}
