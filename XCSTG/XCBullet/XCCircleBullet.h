#pragma once
#ifndef _XCCIRCLE_BULLET_H_
#define _XCCIRCLE_BULLET_H_
#include "XCBullet.h"
namespace xc_bullet {
	class XCCircleBullet:public XCBullet {
	protected:
	  /*float deltaTime = 0.0f, lastFrame = 0.0f;
		float rotate_angle = 0.0f, velocity = 0.0f;
		*/
		
		size_t bulletType = 0;
											/*NORMAL,LARGEISH, HUGE,TINY*/
		const float attack_radius_group[4] = {0.035f,0.04f,0.18f,0.025f};
											/*For GL_TRIANGLES Mode*/
		const float tex_scale_rate[4] =      {0.03f,0.035f,0.25f,0.02f};
		const float tex_point_size[4] =		 {3.0f,3.5f,25.0f,2.0f};
		float attack_damage=1.0f;
		static bool have_resource_init,have_program_init,use_point_sprite;
		static GLuint temp_tbo[5],program_static;
		void SetRenderTBO(GLuint tbo);
		void ShaderInit() override;
		void TextureInit() override;
		void BufferInit() override;
		void DataInit() override;
	public:
		enum CircleBulletType { NORMAL, LARGEISH, HUGE,TINY };
		/*void BulletInit();*/
		/*Only used before bullet render*/
		void SetUsePointSprite(bool use);
		void SetBulletType(size_t type);
		void BulletRender(float nowFrame) override;
		void BulletRelease() override;
		void BulletCollisionWithPlayer(PlayerEntity* player) override;
	};
}
#endif