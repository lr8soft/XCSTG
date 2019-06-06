#include "XCBackgroundStatic.h"
#include "../XCShape/XCDefaultShape.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
using namespace xc_ogl;
void XCBackgroundStatic::ShaderInit()
{
	ShaderReader ShaderLoader;
	ShaderLoader.loadFromFile("Shader/general/generalStaticBG.vert",GL_VERTEX_SHADER);
	ShaderLoader.loadFromFile("Shader/general/generalStaticBG.frag", GL_FRAGMENT_SHADER);
	ShaderLoader.linkAllShader();
	program = ShaderLoader.getProgramHandle();
	glUniform1i(glGetUniformLocation(program,"tex"),0);
}

void XCBackgroundStatic::TextureInit()
{
	if (tbo == -1) 
	{
		ImageLoader texLoader;
		texLoader.loadTextureFromFile(texturePath.c_str());
		tbo = texLoader.getTextureBufferObjectHandle();
	}
}

void XCBackgroundStatic::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER, 
		sizeof(covered_plane_vertex_with_texture), 
		GetCoveredPlaneWithTexVertex(render_abs_width,render_abs_height),
		GL_STATIC_DRAW
	);
	auto vertex_info_loc = glGetAttribLocation(program, "vertex_info");
	glVertexAttribPointer(vertex_info_loc, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(vertex_info_loc);
}

void XCBackgroundStatic::LoadBackGround(std::string tex_path)
{
	texturePath = tex_path;
}

void XCBackgroundStatic::LoadBackGround(GLuint textureHandle)
{
	tbo = textureHandle;
}

void XCBackgroundStatic::BackgroundRender()
{
	glUseProgram(program);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}

void XCBackgroundStatic::BackgroundRelease()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteTextures(1, &tbo);
	glDeleteProgram(program);
}
