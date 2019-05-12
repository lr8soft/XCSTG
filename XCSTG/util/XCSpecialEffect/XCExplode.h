#pragma once
#ifndef _XCExplode_h_
#define _XCExplode_h_
#include <gl/glcorearb.h>
namespace xc_se {
	class XCExplode {
	private:
		static bool have_tbo_init;
		static GLuint tbo;
		int RenderType;
		float RenderSize,NowTime=0;
		const float alive_time = 0.25f;
		bool first_run;
		float deltaTime = 0.0f, lastFrame = 0.0f;
		GLuint vao, vbo, program;
		void ShaderInit();
		void TextureInit();
		void BufferInit();
		void ExplodeReset();
	public:
		XCExplode() = default;
		~XCExplode() = default;
		enum { DefaultEXPLODE, HyperEXPLODE };
		void SpecialEffectInit(int type);
		bool SpecialEffectRender(float x, float y, float z,float size);
	};
}
#endif