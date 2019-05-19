#pragma once
#ifndef _BASE_ENEMY_H_
#define _BASE_ENEMY_H_
#include <functional>
#include <gl/glcorearb.h>
#include "../../XCSpecialEffect/XCRing.h"
namespace xc_game {
	using EnemyFunctionType = std::function<float(float, float, float, float, float, float)>;
	class XCEnemy {
	public:
		XCEnemy() = default;
		virtual void EnemyInit(size_t type);
		virtual void EnemyRender(float nowFrame);
		/*TYPE:SINGLE_COORD*/
		virtual void SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v);
		/*TYPE:FUNCTION_PATH*/
		void SetMoveFunc(EnemyFunctionType xfunc, EnemyFunctionType yfunc);
		/*TYPE:FUNCTION_PATH*/
		void SetStartPoint(float x, float y, float z);
		/*TYPE:FUNCTION_PATH*/
		void SetVelocity(float v);
		void SetDead();
		void SetDamage(float damage);
		virtual void ReleaseResource();
		enum {SINGLE_COORD,FUNCTION_PATH};
		bool IsRendering();
		bool IsDead();
		float** GetNowCoord();
	private:
		xc_se::XCRing dead_se, damage_se;
	protected:
		static bool have_resource_init, have_program_init;
		static GLuint tbo[2],program_static;
		size_t move_type;
		bool have_start_pos = false, have_xyfunc = false, have_velocity = false;
		EnemyFunctionType coordx_func,coordy_func;
		bool should_render = false, should_positive, first_move = true, is_dead = true, be_attack = false;
		float full_enemy_life = 5.0f;
		float enemy_life = 5.0f;
		float NowX, NowY, NowZ;
		float destX, destY, destZ, velocity;//velocity是相对x而言
		float deltaTime = 0.0f, lastFrame = 0.0f;
		/*TYPE:SINGLE_COORD*/
		float slope_k, parameter_b, parameter_theta;;//y=kx+b里的k和b
		GLuint vao, vbo, use_tbo,program;
		enum type { FAIRY,HAIRBALL };
		float GetCoordY();
		void CheckShouldEnd();
		virtual void ShaderInit();
		virtual void BufferInit();
		virtual void TextureInit();
		virtual void SetUseTBO(GLuint tbo);
		virtual void OGLSettingRenderStart();
		virtual void OGLSettingRenderEnd();
	};
}
#endif