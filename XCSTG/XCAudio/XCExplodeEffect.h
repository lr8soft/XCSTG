#pragma once
#ifndef _XCEXPLODE_EFFECT_H_
#define _XCEXPLODE_EFFECT_H_
#include "XCAudio.h"
class XCExplodeEffect:public XCAudio {
public:
	virtual void MusicResourceInit();
	virtual void MusicPlay();
	virtual void MusicStop();
	virtual void MusicRelease();
	virtual void MusicThreadWork() ;
};
#endif