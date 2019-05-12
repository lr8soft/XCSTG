#pragma once
#ifndef _XCCIRCLE_BULLET_H_
#define _XCCIRCLE_BULLET_H_
#include "XCBullet.h"
namespace xc_bullet {
	class XCCircleBullet:public XCBullet {
	protected:
	  /*float deltaTime = 0.0f, lastFrame = 0.0f;
		GLuint vao, vbo, tbo, program;*/
		static bool have_resource_init;
		static GLuint temp_tbo[5];
		void SetRenderTBO(GLuint tbo);
		void ShaderInit() override;
		void TextureInit() override;
		void BufferInit() override;
		void DataInit() override;
	public:
		/*void BulletInit();*/

		void BulletRender(float nowFrame) override;
		void BulletCollisionWithPlayer(PlayerRenderGroup* player) override;
	};
}
#endif