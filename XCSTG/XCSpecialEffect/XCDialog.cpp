#include "XCDialog.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>
#include <ft2build.h>
#include <sstream>
#include FT_FREETYPE_H  
std::map<GLchar, xc_se::XCCharacter> xc_se::XCDialog::XCCharacterGroup;
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
		FontShader.loadFromFile("Shader/Font/defaultFont.vert",GL_VERTEX_SHADER);
		FontShader.loadFromFile("Shader/Font/defaultFont.frag", GL_FRAGMENT_SHADER);
		FontShader.linkAllShader();
		program[FONT_PART] = FontShader.getProgramHandle();
		glUniform1i(glGetUniformLocation(program[FONT_PART],"tex"),0);
		have_program_init = true;
	}
}
void xc_se::XCDialog::AddTextToPreRenderMap(std::wstring text)
{
	FT_Library freetype;
	FT_Face fontFace;
	if (FT_Init_FreeType(&freetype)) {
		MessageBox(0, "FreeType加载失败！", "ERROR", MB_ICONERROR); return;
	}
	if (FT_New_Face(freetype, "Font/SourceHanSansCN-Normal.otf", 0, &fontFace)) {
		MessageBox(0, "无法加载字体Font/SourceHanSansCN-Normal.otf！", "ERROR", MB_ICONERROR); return;
	}
	FT_Set_Pixel_Sizes(fontFace, 0, 48);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	XCUniformChar *tempChar=new XCUniformChar;
	for (auto iter = text.begin(); iter != text.end();iter++) {
		std::wstringstream ss;
		ss.imbue(std::locale("chs"));
		ss << *iter;
		wchar_t load_char = *iter;
		if (FT_Load_Char(fontFace, load_char, FT_LOAD_RENDER))
		{
			char* log = new char[128];
			sprintf_s(log, 64, "无法加载字体 %c!", *iter);
			MessageBox(0, log, "ERROR", MB_ICONERROR);
			delete[] log;
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
		tempChar->tboGroup.push_back(texture);
		tempChar->offsetGroup.push_back(glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows));
		tempChar->sizeGroup.push_back(glm::ivec2(fontFace->glyph->bitmap_left, fontFace->glyph->bitmap_top));
		tempChar->advanceGroup.push_back(fontFace->glyph->advance.x);
	}
	XCRenderStringGroup.insert(std::pair<std::wstring, XCUniformChar*>(text, tempChar));
}
void xc_se::XCDialog::TextureInit()
{
	if (!have_resource_init) {
////////////////////////字符纹理加载Start/////////////////////////////////////////
		FT_Library freetype;
		FT_Face fontFace;
		if (FT_Init_FreeType(&freetype)) {
			MessageBox(0, "FreeType加载失败！", "ERROR", MB_ICONERROR); return;
		}
		if (FT_New_Face(freetype, "Font/SourceHanSansCN-Normal.otf", 0, &fontFace)) {
			MessageBox(0, "无法加载字体Font/SourceHanSansCN-Normal.otf！", "ERROR", MB_ICONERROR); return;
		}
		FT_Set_Pixel_Sizes(fontFace, 0, 48);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);//像素之间紧密对齐
		for (GLubyte c = 0; c < 128; c++)
		{
			if (FT_Load_Char(fontFace, c, FT_LOAD_RENDER))
			{
				char* log = new char[128];
				sprintf_s(log,64,"无法加载字体 %c!",c);
				MessageBox(0, log, "ERROR", MB_ICONERROR);
				delete[] log;
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
			XCCharacter character = {
				texture,
				glm::ivec2(fontFace->glyph->bitmap.width, fontFace->glyph->bitmap.rows),
				glm::ivec2(fontFace->glyph->bitmap_left,  fontFace->glyph->bitmap_top),
				fontFace->glyph->advance.x
			};
			XCCharacterGroup.insert(std::pair<GLchar, XCCharacter>(c, character));
		}
		FT_Done_Face(fontFace);
		FT_Done_FreeType(freetype);
////////////////////////字符纹理加载Finish/////////////////////////////////////////
		have_resource_init = true;
	}
}

void xc_se::XCDialog::BufferInit()
{
	glGenVertexArrays(3, vao);
	glGenBuffers(3, vbo);
////////////////////Char start////////////
	glBindVertexArray(vao[FONT_PART]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[FONT_PART]);
	/*绘制两三角形六个顶点，每个顶点有vec2 tex_pos与vec2 draw_pos*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);
	auto draw_vertex_loc = glGetAttribLocation(program[FONT_PART], "draw_vertex");
	glVertexAttribPointer(draw_vertex_loc, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), nullptr);
	glEnableVertexAttribArray(draw_vertex_loc);

	glBindVertexArray(0);
}
void xc_se::XCDialog::DialogInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
	AddTextToPreRenderMap(L"XCSTG 测试");
}
void xc_se::XCDialog::TextRender(std::string text, float x, float y, float scale, glm::vec4 color)
{
	glUseProgram(program[FONT_PART]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	for (auto iter = text.begin(); iter != text.end(); iter++) {
		XCCharacter CharacterTemp = XCCharacterGroup[*iter];
		float xpos = x + CharacterTemp.offset.x * scale;
		float ypos = y - (CharacterTemp.size.y - CharacterTemp.offset.y) * scale;

		float w = CharacterTemp.size.x * scale;
		float h = CharacterTemp.size.y * scale;
		GLfloat draw_vertex[6][4] = {//似乎进行了上下翻转
		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos,     ypos,       0.0, 1.0 },
		   { xpos + w, ypos,       1.0, 1.0 },

		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos + w, ypos,       1.0, 1.0 },
		   { xpos + w, ypos + h,   1.0, 0.0 }
		};
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao[FONT_PART]);
		glBindTexture(GL_TEXTURE_2D, CharacterTemp.tbo);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[FONT_PART]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(draw_vertex), draw_vertex);
		glm::mat4 projection = glm::ortho(0.0f, 730.0f, 0.0f, 720.0f);
		auto convert_mat_loc = glGetUniformLocation(program[FONT_PART], "convert_mat");
		auto font_color_loc = glGetUniformLocation(program[FONT_PART], "font_color");
		glUniform4f(font_color_loc, color.x, color.y, color.z, color.w);
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (CharacterTemp.advance >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void xc_se::XCDialog::TextUnicodeRender(std::wstring text, float x, float y, float scale, glm::vec4 color)
{
	glUseProgram(program[FONT_PART]);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	XCUniformChar *CharacterTemp = XCRenderStringGroup[text];
	if (CharacterTemp == nullptr) return;
	for (int i = 0; i < CharacterTemp->tboGroup.size();i++) {
		float xpos = x + CharacterTemp->offsetGroup[i].x * scale;
		float ypos = y - (CharacterTemp->sizeGroup[i].y - CharacterTemp->offsetGroup[i].y) * scale;

		float w = CharacterTemp->sizeGroup[i].x * scale;
		float h = CharacterTemp->sizeGroup[i].y * scale;
		GLfloat draw_vertex[6][4] = {
		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos,     ypos,       0.0, 1.0 },
		   { xpos + w, ypos,       1.0, 1.0 },

		   { xpos,     ypos + h,   0.0, 0.0 },
		   { xpos + w, ypos,       1.0, 1.0 },
		   { xpos + w, ypos + h,   1.0, 0.0 }
		};
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(vao[FONT_PART]);
		glBindTexture(GL_TEXTURE_2D, CharacterTemp->tboGroup[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[FONT_PART]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(draw_vertex), draw_vertex);
		glm::mat4 projection = glm::ortho(0.0f, 730.0f, 0.0f, 720.0f);
		auto convert_mat_loc = glGetUniformLocation(program[FONT_PART], "convert_mat");
		auto font_color_loc = glGetUniformLocation(program[FONT_PART], "font_color");
		glUniform4f(font_color_loc, color.x, color.y, color.z, color.w);
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(projection));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		x += (CharacterTemp->advanceGroup[i] >> 6) * scale;
	}
	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}
void xc_se::XCDialog::DialogRender()
{

	//TextRender("XCSTG FreeType测试", 25.0f, 25.0f, 1.0f, glm::vec4(0.5, 0.8f, 0.2f,1.0f));
	TextUnicodeRender(L"XCSTG 测试", 25.0f, 25.0f, 0.8f, glm::vec4(0.5, 0.8f, 0.2f, 1.0f));
}

void xc_se::XCDialog::DialogRelease()
{
	glDeleteVertexArrays(3, vao);
	glDeleteBuffers(3, vbo);
}
