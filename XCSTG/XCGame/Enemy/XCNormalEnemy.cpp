#include "../../util/ImageLoader.h"
#include "../../util/ShaderReader.h"
#include "../../XCShape/XCDefaultShape.h"
#include "../../XCShape/XCTextureFucntions.h"
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
	glGenVertexArrays(8, vao);
	glGenBuffers(8,vbo);
	EnemyTexture8x1Init(program,vao,vbo);
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
	AttackInterval = 0.080f;
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
					NowX = coordx_func(NowX, NowY,enemyTimer, velocity, 0);
					NowY = coordy_func(NowX, NowY,enemyTimer, velocity, 0);
					break;
			}
			switch (EnemyNowState) {
			case ENEMY_MOVING:
				glBindVertexArray(*(vao + (size_t)EnemySameStateTime + 4));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo + (size_t)EnemySameStateTime + 4));
				break;
			case ENEMY_STANDBY:
			case ENEMY_ATTACK:
				glBindVertexArray(*(vao + (size_t)EnemySameStateTime));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo + (size_t)EnemySameStateTime));
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