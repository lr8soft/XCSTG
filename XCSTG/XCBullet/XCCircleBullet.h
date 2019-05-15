#pragma once
#ifndef _XCCIRCLE_BULLET_H_
#define _XCCIRCLE_BULLET_H_
#include "XCBullet.h"
namespace xc_bullet {
	class XCCircleBullet:public XCBullet {
	protected:
	  /*float deltaTime = 0.0f, lastFrame = 0.0f;
		float rotate_angle = 0.0f, velocity = 0.0f;
		std::function<float(float)> coordx_func, coordy_func;*/
		const float attack_radius = 0.035f;
		static bool have_resource_init,have_program_init;
		static GLuint temp_tbo[5],program_static;
		void SetRenderTBO(GLuint tbo);
		void ShaderInit() override;
		void TextureInit() override;
		void BufferInit() override;
		void DataInit() override;
	public:
		/*void BulletInit();*/
		
		void BulletRender(float nowFrame) override;
		void BulletCollisionWithPlayer(PlayerEntity* player) override;
	};
}
#endif