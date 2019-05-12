#include "../ImageLoader.h"
#include "../ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCRing.h"
using namespace xc_ogl;
GLuint xc_se::XCRing::tbo[2];
bool xc_se::XCRing::have_tbo_init = false;
void xc_se::XCRing::ShaderInit()
{
	ShaderReader SELoader;
	SELoader.load_from_file("shader/se/GeneralSE.vert",GL_VERTEX_SHADER);
	SELoader.load_from_file("shader/se/GeneralSE.frag",GL_FRAGMENT_SHADER);
	SELoader.link_all_shader();
	program = SELoader.get_program();
	glUseProgram(program);
}
void xc_se::XCRing::TextureInit()
{
	if (!have_tbo_init) {
		ImageLoader SELoader,SBLoader;
		SELoader.LoadTextureData("image/se/ring.png");
		SBLoader.LoadTextureData("image/se/ring_2.png");
		tbo[RingLightColor] = SELoader.GetTBO();
		tbo[RingDeepColor] = SBLoader.GetTBO();
		have_tbo_init = true;
	}
	glUniform1i(glGetUniformLocation(program,"tex"),0);
}
void xc_se::XCRing::BufferInit()
{
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(covered_plane_vertex), covered_plane_vertex,GL_STATIC_DRAW);
	auto vert_loc = glGetAttribLocation(program, "in_coord");
	glVertexAttribPointer(vert_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(vert_loc);
}
void xc_se::XCRing::RingReset()
{
	first_run = true;
	NowSize = 0.015;
	NowTime = 0;
}
void xc_se::XCRing::SpecialEffectInit(int type)
{
	ring_type = type;
	NowSize= 0.015;
	ShaderInit();
	TextureInit();
	BufferInit();
}

bool xc_se::XCRing::SpecialEffectRender(float x,float y,float z)
{
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	if (first_run) {
		deltaTime = 0.013;
		first_run = false;
	}
	if (NowTime< alive_time) {
		NowTime += deltaTime;
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,tbo[ring_type]);
		glm::mat4 transform_mat;
		transform_mat = glm::translate(transform_mat, glm::vec3(x, y, z));
		transform_mat = glm::scale(transform_mat, glm::vec3(NowSize));
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
		if(ring_type== RingLightColor)
			NowSize +=0.005;
		else {
			NowSize += 0.004;
			NowTime += deltaTime;
		}
			
		return false;
	}
	else {
		RingReset();
		return true;
	}
}
