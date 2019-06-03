#pragma once
#ifndef _XCDIALOG_H_
#define _XCDIALOG_H_
#include <GL/glcorearb.h>
#include <map>
#include <vector>
#include "../util/GameTimer.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
namespace xc_se {
	struct XCCharacter {
		GLuint tbo;
		glm::ivec2 size;
		glm::ivec2 offset;
		GLuint advance;
	};
	struct XCUniformChar {
		std::vector<GLuint> tboGroup;
		std::vector<glm::ivec2> sizeGroup;
		std::vector<glm::ivec2> offsetGroup;
		std::vector<GLuint> advanceGroup;
	};
	class XCDialog {
	protected:
		static bool have_resource_init, have_program_init;
		static GLuint vao[3], vbo[3], tbo[3], program[3];
		static std::map<GLchar, xc_se::XCCharacter> XCCharacterGroup;
		std::map<std::wstring, xc_se::XCUniformChar*> XCRenderStringGroup;
		enum SEPart { FONT_PART, TEX_PART, SE_PART };
		XCGameTimer dialogTimer;
		/*!Only ASCII characters.*/
		void TextRender(std::string text,float x,float y,float scale,glm::vec4 color);
		/*!All characters can use it.*/
		void AddTextToPreRenderMap(std::wstring text);
		/*!All characters can use it.*/
		void TextUnicodeRender(std::wstring text,float x,float y,float scale,glm::vec4 color);
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