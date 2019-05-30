#include "XCEnemyBase.h"
#include <GL3/gl3w.h>

void xc_game::XCEnemyBase::OGLSettingRenderStart()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void xc_game::XCEnemyBase::OGLSettingRenderEnd()
{
	glDisable(GL_BLEND);
}

void xc_game::XCEnemyBase::SetUseTBO(GLuint tbo)
{
	use_tbo = tbo;
}

void xc_game::XCEnemyBase::CheckShouldEnd()
{
	switch (move_type) {
	case SINGLE_COORD:
		if (should_positive) {
			if (NowX > destX) {
				should_render = false;
			}
		}
		else {
			if (destX > NowX) {
				should_render = false;
			}
		}
		break;
	case FUNCTION_PATH:
		break;
	}
	if (NowX > right || NowX<left || NowY>top || NowY < bottom) {
		should_render = false;
	}
	if (is_dead) {
		should_render = false;
	}
}

void xc_game::XCEnemyBase::EnemyRender(float nowFrame)
{
	if (should_render) {
		is_render = true;
		if (EnemyNowState == EnemyLastState) {
			if (EnemySameStateTime < EachStateInterval) {
				switch (EnemyNowState) {
				case ENEMY_ATTACK:
					EnemySameStateTime += AttackInterval; break;
				case ENEMY_STANDBY:
					EnemySameStateTime += StandByInterval; break;
				case ENEMY_MOVING:
					EnemySameStateTime += MovingInterval; break;
				}

				}
				else {
					EnemySameStateTime = 0;
#ifdef _DEBUG
#define _ENEMY_MODE_SHOW_
#endif
#ifdef _ENEMY_MODE_SHOW_
					switch (EnemyNowState) {//±éÀústate
					case ENEMY_MOVING:
					case ENEMY_STANDBY:
						EnemyNowState++; break;
					case ENEMY_ATTACK:
						EnemyNowState = ENEMY_STANDBY; break;
					}
#endif
				}
			}
			else {
				EnemySameStateTime = 0;
				EnemyLastState = EnemyNowState;
			}
	}
}

void xc_game::XCEnemyBase::ReleaseResource()
{
	;
}

void xc_game::XCEnemyBase::EnemyInit(size_t type)
{
	ShaderInit();
	BufferInit();
	TextureInit();
	be_attack = false;
	move_type = type;
	switch (type) {
	case FUNCTION_PATH:
		if (have_start_pos == true && have_velocity == true && have_xyfunc == true) {
			should_render = true;
			is_dead = false;
		}
		else {
			should_render = false;
		}
		break;
	}
}

void xc_game::XCEnemyBase::SetBoundingBox(float t, float b, float l, float r)
{
	top = t; bottom = b; left = l; right = r;
}

void xc_game::XCEnemyBase::SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v)
{
	if (!should_render) {
		destX = dx, destY = dy, destZ = dz;
		NowX = x, NowY = y, NowZ = z;
		velocity = v;
		slope_k = (destY - NowY) / (destX - NowX);
		parameter_b = NowY - slope_k * NowX;
		should_render = true;
		is_dead = false;
		if (destX != NowX)
			parameter_theta = acosf(abs(destX - NowX) / sqrtf(pow(destX - NowX, 2) + pow(destY - NowY, 2)));
		else
			parameter_theta = 3.1415926f / 2.0f;

		if (destX > NowX)
			should_positive = true;
		else
			should_positive = false;
	}
}

float xc_game::XCEnemyBase::GetCoordY()
{
	return slope_k * NowX + parameter_b;
}

void xc_game::XCEnemyBase::SetMoveFunc(EnemyFunctionType xfunc, EnemyFunctionType yfunc)
{
	coordx_func = xfunc;
	coordy_func = yfunc;
	have_xyfunc = true;
}

void xc_game::XCEnemyBase::SetStartPoint(float x, float y, float z)
{
	NowX = x; NowY = y; NowZ = z;
	have_start_pos = true;
}

void xc_game::XCEnemyBase::SetVelocity(float v)
{
	velocity = v;
	have_velocity = true;
}

void xc_game::XCEnemyBase::SetDead()
{
	is_dead = true;
}

void xc_game::XCEnemyBase::SetDamage(float damage)
{
	NowLife -= damage;
	if (NowLife <= 0) {
		is_dead = true;
	}
	else {
		be_attack = true;
	}
}

float ** xc_game::XCEnemyBase::GetNowCoord()
{
	static float *coord_temp[3];
	*(coord_temp) = &NowX;
	*(coord_temp + 1) = &NowY;
	*(coord_temp + 2) = &NowZ;
	return coord_temp;
}

bool xc_game::XCEnemyBase::IsShouldRender()
{
	return should_render;
}

bool xc_game::XCEnemyBase::IsRenderNow()
{
	return is_render;
}

bool xc_game::XCEnemyBase::IsDead()
{
	return is_dead;
}

size_t xc_game::XCEnemyBase::GetEnemyType()
{
	return enemy_type;
}
