#pragma once
#ifndef _BASE_BOSS_H_
#define _BASE_BOSS_H_
#include "XCEnemyBase.h"
#include "../../XCSpellCard/XCSpellCard.h"
#include "../../XCSpecialEffect/XCBossInfoSlot.h"
#include "../../XCSpecialEffect//XCRing.h"
#include <map>
namespace xc_game {
	class XCBoss :public xc_game::XCEnemyBase {
	protected:
		/*float NowLife, MaxLife;
		float NowX, NowY, NowZ;
		float destX, destY, destZ, velocity;
		GLuint vao, vbo, use_tbo, program;
		size_t move_type;
		bool should_render = false, should_positive, first_move = true, is_dead = true, be_attack = false;
		bool have_start_pos = false, have_xyfunc = false, have_velocity = false;
		EnemyFunctionType coordx_func, coordy_func;
		float slope_k, parameter_b, parameter_theta;*/
		enum BossStateGroup {BOSS_STANDBY,BOSS_MOVING,BOSS_ATTACK};
		size_t BossNowState= BOSS_STANDBY,BossLastState= BOSS_STANDBY;
		float BossSameStateTime = 0;
				/*hp     spellcard*/
		std::map<float,XCSpellCard*> spellCardList;
		virtual void ShaderInit() override;
		virtual void BufferInit() override;
		virtual void TextureInit() =0;
		virtual void UseSpellCardRender(float nowFrame);
		static bool have_program_init,have_resource_init;
		static GLuint tbo_static;
		GLuint program_static;
		/*!!!boss不使用XCBaseEnemy类中的vao和vbo!!!*/
		GLuint vao_tex[12],vbo_tex[12],tbo;
		xc_se::XCBossInfoSlot infoSlot;
		xc_se::XCRing explode_se;
	public:
		void AddSpellCard(float maxHealth,XCSpellCard *pspellcard);
		virtual void EnemyInit(size_t type) override;
		virtual void EnemyRender(float nowFrame) override;
		virtual void ReleaseResource() override;
	};
}
#endif