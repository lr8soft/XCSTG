#pragma once
#ifndef _Normal_Enemy_
#define _Normal_Enemy_
#include <gl/glcorearb.h>
#include "../../XCSpecialEffect/XCRing.h"
namespace xc_game {
	class XCEnemy {
	public:
		XCEnemy() = default;
		~XCEnemy() = default;
		virtual void EnemyInit();
		virtual void EnemyRender(float nowFrame);
		virtual void SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v);
		virtual void SetDead();
		virtual void SetDamage(float damage);
		//Enemy may still rendering after dead
		bool IsRendering();
		bool IsDead();
		float** GetNowCoord();
	protected:
		xc_se::XCRing dead_se, damage_se;
		static bool have_resource_init;
		static GLuint tbo[2];
		bool should_render=false,should_positive,first_move=true,is_dead=true;
		float enemy_life = 5.0f;
		float deltaX, deltaY, deltaZ;
		float destX, destY, destZ, velocity;//velocity是相对x而言
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float slope_k, parameter_b;//y=kx+b里的k和b
		GLuint vao, vbo, use_tbo,program;
		enum type { FAIRY,HAIRBALL };
		virtual float GetCoordY();
		virtual void ShaderInit();
		virtual void BufferInit();
		virtual void TextureInit();
		virtual void SetUseTBO(GLuint tbo);
		virtual void CheckShouldEnd();
		virtual void OGLSettingRenderStart();
		virtual void OGLSettingRenderEnd();
	};
}
#endif