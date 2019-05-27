#pragma once
#ifndef _XCEXPLODE_EFFECT_H_
#define _XCEXPLODE_EFFECT_H_
#include "XCAudio.h"
class XCAudioEffect:public XCAudio {
public:
	
	virtual void MusicResourceInit(int effectType);
	virtual void MusicPlay();
	virtual void MusicStop();
	virtual void MusicRelease();
};
#endif