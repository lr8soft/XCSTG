#pragma once
#ifndef _XCSPELLCARD_H_
#define _XCSPELLCARD_H_
#include <iostream>
#include <vector>
#include "../XCBullet/XCBullet.h"
class XCSpellCard {
protected:
	bool NotSpellCard = false,IsSpellCardFinish=false;
	std::string SpellCardName;
	size_t SustainTime;
	float *NowX, *NowY, *NowZ;
	xc_bullet::XCBullet *pBullet;
public:
	virtual void SpellCardInit(float *x,float *y,float *z);
	virtual void SpellCardRun(float nowFrame);
	virtual void SpellCardRelease();
	bool IsFinish();
};
#endif