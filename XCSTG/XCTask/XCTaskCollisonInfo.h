#pragma once
#ifndef _XCTASK_COLLISION_INFO_
#define _XCTASK_COLLISION_INFO_
#include "../XCRenderGroup/PlayerEntity.h"
#include "../XCGame/Enemy/XCEnemyInfo.h"
#include "../XCGame/Enemy/XCBoss.h"
class XCTaskCollisionInfo {
public:
	float deltaTime,nowFrame;
	PlayerEntity* pPlayer=nullptr;
	xc_game::XCEnemyInfo EnemyInfoGroup;
	xc_game::XCBoss *nowRenderBoss = nullptr;
};
#endif