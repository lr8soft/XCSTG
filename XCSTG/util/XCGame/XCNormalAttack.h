#pragma once
#ifndef _NormalAttack_
#define _NormalAttack_
#include <gl/glcorearb.h>
#include "Enemy/XCNormalEnemy.h"
namespace xc_game {
	class XCAttack {
	protected:
		static bool have_resource_init;
		static GLuint tbo[4];
		bool should_render;
		const float finish_dist = 2.0f;
		const float attack_width = 0.1f,attack_height=0.1f;
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float NowX=0, NowY=0, NowZ=0,velocity=0,destY;
		GLuint vao, vbo,program,render_tbo;
		enum ATTACK_STATE{START,MIDDLE,END,FINISH};
		void ShaderInit();
		void TextureInit();
		void BufferInit();
	public:
		XCAttack() = default;
		~XCAttack() = default;
		void AttackInit();
		void AttackRender(float nowFrame);
		void SetPositionAndVelocity(float x, float y, float z,float v);
		void CheckCollisionWithEnemy(XCEnemy *enemy);
		void SetAttack();
		void Reset();
		bool IsRunning();
	};
}
#endif