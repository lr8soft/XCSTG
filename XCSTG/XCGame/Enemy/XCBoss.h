#pragma once
#ifndef _BASE_BOSS_H_
#define _BASE_BOSS_H_
#include "XCEnemyBase.h"
namespace xc_game {
	class XCBoss :public xc_game::XCEnemyBase {
	protected:
		virtual void ShaderInit() override;
		virtual void BufferInit() override;
		virtual void TextureInit() override;
		static bool have_program_init;
		GLuint program_static;
	public:
		virtual void EnemyInit(size_t type) override;
		virtual void EnemyRender(float nowFrame) override;
		virtual void ReleaseResource() override;
	};
}
#endif