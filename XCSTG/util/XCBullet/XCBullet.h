#pragma once
#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_
#include <gl/glcorearb.h>
#include <functional>
#include "../../PlayerRenderGroup.h"
namespace xc_bullet {
	class XCBullet {
	protected:
		float deltaTime = 0.0f, lastFrame = 0.0f;
		float rotate_angle = 0.0f, velocity = 0.0f;
		float NowX=0.0f, NowY=0.5f, NowZ=0.0f;
		bool should_render = false,have_start_pos=false,have_xyfunc=false,have_velocity=false;
		/*渲染范围 -1.1<NowX<1.1 -1.1<NowY<1.1*/
		/*参数:NowX,nowTime*/
		std::function<float(float,float)> coordx_func;
		/*参数:NowX,NowY*/
		std::function<float(float,float)> coordy_func;
		GLuint vao, vbo, tbo,program;
		virtual void ShaderInit()=0;
		virtual void TextureInit()=0;
		virtual void BufferInit()=0;
		virtual void DataInit() = 0;
		virtual void DataReset() {
			have_start_pos = false;
			have_xyfunc = false;
			have_velocity = false;
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
		/*！！！X函数里参数是放glfwGetTime()的！,Y函数里参数是X*/
		void SetMoveFunc(std::function<float(float,float)> xfunc, std::function<float(float,float)> yfunc) 
		{
			coordx_func = xfunc; coordy_func = yfunc; have_xyfunc = true;
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
		virtual void BulletCollisionWithPlayer(PlayerRenderGroup* player)=0;
	};
}
#endif