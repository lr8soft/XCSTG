#pragma once
#ifndef _BULLET_BASE_H_
#define _BULLET_BASE_H_
#include <gl/glcorearb.h>
#include "../../PlayerRenderGroup.h"
namespace xc_bullet {
	class XCBullet {
	protected:
		float deltaTime = 0.0f, lastFrame = 0.0f;
		GLuint vao, vbo, tbo,program;
		virtual void ShaderInit()=0;
		virtual void TextureInit()=0;
		virtual void BufferInit()=0;
		virtual void DataInit() = 0;
	public:
		XCBullet()=default;
		~XCBullet()=default;
		void BulletInit() {
			ShaderInit(); 
			TextureInit();
			BufferInit();
			DataInit();
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