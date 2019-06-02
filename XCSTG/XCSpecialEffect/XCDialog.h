#pragma once
#ifndef _XCDIALOG_H_
#define _XCDIALOG_H_
#include <GL/glcorearb.h>
#include "../util/GameTimer.h"
namespace xc_se {
	class XCDialog {
	protected:
		enum SEPart {TEX_PART,FONT_PART,SE_PART};
		static bool have_resource_init, have_program_init;
		static GLuint vao[3], vbo[3], tbo[3], program[3];
		XCGameTimer dialogTimer;
		virtual void ShaderInit();
		virtual void TextureInit();
		virtual void BufferInit();
	public:
		virtual void DialogInit();
		virtual void DialogRender();
		virtual void DialogRelease();
	};
}
#endif