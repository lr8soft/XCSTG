#include "XCGameInfoSlot.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <GL3/gl3w.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
using namespace xc_se;
bool xc_se::XCGameInfoSlot::have_resource_init = false;
bool xc_se::XCGameInfoSlot::have_program_init = false;
bool xc_se::XCGameInfoSlot::have_buffer_init = false;
GLuint xc_se::XCGameInfoSlot::vao[3];
GLuint xc_se::XCGameInfoSlot::vbo[3];
GLuint xc_se::XCGameInfoSlot::tbo[3];
GLuint xc_se::XCGameInfoSlot::program[3];
void xc_se::XCGameInfoSlot::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader BossHP, SpellCardSlot,RenderCoverPlane;
		BossHP.loadFromFile("Shader/se/BossSE.vert", GL_VERTEX_SHADER);
		BossHP.loadFromFile("Shader/se/BossSE.frag", GL_FRAGMENT_SHADER);
		BossHP.linkAllShader();
		program[HP_SLOT] = BossHP.getProgramHandle();

		SpellCardSlot.loadFromFile("Shader/general/generalShader.vert", GL_VERTEX_SHADER);
		SpellCardSlot.loadFromFile("Shader/general/generalShader.frag", GL_FRAGMENT_SHADER);
		SpellCardSlot.linkAllShader();
		program[SPELLCARD_SLOT] = SpellCardSlot.getProgramHandle();

		RenderCoverPlane.loadFromFile("Shader/info/renderCover.vert", GL_VERTEX_SHADER);
		RenderCoverPlane.loadFromFile("Shader/info/renderCover.frag", GL_FRAGMENT_SHADER);
		RenderCoverPlane.linkAllShader();
		program[RENDER_PLANE] = RenderCoverPlane.getProgramHandle();
		have_program_init = true;
	}

}

void xc_se::XCGameInfoSlot::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader spellCardSlot,renderGameCoverPlane;
		spellCardSlot.loadTextureFromFile("Image/font/spellcard_word.png");
		renderGameCoverPlane.loadTextureFromFile("Image/bg/testbg_ÇÖÉ¾.jpeg");
		tbo[SPELLCARD_SLOT] = spellCardSlot.getTextureBufferObjectHandle();
		tbo[RENDER_PLANE] = renderGameCoverPlane.getTextureBufferObjectHandle();
		have_resource_init = true;
	}
}

void xc_se::XCGameInfoSlot::BufferInit()
{
	if (!have_buffer_init) {
		glGenVertexArrays(3, vao);
		glGenBuffers(3, vbo);
		have_buffer_init = true;
	}	
}

void xc_se::XCGameInfoSlot::SetInfo(float * hp, float * mhp, int rtime, int sccount)
{
	BossHP = hp;
	BossMaxHP=mhp;
	RemainingTime = rtime;
	SpellCardCount = sccount;
}

void xc_se::XCGameInfoSlot::SetAbsWidthAndHeight(float absW, float absH)
{
	render_abs_height = absH;
	render_abs_width = absW;
}

void xc_se::XCGameInfoSlot::BossHPInit()
{
	SpecialEffectInit();
	glBindVertexArray(vao[HP_SLOT]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[HP_SLOT]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);
	auto in_vert_loc = glGetAttribLocation(program[HP_SLOT], "in_coord");
	glVertexAttribPointer(in_vert_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(in_vert_loc);
	glUniform1i(glGetUniformLocation(program[HP_SLOT], "tex"), 0);
}

void xc_se::XCGameInfoSlot::SpecialEffectInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

bool xc_se::XCGameInfoSlot::SpellCardInfoRender(int type)
{
	spellCardSlotTimer.Tick();
	float accumlateTime = spellCardSlotTimer.getAccumlateTime();
	if (accumlateTime <3.0f) {
		glUseProgram(program[SPELLCARD_SLOT]);
		glBindVertexArray(vao[SPELLCARD_SLOT]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[SPELLCARD_SLOT]);
		glBufferSubData(GL_ARRAY_BUFFER, 0, 24 * sizeof(float), GetSpecificTexture(1, 3, 1, 1+ type));
		glBindTexture(GL_TEXTURE_2D, tbo[SPELLCARD_SLOT]);
		glm::mat4 transform_mat;
		transform_mat = glm::translate(transform_mat, glm::vec3(0.0f, 0.6f, 0.0f));
		transform_mat = glm::scale(transform_mat, glm::vec3(0.8f*render_abs_width, 0.08f*render_abs_height, 0.0f));
		auto convert_mat_loc = glGetUniformLocation(program[SPELLCARD_SLOT], "convert_mat");
		auto gradient_number_loc = glGetUniformLocation(program[SPELLCARD_SLOT], "gradient_number");
		if (accumlateTime < 1.0f) {
			glUniform1f(gradient_number_loc, 1.0f-accumlateTime);
		}
		else if (accumlateTime>=1.0f&&accumlateTime<2.5f) {
			glUniform1f(gradient_number_loc, 0.0f);
		}
		else {
			glUniform1f(gradient_number_loc, accumlateTime/3.0f);
		}
		
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
		glUseProgram(0);
		return false;
	}
	else {
		spellCardSlotTimer.Clear();
		return true;
	}

}
void xc_se::XCGameInfoSlot::CoveredPlaneInit()
{
	SpecialEffectInit();
	auto vertex_info_loc = glGetAttribLocation(program[RENDER_PLANE], "vertex_info");
	glBindVertexArray(vao[RENDER_PLANE]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[RENDER_PLANE]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex_with_texture), covered_plane_vertex_with_texture, GL_STATIC_DRAW);
	glVertexAttribPointer(vertex_info_loc, 4, GL_FLOAT, GL_FALSE, 0, (void*)(0));
	glEnableVertexAttribArray(vertex_info_loc);
	glUniform1i(glGetUniformLocation(program[RENDER_PLANE], "tex"), 0);
}
void xc_se::XCGameInfoSlot::CoveredPlaneRender(float absW, float absH)
{
	glUseProgram(program[RENDER_PLANE]);
	glBindVertexArray(vao[RENDER_PLANE]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[RENDER_PLANE]);
	glBindTexture(GL_TEXTURE_2D, tbo[RENDER_PLANE]);
	auto abs_loc=glGetUniformLocation(program[RENDER_PLANE],"render_rate");
	glUniform2f(abs_loc, absW, absH);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
	glUseProgram(0);
}
bool xc_se::XCGameInfoSlot::BossHPRender()
{
	glUseProgram(program[HP_SLOT]);
	glBindVertexArray(vao[HP_SLOT]);
	glBindBuffer(GL_ARRAY_BUFFER,vbo[HP_SLOT]);
	glm::mat4 transform_mat;
	transform_mat = glm::translate(transform_mat, glm::vec3(0.0f,0.96f,0.0f));
	transform_mat = glm::scale(transform_mat, glm::vec3((*BossHP) / (*BossMaxHP)*0.8f*render_abs_width,0.008f*render_abs_height,0.0f));
	auto transfom_mat_loc = glGetUniformLocation(program[HP_SLOT], "transform_mat");
	auto time_loc = glGetUniformLocation(program[HP_SLOT], "time");
	glUniformMatrix4fv(transfom_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
	glUniform1f(time_loc, glfwGetTime());
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindVertexArray(0);
	glUseProgram(0);
	return false;
}

void xc_se::XCGameInfoSlot::SpellCardInfoInit()
{
	SpecialEffectInit();
	auto render_pos_loc = glGetAttribLocation(program[SPELLCARD_SLOT], "render_pos");
	auto tex_pos_loc = glGetAttribLocation(program[SPELLCARD_SLOT], "tex_pos");
	glBindVertexArray(vao[SPELLCARD_SLOT]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[SPELLCARD_SLOT]);
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(render_pos_loc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
	glVertexAttribPointer(tex_pos_loc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(render_pos_loc);
	glEnableVertexAttribArray(tex_pos_loc);
	glUniform1i(glGetUniformLocation(program[SPELLCARD_SLOT], "tex"), 0);
}


void xc_se::XCGameInfoSlot::SpecialEffectRelease()
{
	glDeleteVertexArrays(sizeof(vao)/sizeof(GLuint),vao);
	glDeleteBuffers(sizeof(vbo) / sizeof(GLuint), vbo);
}
