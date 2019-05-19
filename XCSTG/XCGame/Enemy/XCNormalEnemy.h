#pragma once
#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_
#include "../../XCSpecialEffect/XCRing.h"
#include "XCEnemyBase.h"
namespace xc_game {
	class XCNormalEnemy:public XCEnemyBase {
	public:
		XCNormalEnemy() = default;
		enum type { FAIRY, HAIRBALL };
		virtual void EnemyInit(size_t type) override;
		virtual void EnemyRender(float nowFrame) override;
		/*TYPE:SINGLE_COORD*/
	protected:
		xc_se::XCRing dead_se, damage_se;
		static bool have_resource_init, have_program_init;
		static GLuint tbo[2],program_static;
		float full_enemy_life = 5.0f;
		float deltaTime = 0.0f, lastFrame = 0.0f;
		virtual void ShaderInit() override;
		virtual void BufferInit() override;
		virtual void TextureInit() override;
	};
}
#endif