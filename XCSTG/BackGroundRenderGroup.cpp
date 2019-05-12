#include "BackGroundRenderGroup.h"
#include "util/ImageLoader.h"
#include "util/ShaderReader.h"
#include "util/XCShape/XCDefaultShape.h"
using namespace xc_ogl;
void BackGroundRenderGroup::BufferLoader()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);

	auto vertex_loc = glGetAttribLocation(program, "in_vertex");
	glVertexAttribPointer(vertex_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(vertex_loc);
}

void BackGroundRenderGroup::TextureLoader()
{
	ImageLoader BGLoader;
	BGLoader.LoadTextureData("image/bg/eff05.png");
	tbo[0] = BGLoader.GetTBO();
	BackGroundTexSet(tbo[0]);
	glUniform1i(glGetUniformLocation(program,"tex"),0);
}

void BackGroundRenderGroup::ShaderLoader()
{
	ShaderReader glbg;
	glbg.load_from_file("shader/vertex.glsl", GL_VERTEX_SHADER);
	glbg.load_from_file("shader/fragment.glsl", GL_FRAGMENT_SHADER);
	glbg.link_all_shader();
	program = glbg.get_program();
}

void BackGroundRenderGroup::BackGroundTexSet(GLuint tbo)
{
	use_tbo = tbo;
}

void BackGroundRenderGroup::GroupInit()
{
	ShaderLoader();
	BufferLoader();
	TextureLoader();
}

void BackGroundRenderGroup::GroupRender()
{
	if (RenderBG) {
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, use_tbo);
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
	}
}

void BackGroundRenderGroup::SetRender(bool dorender)
{
	RenderBG = dorender;
}

void BackGroundRenderGroup::GroupKeyCheck(GLFWwindow * screen)
{
	if (glfwGetKey(screen, GLFW_KEY_B) == GLFW_PRESS) {//GLFW_PRESS
		RenderBG = !RenderBG;
	}
}
