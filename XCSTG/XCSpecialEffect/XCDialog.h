#pragma once
#ifndef _XCDIALOG_H_
#define _XCDIALOG_H_
#include <GL/glcorearb.h>
#include "../util/GameTimer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace xc_se {
	class XCDialog {
	protected:
		static bool have_resource_init, have_program_init;
		static GLuint vao[2], vbo[2], tbo[2], program[2];
		enum SEPart { TEX_PART, SE_PART };
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