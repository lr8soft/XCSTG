#include "BulletRenderGroup.h"
void BulletRenderGroup::GroupInit()
{
	auto xfunc = [](float NowX,float time)->float {
		float ret_x = NowX - time;
		return NowX;
	};
	auto yfunc = [](float NowX,float NowY)->float {
		float ret_y = NowY + NowX / 2;
		return NowY;
	};
	for (int i = 0; i < 6;i++) {
		normalbullet[i].SetRotateAngle(1440.0f);
		normalbullet[i].SetVelocity(1.0f);
		normalbullet[i].SetMoveFunc(xfunc, yfunc);
		normalbullet[i].SetStartingPoint(0.1f*i, 0.1f*i,0.0f);
		normalbullet[i].BulletInit();
	}
}

void BulletRenderGroup::GroupRender(float nowFrame)
{
	for (int i = 0; i < 6; i++) {
		normalbullet[i].BulletRender(nowFrame);
	}
}

void BulletRenderGroup::GroupInitInfo(PlayerRenderGroup * playerinfo)
{
	ptr = playerinfo;
}

void BulletRenderGroup::GroupUpdateInfo()
{
	for (int i = 0; i < 6; i++) {
		normalbullet[i].BulletCollisionWithPlayer(ptr);
	}
}
