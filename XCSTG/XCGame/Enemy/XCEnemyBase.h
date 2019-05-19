#pragma once
#ifndef _XCEnemyBASE_H_
#define _XCEnemyBASE_H_
#include <functional>
#include <GL/glcorearb.h>
namespace xc_game {
	using EnemyFunctionType = std::function<float(float, float, float, float, float, float)>;
	/*默认新建对象出来时should_render为false*/
	class XCEnemyBase {
	protected:
		float NowLife, MaxLife;
		float NowX, NowY, NowZ;
		float destX, destY, destZ, velocity;
		GLuint vao, vbo, use_tbo, program;
		size_t move_type;
		bool should_render = false, should_positive, first_move = true, is_dead = true, be_attack = false;
		bool have_start_pos = false, have_xyfunc = false, have_velocity = false;
		EnemyFunctionType coordx_func, coordy_func;
		float slope_k, parameter_b, parameter_theta;
		virtual void ShaderInit()=0;
		virtual void BufferInit() = 0;
		virtual void TextureInit() = 0;
		virtual void OGLSettingRenderStart();
		virtual void OGLSettingRenderEnd();
		void SetUseTBO(GLuint tbo);
		void CheckShouldEnd();
		
	public:
		enum { SINGLE_COORD, FUNCTION_PATH };
		virtual void EnemyRender(float nowFrame) = 0;
		virtual void ReleaseResource();
		virtual void EnemyInit(size_t CoordType);
		/*TYPE:SINGLE_COORD*/
		void SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v);
		/*TYPE:SINGLE_COORD*/
		float GetCoordY();
		/*TYPE:FUNCTION_PATH*/
		void SetMoveFunc(EnemyFunctionType xfunc, EnemyFunctionType yfunc);
		/*TYPE:FUNCTION_PATH*/
		void SetStartPoint(float x, float y, float z);
		/*TYPE:FUNCTION_PATH*/
		void SetVelocity(float v);
		void SetDead();
		void SetDamage(float damage);
		float **GetNowCoord();
		bool IsRendering();
		bool IsDead();
	};
}
#endif