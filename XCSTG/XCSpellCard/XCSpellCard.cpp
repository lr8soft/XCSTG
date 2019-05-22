#include "XCSpellCard.h"
#include "../util/ShaderReader.h"
#include "../XCBullet/XCCircleBullet.h"
using namespace std;
using namespace xc_bullet;
void XCSpellCard::SpellCardInit(float *x, float *y, float *z)
{
	pBullet = new XCCircleBullet[256];
	auto xfunc = [](float x,float y,float nt,float dt,float v,float p) {
		return x;
	};
	auto yfunc = [](float x, float y, float nt, float dt, float v, float p) {
		return y-v/100;
	};
	for (int i = 0; i < 256;i++) {
		((XCCircleBullet*)pBullet)[i].SetBulletType(((XCCircleBullet*)pBullet)[i].HUGE);
		((XCCircleBullet*)pBullet)[i].SetMoveFunc(xfunc, yfunc);
		((XCCircleBullet*)pBullet)[i].SetRotateAngle(rand() / RAND_MAX);
		if(i%2==0)
			((XCCircleBullet*)pBullet)[i].SetStartingPoint(*x+i/256, *y, *z);
		else
			((XCCircleBullet*)pBullet)[i].SetStartingPoint(*x - i / 256, *y, *z);
		((XCCircleBullet*)pBullet)[i].SetVelocity(1.0f);
		((XCCircleBullet*)pBullet)[i].BulletInit();
	}
}

void XCSpellCard::SpellCardRun(float nowFrame)
{
	for (int i = 0; i < 256; i++) {
		((XCCircleBullet*)pBullet)[i].BulletRender(nowFrame);
	}
}

void XCSpellCard::SpellCardRelease()
{
	delete[] pBullet;
}

bool XCSpellCard::IsFinish()
{
	return IsSpellCardFinish;
}
