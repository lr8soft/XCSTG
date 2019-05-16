#pragma once
#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_
#include <gl/glcorearb.h>
#include <functional>
#include "../rendergroup/PlayerEntity.h"
namespace xc_bullet {
	/*参数:NowX, NowY, nowTime, deltaTime, velocity, parameter*/
	using BulletFunctionType=std::function<float(float, float, float, float, float, float)>;
	class XCBullet {
	protected:
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float rotate_angle = 0.0f, velocity = 0.0f;
		float NowX=0.0f, NowY=0.5f, NowZ=0.0f;
		bool should_render = false,have_start_pos=false,have_xyfunc=false,have_velocity=false;

		bool aim_to_player = false,have_atp_init=false,atp_positive=false;
		float atp_k, atp_b,atp_theta;
		/*渲染范围 -1.1<NowX<1.1 -1.1<NowY<1.1*/
		BulletFunctionType coordx_func,coordy_func;
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
		void UpdateAimToPlayerCoord() {
			if (ShouldAimToPlayer()) {
				if (atp_positive)
					NowX += velocity * cosf(atp_theta)* deltaTime;
				else
					NowX -= velocity * cosf(atp_theta)* deltaTime;
				NowY = atp_k * NowX + atp_b;
				std::cout << "NowX:" << NowX << " NowY:" << NowY << std::endl;
			}
		}
		void SetStartingPoint(float x,float y,float z) {
			NowX = x; NowY = y; NowZ = z;
			have_start_pos = true;
		}
		void StopBulletWork()
		{
			should_render = false;
		}
		/*!Inherit example:
			XCBullet::BulletRender(nowFrame);
			.....(Put your code here)*/
		virtual void BulletRender(float nowFrame) {
			float currentFrame = nowFrame;
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
		}
		/*父类的方法是自机狙的*/
		virtual void BulletCollisionWithPlayer(PlayerEntity* player) {
			if (!aim_to_player) return;
			if (player == nullptr) return;
			if (should_render) 
			{
				if (!have_atp_init) {
					auto player_coord = player->GetPlayerCoord();
					float x = **player_coord, y = **(player_coord + 1), z = **(player_coord + 2);
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