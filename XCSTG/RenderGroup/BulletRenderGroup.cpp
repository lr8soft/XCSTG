#include "BulletRenderGroup.h"
#include <iostream>
void BulletRenderGroup::GroupInit()
{
	auto xfunc = [](float NowX,float NowY,float nowTime,float deltaTime, float v, float p)->float {
		float ret_x,sint=sin(glfwGetTime());
		float positive = sint / abs(sint);
		ret_x = NowX + positive * deltaTime*v / 3;
		return ret_x;
	};
	auto yfunc = [](float NowX, float NowY, float nowTime, float deltaTime, float v, float p)->float {
		return NowY;
	};
	for (int i = 0; i < 6;i++) {
		normalbullet[i].SetRotateAngle(1440.0f);
		normalbullet[i].SetVelocity(1.0f);
		normalbullet[i].SetMoveFunc(xfunc, yfunc);
		normalbullet[i].SetStartingPoint(0.0f, 0.1f*i,0.0f);
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
#pragma omp parallel for
	for (int i = 0; i < 6; i++) {
		normalbullet[i].BulletCollisionWithPlayer(ptr);
	}
}
