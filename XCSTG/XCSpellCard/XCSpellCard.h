#pragma once
#ifndef _XCSPELLCARD_H_
#define _XCSPELLCARD_H_
#include <iostream>
#include <vector>
#include "../XCBullet/XCBullet.h"
#include "../XCTask/XCTaskCollisonInfo.h"
class XCSpellCard {
protected:
	float top = 1.0f, bottom = -1.0f, left = 1.0f, right = 1.0f;
	bool NotSpellCard = false,IsSpellCardFinish=false,IsActived=false;
	std::string SpellCardName;
	size_t SustainTime;
	std::vector<xc_bullet::XCBullet*> pBullet;
	size_t bullet_count;
public:
	virtual void SpellCardInit()=0;
	virtual void SpellCardRun(float nowFrame) {
		IsActived = true;
		for (auto iter = pBullet.begin(); iter != pBullet.end(); iter++) {
			if ((*iter)->IsBulletRender()) {
				(*iter)->BulletRender(nowFrame);
			}
		}
	}
	virtual void SpellCardRelease(){
		pBullet.clear();
	}
	virtual void SpellCardCollisonCheck(XCTaskCollisionInfo *pInfo) {
		if (pInfo == nullptr) return;
		for (auto iter = pBullet.begin(); iter != pBullet.end(); iter++) {
			if ((*iter)->IsBulletRender())
				(*iter)->BulletCollisionWithPlayer(pInfo->pPlayer);

		}
	}
	bool GetIsActive()
	{
		return IsActived;
	}

	bool IsFinish()
	{
		return IsSpellCardFinish;
	}
	void SetBorder(float t,float b,float l,float r) 
	{
		top = t; bottom = b; left = l; right = r;
	}

};
#endif