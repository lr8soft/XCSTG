#pragma once
#ifndef _XCEnemyBASE_H_
#define _XCEnemyBASE_H_
#include <functional>
#include <GL/glcorearb.h>
#define BOSS_ENEMY 0
#define NORMAL_ENEMY 1
namespace xc_game {
	using EnemyFunctionType = std::function<float(float, float, float, float, float, float)>;
	/*Ĭ���½��������ʱshould_renderΪfalse*/
	class XCEnemyBase {
	public:
		enum { SINGLE_COORD, FUNCTION_PATH };
		enum EnemyState { ENEMY_STANDBY, ENEMY_MOVING, ENEMY_ATTACK };
		virtual void EnemyRender(float nowFrame);
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
		bool IsShouldRender();
		bool IsRenderNow();
		bool IsDead();
		size_t GetEnemyType();
	protected:
		float NowLife, MaxLife;
		float NowX, NowY, NowZ;
		float destX, destY, destZ, velocity;
		GLuint use_tbo, program;
		/*�йص��˲�ͬ״̬ʱ�����ͼ����*/
		int EnemyNowState= ENEMY_STANDBY, EnemyLastState= ENEMY_STANDBY, EachStateInterval = 0;
		float StandByInterval=0, AttackInterval=0, MovingInterval=0;
		float EnemySameStateTime = 0.0f;
		int move_type,enemy_type;
			/*�п�����Ӧ�ñ���Ⱦ�ģ�����δ��Ⱦ															�Ƿ���Ⱦ��*/
		bool should_render = false, should_positive, first_move = true, is_dead = true, be_attack = false,is_render=false;
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
	};
}
#endif