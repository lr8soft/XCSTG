#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCRing.h"
using namespace xc_ogl;
GLuint xc_se::XCRing::tbo[4];
GLuint xc_se::XCRing::program_static;
bool xc_se::XCRing::have_tbo_init = false;
bool xc_se::XCRing::have_program_init = false;
void xc_se::XCRing::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader SELoader;
		SELoader.loadFromFile("shader/se/GeneralSE.vert", GL_VERTEX_SHADER);
		SELoader.loadFromFile("shader/se/GeneralSE.frag", GL_FRAGMENT_SHADER);
		SELoader.linkAllShader();
		program_static = SELoader.getProgramHandle();
		have_program_init = true;
	}
	program = program_static;
}
void xc_se::XCRing::TextureInit()
{
	if (!have_tbo_init) {
		ImageLoader SELoader,SBLoader,PlayerSELoader,BossSELoader;
		SELoader.loadTextureFromFile("image/se/ring.png");
		SBLoader.loadTextureFromFile("image/se/ring_2.png");
		PlayerSELoader.loadTextureFromFile("image/se/pexplode.png");
		BossSELoader.loadTextureFromFile("image/se/explode.png");
		tbo[RingLightColor] = SELoader.getTextureBufferObjectHandle();
		tbo[RingDeepColor] = SBLoader.getTextureBufferObjectHandle();
		tbo[RingPlayerDead] = PlayerSELoader.getTextureBufferObjectHandle();
		tbo[RingBossDead] = BossSELoader.getTextureBufferObjectHandle();
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
void xc_se::XCRing::SpecialEffectReset()
{
	XCSpecialEffect::SpecialEffectReset();
	switch (ring_type) {
	case RingBossDead:
		RenderSize = 0.3f;break;
	case RingPlayerDead:
		RenderSize = 0.3f; break;
	default:
		RenderSize = 0.015; break;
	}
}

void xc_se::XCRing::SpecialEffectRelease()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
}

void xc_se::XCRing::SpecialEffectInit(int type)
{
	ring_type = type;
	SETimer.Clear();
	ShaderInit();
	TextureInit();
	BufferInit();
	switch (ring_type) {
	case RingBossDead:
		RenderSize = 0.3f;
		RenderTime = 0.12f;
		seaudio.MusicResourceInit(seaudio.BOSS_DEAD_EFFECT);
		break;
	case RingPlayerDead:
		RenderSize = 0.3f;
		RenderTime = 0.12f;
		seaudio.MusicResourceInit(seaudio.PLAYER_DEAD_EFFECT);
		break;
	default:
		RenderSize = 0.015;
		RenderTime = 0.2f;
		seaudio.MusicResourceInit(seaudio.ENEMY_DEAD_EFFECT);
		break;
	}
}

bool xc_se::XCRing::SpecialEffectRender(float x,float y,float z)
{
	SETimer.Tick();
	if (SETimer.getAccumlateTime()< RenderTime) {
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D,tbo[ring_type]);
		glm::mat4 transform_mat,temp_mat;
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		switch (ring_type) {
		case RingPlayerDead:
			break;
		case RingBossDead:
			temp_mat = glm::translate(temp_mat, glm::vec3(x, y, z));
			temp_mat = glm::rotate(temp_mat, glm::degrees(rand() / RAND_MAX * 180.0f), glm::vec3(0,0,1));
			temp_mat = glm::scale(temp_mat, glm::vec3(RenderSize));
			glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(temp_mat));
			glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
			break;
		default:
			break;
		}
		transform_mat = glm::translate(transform_mat, glm::vec3(x, y, z));
		transform_mat = glm::scale(transform_mat, glm::vec3(RenderSize*render_abs_width /3, RenderSize*render_abs_height / 3, RenderSize/ 3));
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / 2*sizeof(float));
		seaudio.MusicPlay();
		switch (ring_type) {
		case RingPlayerDead:
			RenderSize += 3.0f* SETimer.getDeltaFrame(); break;
		case RingBossDead:
			RenderSize += 0.06f; break;
		default:
			RenderSize += 0.03f; break;
		}
		return false;
	}
	else {
		SpecialEffectReset();
		return true;
	}
}
