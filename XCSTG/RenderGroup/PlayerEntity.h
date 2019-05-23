#pragma once
#ifndef _Render_group_
#define _Render_group_
#include <gl/glcorearb.h>
#include <GLFW/glfw3.h>
#include "../util/GameTimer.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
#include "../XCGame/XCNormalAttack.h"
#include "../XCSpecialEffect/XCRing.h"
class PlayerEntity {
private:
	xc_se::XCRing dead_se;
	bool dead_time = false;
	XCGameTimer playerTimer;
	xc_game::XCEnemyInfo *pEnemyInfo=nullptr;
	xc_game::XCAttack base_attack[2];
	const float base_speed = 1.45f, trace_interval = 0.05f;;
	float player_fire_power = 6.0f;//attack speed
	float NowX = 0, NowY = -0.1, NowZ = 0;
	bool RenderDecisionPoint = false;
	/*判定点vao、vbo与tbo*/
	GLuint vao_deci, vbo_deci,tbo_deci;
	/*玩家贴图vao、vbo、tbo*/
	GLuint vao_player[24], vbo_player[24], tbo_player;
	GLint program[2];
	/*DECISION:判定点程序 TX:玩家贴图程序*/
	enum { DECISIONTEX, PLAYERTEX };
	enum PlayerState {PLAYER_STANDBY,PLAYER_TURNRIGHT, PLAYER_TURNLEFT};
	int PlayerLastState= PLAYER_STANDBY,PlayerNowState= PLAYER_STANDBY;
	float PlayerSameStateTime= 0;
	void SetPlayerDirection(int direction);
	void EveryRenderInit();
	void EveryFinishRender();
	void OGLSettingRenderStart();
	void OGLSettingRenderEnd();
	void ShaderLoader();
	void TextureLoader();
public:
	PlayerEntity() = default;
	~PlayerEntity() = default;
	void GroupInit();
	void GroupRender(float nowFrame);
	void PlayerCollisonEvent(xc_game::XCEnemyInfo *info);
	void GroupKeyCheck(GLFWwindow* screen);
	void SetDead();
	const float** GetPlayerCoord();
};
#endif