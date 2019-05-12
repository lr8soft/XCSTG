#pragma once
#ifndef _TraceAttack_h_
#define _TraceAttack_h_
#include "Enemy/XCNormalEnemy.h"
namespace xc_game {
	class XCTrackAttack{
	protected:
		static bool have_resource_init;
		static GLuint tbo;
		bool should_positive,have_enemy_lock=false;
		const float attack_damage = 0.1f;
		const float attack_radius=0.1f;
		const float return_velocity = 1.5f;
		unsigned int runtime_mode= FOLLOW_PLAYER_MODE;
		float offset_posX;
		float *playerX, *playerY, *playerZ;//玩家坐标指针
		float NowX = 0, NowY = 0, NowZ = 0, velocity = 0;
		float *destX=nullptr, *destY=nullptr, *destZ = nullptr;//敌人坐标指针
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float temp_k, temp_b;
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
		enum TraceMode{ FOLLOW_ENEMY_MODE, FOLLOW_PLAYER_MODE, MOVEING_MODE,FORCE_RETURN };
		void AttackInit();
		void AttackRender(float nowFrame);
		void SetPlayerPosition(float *x,float *y,float *z);
		void SetVelocity(float v);
		void SetOffsizeX(float offsize_x);
		void SetTarget(float *X,float *Y,float *Z);
		void CheckCollisionWithEnemy(XCEnemy *enemy);
		bool IsWorking();
		void SetAttackMode(size_t mode);
	};
}
#endif