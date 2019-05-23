#include "XCBoss.h"
#include "../../util/ShaderReader.h"
#include "../../util/ImageLoader.h"
#include "../../XCShape/XCDefaultShape.h"
#include "../../XCShape/XCDefaultTexturePosition.h"
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
		BossShaderLoader.load_from_file("Shader/boss/BossBase.vert", GL_VERTEX_SHADER);
		BossShaderLoader.load_from_file("Shader/boss/BossBase.frag", GL_FRAGMENT_SHADER);
		/*BossShaderLoader.load_from_file("Shader/general/generalTex.vert",GL_VERTEX_SHADER);
		BossShaderLoader.load_from_file("Shader/general/generalTex.frag",GL_FRAGMENT_SHADER);*/
		BossShaderLoader.link_all_shader();
		program_static = BossShaderLoader.get_program();
		have_program_init = true;
	}
	program = program_static;
}

void xc_game::XCBoss::BufferInit()
{
	glUseProgram(program);
	glGenVertexArrays(12, vao_tex);
	glGenBuffers(12, vbo_tex);

	auto vert_pos = glGetAttribLocation(program, "display_coord");
	auto tex_pos = glGetAttribLocation(program, "input_tex_coord");
	for (int i = 0; i < sizeof(vbo_tex) / sizeof(GLuint);i++) {
		glBindVertexArray(vao_tex[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_tex[i]);
		switch (i) {
			case 0:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_standby_0_4x3), boss_standby_0_4x3, GL_STATIC_DRAW);
				break;
			case 1:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_standby_1_4x3), boss_standby_1_4x3, GL_STATIC_DRAW);
				break;
			case 2:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_standby_2_4x3), boss_standby_2_4x3, GL_STATIC_DRAW);
				break;
			case 3:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_standby_3_4x3), boss_standby_3_4x3, GL_STATIC_DRAW);
				break;
			case 4:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_moving_0_4x3), boss_moving_0_4x3, GL_STATIC_DRAW);
				break;
			case 5:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_moving_1_4x3), boss_moving_1_4x3, GL_STATIC_DRAW);
				break;
			case 6:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_moving_2_4x3), boss_moving_2_4x3, GL_STATIC_DRAW);
				break;
			case 7:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_moving_3_4x3), boss_moving_3_4x3, GL_STATIC_DRAW);
				break;
			case 8:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_attack_0_4x3), boss_attack_0_4x3, GL_STATIC_DRAW);
				break;
			case 9:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_attack_1_4x3), boss_attack_1_4x3, GL_STATIC_DRAW);
				break;
			case 10:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_attack_2_4x3), boss_attack_2_4x3, GL_STATIC_DRAW);
				break;
			case 11:
				glBufferData(GL_ARRAY_BUFFER, sizeof(boss_attack_3_4x3), boss_attack_3_4x3, GL_STATIC_DRAW);
				break;
		}
		glVertexAttribPointer(vert_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(tex_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(vert_pos);
		glEnableVertexAttribArray(tex_pos);
	}

	
}
xc_game::XCBoss::XCBoss()
{
	NowLife = 100000, MaxLife = 100000;
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
	if (should_render) {
		OGLSettingRenderStart();
		glUseProgram(program);
		if (BossNowState == BossLastState) {
			if (BossSameStateTime < 3.8) {
				switch (BossNowState) {
				case BOSS_ATTACK:
					BossSameStateTime += 0.070f; break;
				case BOSS_STANDBY:
					BossSameStateTime += 0.040f; break;
				case BOSS_MOVING:
					BossSameStateTime += 0.050f; break;
				}
				
			}else {
				BossSameStateTime = 0;
#define _BOSS_MODE_SHOW_
#ifdef _BOSS_MODE_SHOW_
				switch (BossNowState) {
				case BOSS_MOVING:
				case BOSS_STANDBY:
					++BossNowState;break;
				case BOSS_ATTACK:
					BossNowState = BOSS_STANDBY; break;
				}
#endif
			}
		}
		else {
			BossSameStateTime = 0;
			BossLastState=BossNowState;
		}
		switch (BossNowState) {
			case BOSS_STANDBY:
				glBindVertexArray(*(vao_tex + (size_t)BossSameStateTime));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo_tex + (size_t)BossSameStateTime));
				break;
			case BOSS_MOVING:
				glBindVertexArray(*(vao_tex + (size_t)BossSameStateTime+4));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo_tex + (size_t)BossSameStateTime+4));
				break;
			case BOSS_ATTACK:
				glBindVertexArray(*(vao_tex + (size_t)BossSameStateTime + 8));
				glBindBuffer(GL_ARRAY_BUFFER, *(vbo_tex + (size_t)BossSameStateTime + 8));
				break;
		}
		glBindTexture(GL_TEXTURE_2D, use_tbo);
		glm::mat4 transform_mat;
		transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
		transform_mat = glm::scale(transform_mat, glm::vec3(0.16f,0.20f,0.0f));
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0,sizeof(boss_standby_0_4x3)/4*sizeof(float));
		infoSlot.SpecialEffectRender();
		if (is_dead) {
			if (explode_se.SpecialEffectRender(NowX, NowY, NowZ))//·µ»Øtrue¼´äÖÈ¾Íê³É
				is_dead = false;//should_render = false;
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
