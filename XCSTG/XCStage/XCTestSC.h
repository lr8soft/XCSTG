#pragma once
#ifndef _XCTESTSC_H_
#define _XCTESTSC_H_
#include "../XCSpellCard/XCSpellCard.h"
class XCTestSC :public XCSpellCard{
protected:
public:
	virtual void SpellCardInit() override;
	virtual void SpellCardRun(float nowFrame) override;
	virtual void SpellCardRelease()override;
	virtual void SpellCardCollisonCheck(XCTaskCollisionInfo *pInfo)override;
};
#endif