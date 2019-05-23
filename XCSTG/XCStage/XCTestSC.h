#pragma once
#ifndef _XCTESTSC_H_
#define _XCTESTSC_H_
#include "../XCSpellCard/XCSpellCard.h"
#include "../XCBullet/XCCircleBullet.h"
class XCTestSC :public XCSpellCard{
private:
	xc_bullet::XCCircleBullet *ptrCBullet=nullptr;
public:
	virtual void SpellCardInit() override;
	virtual void SpellCardRelease() override;
	virtual void SpellCardCollisonCheck(XCTaskCollisionInfo *pInfo) override;
};
#endif