#pragma once
#ifndef _XCPARTICLE_H_
#define _XCPARTICLE_H_
#include "../util/GameTimer.h"
#include "XCSpecialEffect.h"
#include <gl/glcorearb.h>
namespace xc_se {
	class XCParticle:public XCSpecialEffect {
	protected:
		/*	bool should_se_render = true, first_run = true,is_rendering=false;
		float RenderX, RenderY, RenderZ,RenderTime,RenderSize;
		GLuint vao, vbo, program;
		XCGameTimer SETimer;*/
		static bool have_tbo_init, have_program_init;
		static GLuint tbo[2], program_static;
		int particle_type, ParticleOffset = 0;
		float RenderRotate = 0.0f;
		virtual void ShaderInit() override;
		virtual void TextureInit() override;
		virtual void BufferInit() override;
	public:
		enum {CIRCLE_PARTICLE, MOVING_PARTICLE};
		virtual bool SpecialEffectRender(float x, float y, float z) override;
		virtual void SpecialEffectInit(int type) override;
		virtual void SpecialEffectReset() override;
		virtual void SpecialEffectRelease() override;
		/*!Set different offset to make particle colorful.*/
		inline void SetOffset(int ot) {
			ParticleOffset = ot;
		}
	};
}
#endif