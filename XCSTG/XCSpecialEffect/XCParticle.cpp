#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCParticle.h"
#include <GL3/gl3w.h>
using namespace xc_ogl;
GLuint xc_se::XCParticle::tbo[3];
GLuint xc_se::XCParticle::program_static;
bool xc_se::XCParticle::have_tbo_init = false;
bool xc_se::XCParticle::have_program_init = false;
void xc_se::XCParticle::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader SELoader;
		SELoader.load_from_file("shader/particle/particleGeneral.vert", GL_VERTEX_SHADER);
		SELoader.load_from_file("shader/particle/particleGeneral.frag", GL_FRAGMENT_SHADER);
		SELoader.link_all_shader();
		program_static = SELoader.get_program();
		have_program_init = true;
	}
	program = program_static;
}

void xc_se::XCParticle::TextureInit()
{
	if (!have_tbo_init) {
		ImageLoader TexLoader, TexLoader1, TexLoader2;
		TexLoader.LoadTextureData("Image/particle/uniform_particle.png");
		TexLoader1.LoadTextureData("Image/particle/uniform_tex.png");
		TexLoader2.LoadTextureData("Image/particle/test_se2.png");
		tbo[0] = TexLoader.GetTBO();
		tbo[1] = TexLoader1.GetTBO();
		tbo[2] = TexLoader2.GetTBO();
		have_tbo_init = true;
	}
	glUniform1i(glGetUniformLocation(program, "tex"), 0);
}

void xc_se::XCParticle::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,4*sizeof(float),GetPointSpriteVertex(10.0f),GL_STATIC_DRAW);
	auto coord_loc = glGetAttribLocation(program, "display_coord");
	glVertexAttribPointer(coord_loc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), nullptr);
	glEnableVertexAttribArray(coord_loc);
	RenderSize = 0.015f;
}

xc_se::XCParticle::XCParticle()
{
}

xc_se::XCParticle::~XCParticle()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void xc_se::XCParticle::SpecialEffectInit(int type)
{
	XCSpecialEffect::SpecialEffectInit(type);
	particle_type = type;
}

bool xc_se::XCParticle::SpecialEffectRender(float x, float y, float z)
{
	SETimer.Tick();
	//if (SETimer.getAccumlateTime() < RenderTime)
	//{
	glEnable(GL_BLEND);
	//glBlendFunc(GL_ONE, GL_ONE);
		glUseProgram(program);
		glEnable(GL_PROGRAM_POINT_SIZE);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tbo[2]);
		glm::mat4 transform_mat;
		auto rand_loc		 = glGetUniformLocation(program, "rand");
		auto convert_mat_loc = glGetUniformLocation(program, "transform_mat");
		transform_mat = glm::translate(transform_mat, glm::vec3(x, y+sin(SETimer.getAccumlateTime()), z));
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glUniform1f(rand_loc, SETimer.getAccumlateTime());

		glDrawArrays(GL_POINTS, 0, 6);
		glDisable(GL_PROGRAM_POINT_SIZE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//	}
	//else {
	//	SpecialEffectReset();
	//	return true;
	//}
	return false;
}

void xc_se::XCParticle::SpecialEffectReset()
{
	XCSpecialEffect::SpecialEffectReset();
}


