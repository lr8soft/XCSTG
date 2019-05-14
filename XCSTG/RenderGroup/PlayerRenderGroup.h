#pragma once
#ifndef _Render_group_
#define _Render_group_
#include <gl/glcorearb.h>
#include <GLFW/glfw3.h>
#include "../XCGame/Enemy/XCEnemyInfo.h"
#include "../XCGame/XCNormalAttack.h"
#include "../XCGame/XCTraceAttack.h"
#include "../XCSpecialEffect/XCRing.h"
class PlayerRenderGroup {
private:
	xc_se::XCRing dead_se;
	bool dead_time = false;
	xc_game::XCEnemyInfo *enemy_info=nullptr;
	xc_game::XCAttack base_attack[2];
	xc_game::XCTrackAttack trace_attack[4];
	const float base_speed = 1.45f, trace_interval = 0.05f;;
	float player_fire_power = 6.0f;//attack speed
	float deltaTime = 0.0f,lastFrame = 0.0f;
	float NowX = 0, NowY = -0.1, NowZ = 0;
	bool RenderDecisionPoint = false;
	GLuint vao[2], vbo[2], tbo,TboPL[3],tboPL,tboDecision;
	GLint program[2];
	/*PLAYER:decision point program TX:texture progrm*/
	enum { DECISION, TX };
	void EveryRenderInit();
	void OGLSettingRenderStart();
	void OGLSettingRenderEnd();
	void ShaderLoader();
	void TextureLoader();
	void MoveTexSet(GLuint id);
public:
	PlayerRenderGroup() = default;
	~PlayerRenderGroup() = default;
	void GroupInit();
	void GroupRender(float nowFrame);
	void GroupUpdateInfo();
	void GroupKeyCheck(GLFWwindow* screen);
	void GroupInitInfo(xc_game::XCEnemyInfo *info);
	void SetDead();
	const float** GetPlayerCoord();
};
#endif