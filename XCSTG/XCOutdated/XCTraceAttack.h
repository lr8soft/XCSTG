#pragma once
#ifndef _TraceAttack_h_
#define _TraceAttack_h_
#include "Enemy/XCEnemyBase.h"
#include "../util/GameTimer.h"
namespace xc_game {
	class XCTrackAttack{
	protected:
		static bool have_resource_init,have_program_init;
		static GLuint tbo,program_static;
		bool should_positive,have_enemy_lock=false;
		const float attack_damage = 0.01f;
		const float attack_radius=0.03f;
		const float return_velocity = 6.0f;
		unsigned int runtime_mode= FOLLOW_PLAYER_MODE,require_mode= NONE_MODE;
		float offset_posX;
		float *playerX, *playerY, *playerZ;//玩家坐标指针
		float NowX = 0, NowY = 0, NowZ = 0, velocity = 0;
		float *destX=nullptr, *destY=nullptr, *destZ = nullptr;//敌人坐标指针
		float temp_k, temp_b,temp_theta;
		XCGameTimer attackTimer;
		GLuint vao, vbo,program;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
		void ReCalcParameter();
		void UpdateCoordY();
		void SetAttackMode_Inside(size_t mode);
	public:
		XCTrackAttack() = default;
		~XCTrackAttack() = default;
		enum TraceMode{ FOLLOW_ENEMY_MODE, FOLLOW_PLAYER_MODE, MOVEING_MODE,FORCE_RETURN,NONE_MODE };
		void AttackInit();
		void AttackRender(float nowFrame);
		void SetPlayerPosition(float *x,float *y,float *z);
		void SetVelocity(float v);
		void SetOffsizeX(float offsize_x);
		void SetTarget(float *X,float *Y,float *Z);
		void CheckCollisionWithEnemy(XCEnemyBase *enemy);
		bool IsWorking();
		void SetAttackMode(size_t mode);
	};
}
#endif