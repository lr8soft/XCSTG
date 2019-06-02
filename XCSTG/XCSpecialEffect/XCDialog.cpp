#include "XCDialog.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H  
bool xc_se::XCDialog::have_resource_init = false;
bool xc_se::XCDialog::have_program_init = false;
GLuint xc_se::XCDialog::vao[3];
GLuint xc_se::XCDialog::vbo[3];
GLuint xc_se::XCDialog::tbo[3];
GLuint xc_se::XCDialog::program[3];
using namespace xc_ogl;
void xc_se::XCDialog::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader FontShader;
		FontShader.loadFromFile("defaultFont.vert",GL_VERTEX_SHADER);
		FontShader.loadFromFile("defaultFont.frag", GL_FRAGMENT_SHADER);
		FontShader.linkAllShader();
		program[FONT_PART] = FontShader.getProgramHandle();
		have_program_init = true;
	}
}

void xc_se::XCDialog::TextureInit()
{
	if (!have_resource_init) {
		FT_Library freetype;
		if (FT_Init_FreeType(&freetype)) {
			MessageBox(0, "字体库加载失败！", "ERROR", MB_ICONERROR);
		}
		FT_Face fontFace;
		if(FT_New_Face(freetype,"Font/SourceHanSansCN-Normal.otf",0,&fontFace))
			MessageBox(0, "无法加载字体Font/SourceHanSansCN-Normal.otf！", "ERROR", MB_ICONERROR);
		FT_Set_Pixel_Sizes(fontFace, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		for (GLubyte c = 0; c < 128; c++)
		{
			if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
			{
				MessageBox(0, "无法加载字体!", "ERROR", MB_ICONERROR);
				continue;
			}
			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);
			glTexImage2D(
				GL_TEXTURE_2D,
				0,
				GL_RED,
				fontFace->glyph->bitmap.width,
				fontFace->glyph->bitmap.rows,
				0,
				GL_RED,
				GL_UNSIGNED_BYTE,
				fontFace->glyph->bitmap.buffer
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			// 储存字符供之后使用
		/*	Character character = {
				texture,
				glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
				glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
				face->glyph->advance.x
			};
			Characters.insert(std::pair<GLchar, Character>(c, character));*/
		}
		have_resource_init = true;
	}
}

void xc_se::XCDialog::BufferInit()
{
}

void xc_se::XCDialog::DialogInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

void xc_se::XCDialog::DialogRender()
{
}

void xc_se::XCDialog::DialogRelease()
{
	glDeleteVertexArrays(3, vao);
	glDeleteBuffers(3, vbo);
}
