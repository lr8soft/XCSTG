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
		inline bool IsRendering() {
			return is_rendering;
		}
		inline bool ShouldRender() {
			return should_se_render;
		}
		inline void SetRenderTime(float time) {
			RenderTime = time;
		}
		inline void SetRenderSize(float size) {
			RenderSize = size;
		}
		inline void SetShouldRender(bool shouldrender) {
			should_se_render = shouldrender;
		}
		inline void SetIsRendering(bool isrendering) {
			is_rendering = isrendering;
		}
		float* GetRenderCoord() {
			static float RenderCoord[3];
			RenderCoord[0] = RenderX;
			RenderCoord[1] = RenderY;
			RenderCoord[2] = RenderZ;
			return RenderCoord;
		}
		virtual bool SpecialEffectRender(float x, float y, float z) {
			RenderX = x; RenderY = y; RenderZ = z;
			return false;
		}
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