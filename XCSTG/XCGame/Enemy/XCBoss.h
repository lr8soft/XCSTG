#pragma once
#ifndef _BASE_BOSS_H_
#define _BASE_BOSS_H_
#include "XCNormalEnemy.h"
namespace xc_game {
	class XCBoss :public xc_game::XCEnemy {
	public:
		virtual void EnemyInit(size_t type);
		virtual void EnemyRender(float nowFrame);
		virtual void ReleaseResource();
	protected:
		virtual void ShaderInit();
		virtual void BufferInit();
		virtual void TextureInit();
	};
}
#endif