#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCParticle.h"
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
		for (int i = 0; i < sizeof(tbo) / sizeof(GLuint);i++) {
			ImageLoader TexLoader;
			switch (i) {
			case STAR_PARTICLE:
				TexLoader.LoadTextureData("Image/particle/uniform_tex.png");
				break;
			case CIRCLE_PARTICLE:
				TexLoader.LoadTextureData("Image/particle/uniform_tex.png");
				break;
			case MOVING_PARTICLE:
				TexLoader.LoadTextureData("Image/particle/moving_tex.png");
				break;
			default:
				TexLoader.LoadTextureData("Image/particle/uniform_tex.png");
				break;
			}
			tbo[i] = TexLoader.GetTBO();
		}
		have_tbo_init = true;
	}
	glUniform1i(glGetUniformLocation(program, "tex"), 0);
}

void xc_se::XCParticle::BufferInit()
{
	glUseProgram(program);
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,5*sizeof(float), GetPointSpriteVertex(0.0f,0.0f,1.0f),GL_STATIC_DRAW);
	auto coord_loc = glGetAttribLocation(program, "display_coord");
	auto tex_info_loc = glGetAttribLocation(program, "tex_info");
	glVertexAttribPointer(coord_loc, 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), nullptr);
	glVertexAttribPointer(tex_info_loc, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2*sizeof(float)));
	glEnableVertexAttribArray(coord_loc);
	glEnableVertexAttribArray(tex_info_loc);

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
}

bool xc_se::XCParticle::SpecialEffectRender(float x, float y, float z)
{
	SETimer.Tick();
	if (SETimer.getAccumlateTime() < RenderTime)
	{
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER,vbo);
		glm::mat4 transform_mat;
		auto convert_mat_loc = glGetUniformLocation(program, "convert_mat");
		transform_mat = glm::translate(transform_mat, glm::vec3(x, y, z));
		transform_mat = glm::scale(transform_mat, glm::vec3(RenderSize));
		glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_POINT, 0, 1);

	}
	else {
		SpecialEffectReset();
		return true;
	}
	return false;
}

void xc_se::XCParticle::SpecialEffectReset()
{
	XCSpecialEffect::SpecialEffectReset();
}


