#pragma once
#ifndef _XCRING_H_
#define _XCRING_H_
#include <gl/glcorearb.h>
namespace xc_se {
	class XCRing {
	private:
		static bool have_tbo_init;
		static GLuint tbo[2];
		int ring_type;
		float RenderX, RenderY, RenderZ;
		float NowSize = 0.015f,NowTime=0.0f;
		bool should_se_render = true,first_run=true;
		const float alive_time = 0.25f;
		float deltaTime = 0.0f, lastFrame = 0.0f;
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
		enum { RingLightColor, RingDeepColor};
		bool SpecialEffectRender(float x, float y, float z);
	};
}
#endif