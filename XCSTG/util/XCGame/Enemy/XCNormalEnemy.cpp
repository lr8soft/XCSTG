#include "../../ImageLoader.h"
#include "../../ShaderReader.h"
#include "../../XCShape/XCDefaultShape.h"
#include "XCNormalEnemy.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
bool xc_game::XCEnemy::have_resource_init = false;//static memeber init
GLuint xc_game::XCEnemy::tbo[2];
float xc_game::XCEnemy::GetCoordY()
{
	return slope_k * deltaX + parameter_b;
}
void xc_game::XCEnemy::ShaderInit()
{
	ShaderReader EYLoader;
	EYLoader.load_from_file("shader/enemy/normal.vert",GL_VERTEX_SHADER);
	EYLoader.load_from_file("shader/enemy/normal.frag",GL_FRAGMENT_SHADER);
	EYLoader.link_all_shader();
	program = EYLoader.get_program();
}

void xc_game::XCEnemy::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex,GL_STATIC_DRAW);
	auto vert_pos = glGetAttribLocation(program,"in_vert");
	glVertexAttribPointer(vert_pos,2,GL_FLOAT,GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(vert_pos);
}

void xc_game::XCEnemy::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader FairyLoader, HairBallLoader;
		FairyLoader.LoadTextureData("image/enemy/fairy.png");
		HairBallLoader.LoadTextureData("image/enemy/hairball.png");
		tbo[FAIRY] = FairyLoader.GetTBO();
		tbo[HAIRBALL] = HairBallLoader.GetTBO();
		have_resource_init = true;
		glUniform1i(glGetUniformLocation(program,"tex"),0);
	}
	SetUseTBO(tbo[FAIRY]);//Default fairy
}

void xc_game::XCEnemy::SetUseTBO(GLuint tbo)
{
	use_tbo = tbo;
}

void xc_game::XCEnemy::CheckShouldEnd()
{
	if (should_positive) {
		if (deltaX > destX) {
			should_render = false;
		}
	}
	else {
		if (destX > deltaX) {
			should_render = false;
		}
	}
	if (deltaX>1|| deltaX<-1|| deltaY>1|| deltaY<-1) {
		should_render = false;
	}
	if (is_dead) {
		should_render = false;
	}
}

void xc_game::XCEnemy::OGLSettingRenderStart()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void xc_game::XCEnemy::OGLSettingRenderEnd()
{
	glDisable(GL_BLEND);
}

void xc_game::XCEnemy::EnemyInit()
{
	ShaderInit();
	BufferInit();
	TextureInit();
	dead_se.SpecialEffectInit(dead_se.RingLightColor);
	damage_se.SpecialEffectInit(damage_se.RingDeepColor);
	enemy_life = full_enemy_life;
	be_attack = false;
}

void xc_game::XCEnemy::EnemyRender(float nowFrame)
{
	float currentFrame = nowFrame;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	if (should_render) {
		OGLSettingRenderStart();
		if (is_dead) {
			if (dead_se.SpecialEffectRender(deltaX,deltaY,deltaZ))//Íê³É±¬Õ¨äÖÈ¾
				should_render = false;
		}
		else {
			glUseProgram(program);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, use_tbo);
			glm::mat4 transform_mat;
			if (first_move) {
				transform_mat = glm::translate(transform_mat, glm::vec3(deltaX, deltaY, deltaZ));
				first_move = false;
			}
			else {
				transform_mat = glm::translate(transform_mat, glm::vec3(deltaX, GetCoordY(), deltaZ));
				deltaY = GetCoordY();
			}
			if (should_positive)
				deltaX += velocity * deltaTime;
			else
				deltaX -= velocity * deltaTime;
			transform_mat = glm::scale(transform_mat, glm::vec3(0.06f, 0.06f, 0.06f));
			auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
			glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
			glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
			if (be_attack) {
			//	damage_se.SpecialEffectRender(deltaX, deltaY, deltaZ);
				be_attack=false;
			}
			else {
			//	damage_se.SpecialEffectRenderFinish();
			}
			CheckShouldEnd();
		}
		OGLSettingRenderEnd();	
	}


}

void xc_game::XCEnemy::SetGenerateAndVelocity(float x, float y, float z, float dx, float dy, float dz, float v)
{
	if (!should_render) {
		destX = dx, destY = dy, destZ = dz;
		deltaX = x, deltaY = y, deltaZ = z;
		velocity = v;
		slope_k = (destY - deltaY) / (destX - deltaX);
		parameter_b = deltaY - slope_k * deltaX;
		should_render = true;
		is_dead = false;
		if (destX > deltaX)
			should_positive = true;
		else
			should_positive = false;
	}
}

void xc_game::XCEnemy::SetDead()
{
	//should_render = false;
	is_dead = true;
}

void xc_game::XCEnemy::SetDamage(float damage)
{
	enemy_life -= damage;
	if (enemy_life <=0) {
		is_dead = true;
	}
	else {
		be_attack = true;
	}

		//damage_se.SpecialEffectRender(deltaX,deltaY,deltaZ);
}

bool xc_game::XCEnemy::IsRendering()
{
	return should_render;
}

bool xc_game::XCEnemy::IsDead()
{
	return is_dead;
}

float ** xc_game::XCEnemy::GetNowCoord()
{
	float *coord_temp[3];
	*(coord_temp) = &deltaX;
	*(coord_temp+1) = &deltaY;
	*(coord_temp+2) = &deltaZ;
	return coord_temp;
}
