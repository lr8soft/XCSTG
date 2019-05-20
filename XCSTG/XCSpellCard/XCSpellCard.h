#pragma once
#ifndef _XCSPELLCARD_H_
#define _XCSPELLCARD_H_
#include <iostream>
#include <vector>
#include "../XCBullet/XCBullet.h"
class XCSpellCard {
protected:
	bool NotSpellCard = false;
	std::string SpellCardName;
	size_t SustainTime;
	xc_bullet::XCBullet *pBullet;
public:
	virtual void SpellCardInit();
	virtual void SpellCardRun();
	virtual void SpellCardRelease();
};
#endif