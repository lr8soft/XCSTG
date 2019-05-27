#pragma once
#ifndef _NormalAttack_
#define _NormalAttack_
#include <gl/glcorearb.h>
#include "../util/GameTimer.h"
#include "Enemy/XCEnemyBase.h"
#include "../XCAudio/XCAudioEffect.h"
namespace xc_game {
	class XCAttack {
	protected:
		static bool have_resource_init,have_program_init;
		static GLuint tbo,program_static;
		bool should_render,should_render_attack=true;
		XCGameTimer attackTimer;
		XCAudioEffect attackAudioEffect;
		const float finish_dist = 2.0f;
		const float attack_width = 0.1f,attack_height=0.1f;
		float NowX=0, NowY=0, NowZ=0,velocity=0,destY;
		GLuint vao[4], vbo[4],program;
		//enum ATTACK_STATE{START,MIDDLE,END,FINISH};
		void ShaderInit();
		void TextureInit();
		void BufferInit();
	public:
		XCAttack() = default;
		~XCAttack() = default;
		void AttackInit();
		void AttackRender(float nowFrame);
		void SetPositionAndVelocity(float x, float y, float z,float v);
		void CheckCollisionWithEnemy(XCEnemyBase *enemy);
		void SetAttack();
		void Reset();
		bool IsRunning();
	};
}
#endif