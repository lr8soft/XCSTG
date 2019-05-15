#pragma once
#ifndef _XCTASK_COLLISION_INFO_
#define _XCTASK_COLLISION_INFO_
#include "../RenderGroup/PlayerEntity.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
class XCTaskCollisionInfo {
public:
	float deltaTime,nowFrame;
	PlayerEntity* pPlayer=nullptr;
	xc_game::XCEnemyInfo EnemyInfoGroup;
};
#endif