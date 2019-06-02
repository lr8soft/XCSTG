#pragma once
#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_
#include <gl/glcorearb.h>
#include <functional>
#include "../XCRenderGroup/PlayerEntity.h"
#include "../XCGame/XCEntity.h"
#include "../util/GameTimer.h"
namespace xc_bullet {
	/*参数:NowX, NowY,XCGameTimer, velocity, parameter*/
	using BulletFunctionType=std::function<float(float, float, XCGameTimer, float, float)>;
	class XCBullet:public XCEntity {
	protected:
		XCGameTimer BulletTimer;
		float rotate_angle = 0.0f, velocity = 0.0f;
		//float NowX=0.0f, NowY=0.5f, NowZ=0.0f;
		bool should_render = false,have_start_pos=false,have_xyfunc=false,have_velocity=false;
		bool aim_to_player = false,have_atp_init=false,atp_positive=false;
		float atp_k, atp_b,atp_theta;
		float top = 1.1, bottom = -1.1, left = -1.1, right = 1.1;
		/*渲染范围 -1.1<NowX<1.1 -1.1<NowY<1.1*/
		BulletFunctionType coordx_func,coordy_func,coordz_func;
		GLuint vao, vbo, tbo,program;
		virtual void ShaderInit()=0;
		virtual void TextureInit()=0;
		virtual void BufferInit()=0;
		virtual void DataInit() = 0;
		virtual void DataReset() {
			have_start_pos = false;
			have_xyfunc = false;
			have_velocity = false;
			have_atp_init = false;
			aim_to_player = false;
		}
	public:
		XCBullet()=default;
		~XCBullet()=default;
		virtual void BulletInit() {
			ShaderInit(); 
			TextureInit();
			BufferInit();
			DataInit();
		}
		virtual void BulletRelease() = 0;
		void SetBoundingBox(float t, float b, float l, float r)
		{
			top = t; bottom = b; left = l; right = r;
		}
		void SetVelocity(float v)
		{ 
			velocity = v; have_velocity = true;
		}
		void SetRotateAngle(float theta)
		{
			rotate_angle = theta;
		}
		/*!!xfunc:返回NowX,参数:NowX,NowY,nowTime,deltaTime,velocity,parameter
		    yfunc:返回NowY,参数:NowX,NowY,nowTime,deltaTime,velocity,parameter*/
		void SetMoveFunc(BulletFunctionType xfunc, BulletFunctionType yfunc)
		{
			coordx_func = xfunc;
			coordy_func = yfunc; 
			have_xyfunc = true;
		}
		void SetAimToPlayer(bool should) {
			aim_to_player = should;
		}
		bool ShouldAimToPlayer() {
			return aim_to_player;
		}
		bool IsBulletRender() {
			return should_render;
		}
		void UpdateBulletCoord() {
			if (ShouldAimToPlayer()) {
				if (atp_positive)
					NowX += velocity * cosf(atp_theta)* BulletTimer.getDeltaFrame();
				else
					NowX -= velocity * cosf(atp_theta)* BulletTimer.getDeltaFrame();
				NowY = atp_k * NowX + atp_b;
			}
			else {
				NowX = coordx_func(NowX, NowY, BulletTimer, velocity, 0);
				NowY = coordy_func(NowX, NowY, BulletTimer, velocity, 0);
			}
		}
		void SetStartingPoint(float x,float y,float z) {
			SetCoord(x, y, z);
			have_start_pos = true;
		}
		void StopBulletWork()
		{
			should_render = false;
		}
		/*!Inherit example:
			XCBullet::BulletRender(nowFrame);
			.....(Put your code here)*/
		virtual void BulletRender(float nowFrame) = 0;
		/*父类的方法是自机狙的*/
		virtual void BulletCollisionWithPlayer(PlayerEntity* player) {
			if (!aim_to_player) return;
			if (player == nullptr) return;
			if (should_render) 
			{
				if (!have_atp_init) {
					auto player_coord = player->GetNowCoord();
					float x = *player_coord, y = *(player_coord + 1), z = *(player_coord + 2);
					atp_k = (y - NowY) / (x - NowX);
					atp_b = NowY - atp_k * NowX;
					if (x != NowX)
						atp_theta = acosf(abs(x - NowX) / sqrtf(pow(x - NowX, 2) + pow(y - NowY, 2)));
					else
						atp_theta = 3.1415926f / 2.0f;
					if (x > NowX)
						atp_positive = true;
					else
						atp_positive = false;
					have_atp_init = true;
				}
			}
		}
	};
}
#endif