#pragma once
#ifndef _XCTEST_BOSS_H_
#define _XCTEST_BOSS_H_
#include "../XCBoss.h"
class TestBoss :public xc_game::XCBoss {
protected:
	virtual void TextureInit();
	GLuint tbo;
public:
	virtual void EnemyRender(float nowFrame) override;

};
#endif