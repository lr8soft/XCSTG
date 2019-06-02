#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCParticle.h"
#include <GL3/gl3w.h>
using namespace xc_ogl;
GLuint xc_se::XCParticle::tbo[2];
GLuint xc_se::XCParticle::program_static;
bool xc_se::XCParticle::have_tbo_init = false;
bool xc_se::XCParticle::have_program_init = false;
void xc_se::XCParticle::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader SELoader;
		SELoader.loadFromFile("shader/particle/particleGeneral.vert", GL_VERTEX_SHADER);
		SELoader.loadFromFile("shader/particle/particleGeneral.frag", GL_FRAGMENT_SHADER);
		SELoader.linkAllShader();
		program_static = SELoader.getProgramHandle();
		have_program_init = true;
	}
	program = program_static;
}

void xc_se::XCParticle::TextureInit()
{
	if (!have_tbo_init) {
		for (int i = 0; i < sizeof(tbo)/sizeof(GLuint);i++) {
			GLuint tbo_temp;
			glGenTextures(1, &tbo_temp);
			tbo[i] = tbo_temp;
			ImageLoader TexLoader(GL_TEXTURE_2D, tbo_temp);
			switch (i) 
			{
				case CIRCLE_PARTICLE:
					TexLoader.loadTextureFromFile("Image/particle/uniform_particle.png"); break;
				case MOVING_PARTICLE:
				default:
					TexLoader.loadTextureFromFile("Image/particle/uniform_particle.png"); break;
			}
		}
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
	glBufferData(GL_ARRAY_BUFFER,4*sizeof(float),GetPointSpriteVertex(15.0f),GL_STATIC_DRAW);
	auto coord_loc = glGetAttribLocation(program, "display_coord");
	glVertexAttribPointer(coord_loc, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), nullptr);
	glEnableVertexAttribArray(coord_loc);
	RenderSize = 15.0f;
}


void xc_se::XCParticle::SpecialEffectInit(int type)
{
	XCSpecialEffect::SpecialEffectInit(type);
	particle_type = type;
}

bool xc_se::XCParticle::SpecialEffectRender(float x, float y, float z)
{	
	XCSpecialEffect::SpecialEffectRender(x, y, z);
	if (should_se_render) {
		SETimer.Tick();
		is_rendering = true;
		if (SETimer.getAccumlateTime() < RenderTime)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE, GL_ONE);
			glUseProgram(program);
			glEnable(GL_PROGRAM_POINT_SIZE);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tbo[particle_type]);
			
			auto view_mat_loc = glGetUniformLocation(program, "view_mat");
			auto size_loc = glGetUniformLocation(program, "point_size");
			auto offset_loc = glGetUniformLocation(program,"offset");
			glm::mat4 view_mat;
			view_mat = glm::translate(view_mat, glm::vec3(x, y, z));
			glUniformMatrix4fv(view_mat_loc, 1, GL_FALSE, glm::value_ptr(view_mat));
			glUniform1i(offset_loc,ParticleOffset);
			if(z>0)
				glUniform1f(size_loc,RenderSize/z);//glUniform1f(size_loc,15.0f/z);
			else
				glUniform1f(size_loc, RenderSize);//glUniform1f(size_loc, 15.0f);
			glDrawArrays(GL_POINTS, 0, 1);
			glDisable(GL_PROGRAM_POINT_SIZE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else {
			SpecialEffectReset();
			should_se_render = false;
			is_rendering = false;
			return true;
		}
	}
	return false;
}

void xc_se::XCParticle::SpecialEffectReset()
{
	XCSpecialEffect::SpecialEffectReset();
	is_rendering = false;
}

void xc_se::XCParticle::SpecialEffectRelease()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}


