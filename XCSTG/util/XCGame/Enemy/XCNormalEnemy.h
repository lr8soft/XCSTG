#pragma once
#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_
#include <functional>
#include <gl/glcorearb.h>
#include "../../XCSpecialEffect/XCRing.h"
namespace xc_game {
	class XCEnemy {
	public:
		XCEnemy() = default;
		~XCEnemy() = default;
		virtual void EnemyInit(size_t type);
		virtual void EnemyRender(float nowFrame);
		/*TYPE:SINGLE_COORD*/
		virtual void SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v);
		/*TYPE:FUNCTION_PATH*/
		void SetMoveFunc(std::function<float(float, float)> xfunc, std::function<float(float, float)> yfunc);
		/*TYPE:FUNCTION_PATH*/
		void SetStartPoint(float x, float y, float z);
		/*TYPE:FUNCTION_PATH*/
		void SetVelocity(float v);
		virtual void SetDead();
		virtual void SetDamage(float damage);
		enum {SINGLE_COORD,FUNCTION_PATH};
		bool IsRendering();
		bool IsDead();
		float** GetNowCoord();
	protected:
		static bool have_resource_init;
		static GLuint tbo[2];
		xc_se::XCRing dead_se, damage_se;
		size_t move_type;
		bool have_start_pos = false, have_xyfunc = false, have_velocity = false;
		std::function<float(float,float)> coordx_func,coordy_func;
		bool should_render = false, should_positive, first_move = true, is_dead = true, be_attack = false;
		float full_enemy_life = 5.0f;
		float enemy_life = 5.0f;
		float NowX, NowY, NowZ;
		float destX, destY, destZ, velocity;//velocity是相对x而言
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float slope_k, parameter_b, parameter_theta;;//y=kx+b里的k和b
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