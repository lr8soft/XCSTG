#pragma once
#ifndef _BULLET_RENDER_GROUP_
#define _BULLET_RENDER_GROUP_
#include "util/XCBullet/XCCircleBullet.h"
#include "PlayerRenderGroup.h"
class BulletRenderGroup
{
private:
	xc_bullet::XCCircleBullet normalbullet[256];
	PlayerRenderGroup* ptr;
public:
	BulletRenderGroup()=default;
	~BulletRenderGroup()= default;
	void GroupInit();
	void GroupRender(float nowFrame);
	void GroupInitInfo(PlayerRenderGroup* playerinfo);
	void GroupUpdateInfo();
};
#endif
