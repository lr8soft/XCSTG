#include "../../util/ImageLoader.h"
#include "../../util/ShaderReader.h"
#include "../../XCShape/XCDefaultShape.h"
#include "XCNormalEnemy.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
bool xc_game::XCEnemy::have_resource_init = false;//static memeber init
bool xc_game::XCEnemy::have_program_init = false;
GLuint xc_game::XCEnemy::tbo[2];
GLuint xc_game::XCEnemy::program_static;
float xc_game::XCEnemy::GetCoordY()
{
	return slope_k * NowX + parameter_b;
}
void xc_game::XCEnemy::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader EYLoader;
		EYLoader.load_from_file("shader/enemy/normal.vert", GL_VERTEX_SHADER);
		EYLoader.load_from_file("shader/enemy/normal.frag", GL_FRAGMENT_SHADER);
		EYLoader.link_all_shader();
		program_static = EYLoader.get_program();
		have_program_init = true;
	}
	program = program_static;
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
	}
	glUniform1i(glGetUniformLocation(program,"tex"),0);
	SetUseTBO(tbo[FAIRY]);//Default fairy
}

void xc_game::XCEnemy::SetUseTBO(GLuint tbo)
{
	use_tbo = tbo;
}

void xc_game::XCEnemy::CheckShouldEnd()
{
	if (should_positive) {
		if (NowX > destX) {
			should_render = false;
		}
	}
	else {
		if (destX > NowX) {
			should_render = false;
		}
	}
	if (NowX>1.1|| NowX<-1.1|| NowY>1.1|| NowY<-1.1) {
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

void xc_game::XCEnemy::EnemyInit(size_t type)
{
	ShaderInit();
	BufferInit();
	TextureInit();
	dead_se.SpecialEffectInit(dead_se.RingLightColor);
	damage_se.SpecialEffectInit(damage_se.RingDeepColor);
	enemy_life = full_enemy_life;
	be_attack = false;
	move_type = type;
}

void xc_game::XCEnemy::EnemyRender(float nowFrame)
{
	float currentFrame = nowFrame;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
	if (should_render) {
		OGLSettingRenderStart();
		if (is_dead) {
			if (dead_se.SpecialEffectRender(NowX, NowY, NowZ))//Íê³É±¬Õ¨äÖÈ¾
				should_render = false;
		}
		else {
			glUseProgram(program);
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, use_tbo);
			glm::mat4 transform_mat;
			switch (move_type) {
				case SINGLE_COORD:
					if (first_move) {
						transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
						first_move = false;
					}
					else {
						transform_mat = glm::translate(transform_mat, glm::vec3(NowX, GetCoordY(), NowZ));
						NowY = GetCoordY();
					}
					if (should_positive)
						NowX += velocity * cosf(parameter_theta)* deltaTime;
					else
						NowX -= velocity * cosf(parameter_theta)* deltaTime;
					
					break;
				case FUNCTION_PATH:
					NowX = coordx_func(NowX, nowFrame);
					NowY = coordy_func(NowX, NowY);
					transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
					break;
			}
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
		NowX = x, NowY = y, NowZ = z;
		velocity = v;
		slope_k = (destY - NowY) / (destX - NowX);
		parameter_b = NowY - slope_k * NowX;
		should_render = true;
		is_dead = false;
		if(destX != NowX)
			parameter_theta = acosf(abs(destX - NowX) / sqrtf(pow(destX - NowX, 2) + pow(destY - NowY, 2)));
		else
			parameter_theta = 3.1415926f / 2.0f;

		if (destX > NowX)
			should_positive = true;
		else
			should_positive = false;
	}
}

void xc_game::XCEnemy::SetMoveFunc(std::function<float(float, float)> xfunc, std::function<float(float, float)> yfunc)
{
	coordx_func = xfunc; coordy_func = yfunc;
}

void xc_game::XCEnemy::SetStartPoint(float x, float y, float z)
{
	NowX = x; NowY = y; NowZ = z;
	have_start_pos = true;
}

void xc_game::XCEnemy::SetVelocity(float v)
{
	velocity = v;
	have_velocity = true;
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
	*(coord_temp) = &NowX;
	*(coord_temp+1) = &NowY;
	*(coord_temp+2) = &NowZ;
	return coord_temp;
}
