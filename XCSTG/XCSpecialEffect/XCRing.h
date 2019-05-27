#pragma once
#ifndef _XCRING_H_
#define _XCRING_H_
#include "../util/GameTimer.h"
#include "../XCAudio/XCAudioEffect.h"
#include <gl/glcorearb.h>
namespace xc_se {
	class XCRing {
	private:
		static bool have_tbo_init,have_program_init;
		static GLuint tbo[4],program_static;
		XCAudioEffect seaudio;
		int ring_type;
		float RenderX, RenderY, RenderZ;
		float NowSize = 0.015f,NowTime=0.0f, alive_time=0.2f;
		bool should_se_render = true,first_run=true;
		XCGameTimer SETimer;
		GLuint vao, vbo, program;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
		void RingReset();
	public:
		XCRing()=default;
		~XCRing() = default;
		void SpecialEffectInit(int type);
		/*Return true if reset*/
		enum { RingLightColor, RingDeepColor,RingPlayerDead,RingBossDead};
		bool SpecialEffectRender(float x, float y, float z);
	};
}
#endif