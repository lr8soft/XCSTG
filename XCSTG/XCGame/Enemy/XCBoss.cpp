#include "XCBoss.h"
#include "../../util/ShaderReader.h"
#include "../../util/ImageLoader.h"
#include "../../XCShape/XCDefaultShape.h"
#include "../../XCShape/XCTextureFucntions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint xc_game::XCBoss::tbo_static;
bool xc_game::XCBoss::have_program_init = false;
bool xc_game::XCBoss::have_resource_init = false;
void xc_game::XCBoss::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader BossShaderLoader;
		BossShaderLoader.loadFromFile("Shader/boss/BossBase.vert", GL_VERTEX_SHADER);
		BossShaderLoader.loadFromFile("Shader/boss/BossBase.frag", GL_FRAGMENT_SHADER);
		BossShaderLoader.linkAllShader();
		program_static = BossShaderLoader.getProgramHandle();
		have_program_init = true;
	}
	program = program_static;
}

void xc_game::XCBoss::BufferInit()
{
	glUseProgram(program);
	glGenVertexArrays(12, vao_tex);
	glGenBuffers(12, vbo_tex);
	BossTexture4x3Init(program,vao_tex,vbo_tex);	
}
xc_game::XCBoss::XCBoss()
{
	NowLife = 100000, MaxLife = 100000;
	EachStateInterval = 3.8;/*Texture data init*/
	AttackInterval = 0.070f;
	StandByInterval = 0.040f;
	MovingInterval = 0.050f;
}
void xc_game::XCBoss::EnemyInit(size_t type)
{
	XCEnemyBase::EnemyInit(type);
	enemy_type=BOSS_ENEMY;
	infoSlot.SpecialEffectInit();
	infoSlot.SetInfo(&NowLife, &MaxLife, 0, 0);
	explode_se.SpecialEffectInit(explode_se.RingBossDead);
}

void xc_game::XCBoss::EnemyRender(float nowFrame)
{
	XCEnemyBase::EnemyRender(nowFrame);
	if (should_render) {
		OGLSettingRenderStart();
		glUseProgram(program);
		switch (EnemyNowState) {
			case ENEMY_STANDBY:
				glBindVertexArray(*(vao_tex + (size_t)EnemySameStateTime));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo_tex + (size_t)EnemySameStateTime));
				break;
			case ENEMY_MOVING:
				glBindVertexArray(*(vao_tex + (size_t)EnemySameStateTime +4));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo_tex + (size_t)EnemySameStateTime +4));
				break;
			case ENEMY_ATTACK:
				glBindVertexArray(*(vao_tex + (size_t)EnemySameStateTime + 8));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo_tex + (size_t)EnemySameStateTime + 8));
				break;
		}
		glBindTexture(GL_TEXTURE_2D, use_tbo);
		glm::mat4 transform_mat;
		transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
		transform_mat = glm::scale(transform_mat, glm::vec3(0.16f,0.20f,0.0f));
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0, 6);
		infoSlot.BossHPRender();
		infoSlot.SpellCardInfoRender(infoSlot.GET_SPELL_CARD);
		if (is_dead) {
			if (explode_se.SpecialEffectRender(NowX, NowY, NowZ))//返回true即渲染完成
				is_dead = false;//should_render = false;boss不会主动停止渲染
		}
		OGLSettingRenderEnd();
	}
}

void xc_game::XCBoss::ReleaseResource()
{
	glDeleteVertexArrays(12, vao_tex);
	glDeleteBuffers(12, vbo_tex);
}


void xc_game::XCBoss::SetInfo(float health, float maxhealth)
{
	NowLife = health;
	MaxLife = maxhealth;
	is_dead = false;
}
