#pragma once
#ifndef _XCPARTICLE_H_
#define _XCPARTICLE_H_
#include "../util/GameTimer.h"
#include "XCSpecialEffect.h"
#include <gl/glcorearb.h>
namespace xc_se {
	class XCParticle:XCSpecialEffect {
	protected:
		/*	bool should_se_render = true,first_run=true;
		float RenderX, RenderY, RenderZ, RenderTime;
		GLuint vao, vbo, program;
		XCGameTimer SETimer;*/
		static bool have_tbo_init, have_program_init;
		static GLuint tbo[3], program_static;
		int particle_type;
		float RenderSize = 0.015f, RenderRotate=0.0f;
		virtual void ShaderInit() override;
		virtual void TextureInit() override;
		virtual void BufferInit() override;
	public:
		XCParticle();
		~XCParticle();
		enum {STAR_PARTICLE, CIRCLE_PARTICLE, MOVING_PARTICLE};
		virtual bool SpecialEffectRender(float x, float y, float z) override;
		virtual void SpecialEffectInit(int type) override;
		virtual void SpecialEffectReset() override;
	};
}
#endif