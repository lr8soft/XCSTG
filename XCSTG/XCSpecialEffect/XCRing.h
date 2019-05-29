#pragma once
#ifndef _XCRING_H_
#define _XCRING_H_
#include "XCSpecialEffect.h"

#include "../XCAudio/XCAudioEffect.h"
#include <gl/glcorearb.h>
namespace xc_se {
	class XCRing:public XCSpecialEffect {
	protected:
		/*	bool should_se_render = true,first_run=true;
		float RenderX, RenderY, RenderZ, RenderTime;
		GLuint vao, vbo, program;
		XCGameTimer SETimer;*/
		static bool have_tbo_init,have_program_init;
		static GLuint tbo[4],program_static;
		XCAudioEffect seaudio;
		int ring_type;
		virtual void ShaderInit() override;
		virtual void TextureInit() override;
		virtual void BufferInit() override;
		
	public:
		XCRing()=default;
		~XCRing() = default;
		enum { RingLightColor, RingDeepColor,RingPlayerDead,RingBossDead};
		/*Return true if reset*/
		virtual bool SpecialEffectRender(float x, float y, float z) override;
		virtual void SpecialEffectInit(int type) override;
		virtual void SpecialEffectReset() override;
		virtual void SpecialEffectRelease() override;
	};
}
#endif