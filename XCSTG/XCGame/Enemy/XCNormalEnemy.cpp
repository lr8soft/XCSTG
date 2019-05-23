#include "../../util/ImageLoader.h"
#include "../../util/ShaderReader.h"
#include "../../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "XCNormalEnemy.h"
using namespace xc_ogl;
bool xc_game::XCNormalEnemy::have_resource_init = false;//static memeber init
bool xc_game::XCNormalEnemy::have_program_init = false;
GLuint xc_game::XCNormalEnemy::tbo[2];
GLuint xc_game::XCNormalEnemy::program_static;
void xc_game::XCNormalEnemy::ShaderInit()
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

void xc_game::XCNormalEnemy::BufferInit()
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

void xc_game::XCNormalEnemy::TextureInit()
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
void xc_game::XCNormalEnemy::EnemyInit(size_t type)
{
	xc_game::XCEnemyBase::EnemyInit(type);
	enemy_type = NORMAL_ENEMY;
	dead_se.SpecialEffectInit(dead_se.RingLightColor);
	damage_se.SpecialEffectInit(damage_se.RingDeepColor);
	MaxLife = full_enemy_life;
	NowLife = full_enemy_life;
}

void xc_game::XCNormalEnemy::EnemyRender(float nowFrame)
{
	enemyTimer.Tick(nowFrame);
	XCEnemyBase::EnemyRender(nowFrame);
	if (should_render) {
		OGLSettingRenderStart();
		if (is_dead) {
			if (dead_se.SpecialEffectRender(NowX, NowY, NowZ))//ÕÍ≥…±¨’®‰÷»æ
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
					if (should_positive)
						NowX += velocity * cosf(parameter_theta)* enemyTimer.getDeltaFrame();
					else
						NowX -= velocity * cosf(parameter_theta)* enemyTimer.getDeltaFrame();
					NowY = GetCoordY();
					break;
				case FUNCTION_PATH:
					NowX = coordx_func(NowX, NowY, nowFrame, enemyTimer.getDeltaFrame(), velocity, 0);
					NowY = coordy_func(NowX, NowY, nowFrame, enemyTimer.getDeltaFrame(), velocity, 0);
					break;
			}
			transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
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