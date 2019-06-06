#include "XCNormalAttack.h"
#include "../../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../../util/ImageLoader.h"
#include "../../util/ShaderReader.h"
using namespace xc_ogl;
bool xc_game::XCAttack::have_program_init = false;
bool xc_game::XCAttack::have_resource_init = false;
GLuint xc_game::XCAttack::tbo; 
GLuint xc_game::XCAttack::program_static;
void xc_game::XCAttack::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader SELoader;
		SELoader.loadFromFile("shader/general/generalShader.vert", GL_VERTEX_SHADER);
		SELoader.loadFromFile("shader/general/generalShader.frag", GL_FRAGMENT_SHADER);
		SELoader.linkAllShader();
		program_static = SELoader.getProgramHandle();
		have_program_init = true;
	}
	program = program_static;
}

void xc_game::XCAttack::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader SELoader;
		SELoader.loadTextureFromFile("image/se/attack_se.png");
		tbo = SELoader.getTextureBufferObjectHandle();
		have_resource_init = true;
	}
	glUniform1i(glGetUniformLocation(program,"tex"),0);
}

void xc_game::XCAttack::BufferInit()
{
	glUseProgram(program);
	glGenVertexArrays(4, vao);
	glGenBuffers(4, vbo);
	auto in_coord_loc = glGetAttribLocation(program, "render_pos");
	auto in_tex_coord_loc = glGetAttribLocation(program, "tex_pos");
	for (int i = 0; i < 4;i++) {
		glBindVertexArray(vao[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[i]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*24, GetSpecificTexture(4, 1,i+1,1), GL_STATIC_DRAW);
		glVertexAttribPointer(in_coord_loc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(in_tex_coord_loc, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2*sizeof(float)));
		glEnableVertexAttribArray(in_coord_loc);
		glEnableVertexAttribArray(in_tex_coord_loc);
	}
}

void xc_game::XCAttack::AttackInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
	attackAudioEffect.MusicResourceInit(attackAudioEffect.ATTACK_EFFECT);
}

void xc_game::XCAttack::AttackRender(float nowFrame)
{
	if (should_render) {
		attackTimer.Tick(nowFrame);
		NowY += velocity * attackTimer.getDeltaFrame();//首先他在动（碰撞后仍然在计算）
		if (should_render_attack) {//还没碰撞的
			glUseProgram(program);
			if (attackTimer.getAccumlateTime() < 0.1) {
				glBindVertexArray(vao[1]);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
			}
			else if (attackTimer.getAccumlateTime() < 0.15) {
				glBindVertexArray(vao[2]);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
			}
			else if (attackTimer.getAccumlateTime() < 0.20) {
				glBindVertexArray(vao[3]);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
			}
			else {
				glBindVertexArray(vao[0]);
				glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
			}
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, tbo);
			glm::mat4 transform_mat;
			transform_mat = glm::translate(transform_mat, glm::vec3(NowX, NowY, NowZ));
			transform_mat = glm::scale(transform_mat, glm::vec3(0.05f*right,0.05f*top,0.05f));
			auto transform_mat_loc = glGetUniformLocation(program, "convert_mat");
			auto gradient_number_loc = glGetUniformLocation(program, "gradient_number");
			glUniform1f(gradient_number_loc, 0.0f);
			glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
			glDrawArrays(GL_TRIANGLES, 0, 6);
			attackAudioEffect.MusicPlay();
		}
		if (NowY > destY) {//当Y值超过预定上限时候停止渲染，回到初始状态
			should_render = false;
			attackTimer.Clear();
			attackAudioEffect.MusicStop();
		}
	}

}

void xc_game::XCAttack::SetPositionAndVelocity(float x, float y, float z, float v)
{
	if (!should_render) {
		NowX = x;
		NowY = y;
		NowZ = z;
		velocity = v;
		should_render = true;
		should_render_attack = true;
		destY = finish_dist+y;//超过屏幕一个身位
	}
}

void xc_game::XCAttack::SetBorder(float t, float b, float l, float r)
{
	top = t; bottom = b; left = l; right = r;
}

void xc_game::XCAttack::CheckCollisionWithEnemy(xc_game::XCEnemyBase * enemy)
{
	if (!enemy->IsRenderNow()) return;
	if (!should_render_attack) return;//已经碰撞过了，防止发射加速得继续计算但不能碰撞
	auto *enemy_coord = enemy->GetNowCoord();
	float deltaTime = attackTimer.getDeltaFrame();
	float x = *(enemy_coord), y = *(enemy_coord + 1), z = *(enemy_coord + 2);
	if (x<NowX + attack_width && x>NowX - attack_width) {
		if (y>= NowY - attack_height- velocity * deltaTime && y<= NowY + velocity * deltaTime + attack_height) {
			if (!enemy->IsDead()) {
				enemy->SetDamage(3.0f);
				this->should_render_attack = false;
			}
		}
	}
}

void xc_game::XCAttack::SetAttack()
{
	if (!should_render) {
		should_render = true;
	}

}

void xc_game::XCAttack::Reset()
{
	should_render = true;
	velocity = 0;
	NowX = NowY = NowZ = 0;
}

bool xc_game::XCAttack::IsRunning()
{
	return should_render;
}
