#pragma once
#ifndef _Enemy_Render_group_
#define _Enemy_Render_group_
#include "../XCGame/Enemy/XCNormalEnemy.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
#include <glfw/glfw3.h>
class EnemyRenderGroup
{
private:
	xc_game::XCEnemy test_enemy[2560];
	xc_game::XCEnemyInfo AllEnemyInfo;
public:
	EnemyRenderGroup()=default;
	~EnemyRenderGroup() = default;
	void GroupInit();
	void GroupRender(float nowFrame);
	void GroupKeyCheck(GLFWwindow* screen);
	xc_game::XCEnemyInfo* GetEnemyInfoGroup();
};
#endif
