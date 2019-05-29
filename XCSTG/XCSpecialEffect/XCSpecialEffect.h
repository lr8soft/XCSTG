#pragma once
#ifndef _XCSPECIALEFFECT_H_
#define _XCSPECIALEFFECT_H_
#include <gl/glcorearb.h>
#include "../util/GameTimer.h"
namespace xc_se {
	class XCSpecialEffect {
	protected:
		bool should_se_render = true, first_run = true,is_rendering=false;
		float RenderX, RenderY, RenderZ,RenderTime,RenderSize;
		GLuint vao, vbo, program;
		XCGameTimer SETimer;
		virtual void ShaderInit()=0;
		virtual void TextureInit()=0;
		virtual void BufferInit()=0;
	public:
		bool IsRendering() {
			return is_rendering;
		}
		bool ShouldRender() {
			return should_se_render;
		}
		void SetRenderTime(float time) {
			RenderTime = time;
		}
		virtual bool SpecialEffectRender(float x, float y, float z)=0;
		virtual void SpecialEffectInit(int type) 
		{
			ShaderInit();
			TextureInit();
			BufferInit();
			should_se_render = true;
		}
		virtual void SpecialEffectReset()
		{
			first_run = true;
			SETimer.Clear();
		}
		virtual void SpecialEffectRelease() = 0;

	};
}
#endif