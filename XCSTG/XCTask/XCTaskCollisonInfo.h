#pragma once
#ifndef _XCTASK_COLLISION_INFO_
#define _XCTASK_COLLISION_INFO_
#include "../RenderGroup/PlayerRenderGroup.h"
class XCTaskCollisionInfo {
public:
	float deltaTime,nowFrame;
	PlayerRenderGroup* pPlayer=nullptr;
};
#endif