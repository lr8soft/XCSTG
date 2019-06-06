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
		EYLoader.loadFromFile("shader/enemy/enemyGeneral.vert", GL_VERTEX_SHADER);
		EYLoader.loadFromFile("shader/enemy/enemyGeneral.frag", GL_FRAGMENT_SHADER);
		EYLoader.linkAllShader();
		program_static = EYLoader.getProgramHandle();
		have_program_init = true;
	}
	program = program_static;
}

void xc_game::XCNormalEnemy::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1,&vbo);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, nullptr, GL_DYNAMIC_DRAW);
	auto display_coord_pos = glGetAttribLocation(program, "display_coord");
	auto in_tex_coord_pos = glGetAttribLocation(program, "input_tex_pos");
	glVertexAttribPointer(display_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
	glVertexAttribPointer(in_tex_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(display_coord_pos);
	glEnableVertexAttribArray(in_tex_coord_pos);
}

void xc_game::XCNormalEnemy::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader FairyLoader, HairBallLoader;
		FairyLoader.loadTextureFromFile("image/enemy/fairy_tex.png");
		HairBallLoader.loadTextureFromFile("image/enemy/hairball.png");
		tbo[FAIRY] = FairyLoader.getTextureBufferObjectHandle();
		tbo[HAIRBALL] = HairBallLoader.getTextureBufferObjectHandle();
		have_resource_init = true;
	}
	glUniform1i(glGetUniformLocation(program,"tex"),0);
	SetUseTBO(tbo[FAIRY]);//Default fairy

	EachStateInterval = 3.8;/*Texture data init*/
	AttackInterval = 0.060f;
	StandByInterval = 0.040f;
	MovingInterval = 0.080f;
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
		if (IsDead()) {
			dead_se.SetAbsWidthAndHeight(right, top);
			if (dead_se.SpecialEffectRender(NowX, NowY, NowZ))//ÕÍ≥…±¨’®‰÷»æ
				should_render = false;
		}
		else {
			glUseProgram(program);
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
					NowX = coordx_func(NowX, NowY,enemyTimer, velocity, 0)*right;
					NowY = coordy_func(NowX, NowY,enemyTimer, velocity, 0)*top;
					break;
			}
			glBindVertexArray(vao);
			glBindBuffer(GL_ARRAY_BUFFER,vbo);
			switch (EnemyNowState) {
			case ENEMY_MOVING:
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 24, GetSpecificTexture(8, 1, 5+(size_t)EnemySameStateTime, 1));
				break;
			case ENEMY_STANDBY:
			case ENEMY_ATTACK:
				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 24, GetSpecificTexture(8, 1, 1 + (size_t)EnemySameStateTime, 1));
				break;
			}
			transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
			transform_mat = glm::scale(transform_mat, glm::vec3(0.06f*right, 0.06f*top, 0.06f));
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