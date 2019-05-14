#include "XCTraceAttack.h"
#include "../XCShape/XCDefaultShape.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
using namespace xc_ogl;
bool xc_game::XCTrackAttack::have_resource_init = false;
bool xc_game::XCTrackAttack::have_program_init = false;
GLuint xc_game::XCTrackAttack::tbo;
GLuint xc_game::XCTrackAttack::program_static;
void xc_game::XCTrackAttack::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader SELoader;
		SELoader.load_from_file("shader/se/GeneralSE.vert", GL_VERTEX_SHADER);
		SELoader.load_from_file("shader/se/GeneralSE.frag", GL_FRAGMENT_SHADER);
		SELoader.link_all_shader();
		program_static = SELoader.get_program();
		have_program_init = true;
	}
	program = program_static;
}

void xc_game::XCTrackAttack::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader TXLoader;
		TXLoader.LoadTextureData("image/se/attack_ball.png");
		tbo = TXLoader.GetTBO();
		have_resource_init = true;
	}
	glUniform1i(glGetUniformLocation(program, "tex"), 0);
}

void xc_game::XCTrackAttack::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);
	glVertexAttribPointer(glGetAttribLocation(program, "in_coord"), 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(glGetAttribLocation(program, "in_coord"));

}
void xc_game::XCTrackAttack::ReCalcParameter()
{
	if (have_enemy_lock) {
		if (*destX != NowX) {
			temp_k = (*destY - NowY) / (*destX - NowX);
			temp_b = NowY - (temp_k*NowX);
			temp_theta = acosf(abs(*destX-NowX)/sqrtf(pow(*destX-NowX,2)+ pow(*destY - NowY, 2)));
		}
		else {
			temp_k = 0;
			temp_b = NowY;
			temp_theta = 3.1415926f/2.0f;
		}
	}
}
void xc_game::XCTrackAttack::UpdateCoordY()
{
	NowY=temp_k * NowX + temp_b;
}

void xc_game::XCTrackAttack::AttackInit()
{
	ShaderInit();
	TextureInit();
	BufferInit();
}

void xc_game::XCTrackAttack::AttackRender(float nowFrame)
{
	float currentFrame = nowFrame;
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	glUseProgram(program);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glm::mat4 transform_mat;
	switch (runtime_mode) {
		case FORCE_RETURN: 
		{
			SetAttackMode_Inside(FOLLOW_PLAYER_MODE);
			break;
		}
		case FOLLOW_PLAYER_MODE:
		{
			NowX = *playerX; NowY = *playerY; NowZ = *playerZ;
			transform_mat = glm::translate(transform_mat, glm::vec3(NowX + offset_posX , NowY + 0.15f, NowZ));

			break;
		}
		case FOLLOW_ENEMY_MODE: {
			if (have_enemy_lock) {
				NowX = *destX; NowY = *destY; NowZ = *destZ;
				transform_mat = glm::translate(transform_mat, glm::vec3(NowX + offset_posX, NowY, NowZ));
				if (require_mode== FOLLOW_PLAYER_MODE) {//异常：本应跟随敌人，却收到了跟随玩家的请求
					SetAttackMode_Inside(FOLLOW_PLAYER_MODE);
				}
			}
			else {//destXYZ还是空值
				SetAttackMode_Inside(FOLLOW_PLAYER_MODE);
			}
			break;
		}
		case MOVEING_MODE:
		{
			if (have_enemy_lock) {
				ReCalcParameter();

				if (should_positive) {//NowX初始值比destX小，每次递增NowX逼近destX
					NowX += (velocity *cosf(temp_theta))*pow(deltaTime, 0.15f);///deltaTime;//(velocity *cosf(temp_theta))*pow(deltaTime,0.15f);
					if(NowX>=*destX)//超过了destX，越界即碰撞了
						SetAttackMode_Inside(FOLLOW_ENEMY_MODE);
				}
				else {//NowX初始值比destX大，每次递减NowX逼近destX
					NowX -= (velocity *cosf(temp_theta) )*pow(deltaTime, 0.15f);
					if (NowX <= *destX)//比destX还小，越界即碰撞了
						SetAttackMode_Inside(FOLLOW_ENEMY_MODE);
				}
				UpdateCoordY();
				if(NowX>1.1||NowX<-1.1||NowY>1.1||NowX<-1.1)//越界了
					SetAttackMode_Inside(FOLLOW_PLAYER_MODE);
					
				transform_mat = glm::translate(transform_mat, glm::vec3(NowX + offset_posX, NowY, NowZ));
			}
			else {//destXYZ还是空值
				SetAttackMode_Inside(FOLLOW_PLAYER_MODE);
			}
			break;
		}
	}
	
	transform_mat = glm::rotate(transform_mat, glm::radians(nowFrame*180.0f), glm::vec3(0, 0, 1));
	transform_mat = glm::scale(transform_mat, glm::vec3(0.03f, 0.03f, 0.03f));
	auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
	glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tbo);
	glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));	

}

void xc_game::XCTrackAttack::SetPlayerPosition(float *x, float *y, float *z)
{
	playerX = x; playerY = y; playerZ = z;
}

void xc_game::XCTrackAttack::SetVelocity(float v)
{
	velocity = v;
}

void xc_game::XCTrackAttack::SetOffsizeX(float offsize_x)
{
	offset_posX = offsize_x;
}
/*!!!在默认追踪玩家模式下才能设置目标*/
/*!!阴阳玉正在攻击/追踪敌人，设置目标无效*/
void xc_game::XCTrackAttack::SetTarget(float *X, float *Y, float *Z)
{
	if (runtime_mode== FOLLOW_PLAYER_MODE) {
		destX = X; destY = Y; destZ = Z;
		have_enemy_lock = true;
		if (NowX < *destX) {
			should_positive = true;
		}
		else {
			should_positive = false;
		}
	}
	
}

void xc_game::XCTrackAttack::CheckCollisionWithEnemy(XCEnemy * enemy)
{
	float **enemy_coord = enemy->GetNowCoord();
	float *tx = *(enemy_coord), *ty = *(enemy_coord + 1), *tz = *(enemy_coord + 2);
	float x = *(tx), y = *(ty), z = *(tz);
	float distance = sqrtf(pow(x-NowX,2)+ pow(y - NowY, 2));
	if (runtime_mode!= FOLLOW_PLAYER_MODE) {//跟随模式没有攻击性
		if (distance <= attack_radius) {
			enemy->SetDamage(attack_damage);
			switch (runtime_mode) {
			case FOLLOW_ENEMY_MODE:
				if (enemy->IsDead()) {
					SetAttackMode_Inside(FORCE_RETURN);
					have_enemy_lock = false;
				}
				break;
			case MOVEING_MODE://路上碰到新的，追他
				SetAttackMode_Inside(FOLLOW_ENEMY_MODE);
				SetTarget(tx, ty, tz);
				break;

			}
		}
		else {
			switch (runtime_mode) {
			case FOLLOW_ENEMY_MODE:
				SetAttackMode_Inside(FOLLOW_PLAYER_MODE);
				have_enemy_lock = false;
				break;
			case MOVEING_MODE:
				break;

			}
		}
	}
}
bool xc_game::XCTrackAttack::IsWorking()
{
	if (runtime_mode != FOLLOW_PLAYER_MODE)
		return true;
	else
		return false;
}
/*!强制设定模式，忽略当前所有模式*/
void xc_game::XCTrackAttack::SetAttackMode_Inside(size_t mode)
{
	runtime_mode = mode;
	switch (runtime_mode) {
	case FORCE_RETURN:
		have_enemy_lock = false;
		destX = destY = destZ = nullptr;
		break;
	}
}
/*!只有阴阳玉处于跟随玩家模式才能被设置*/
/*!FORCE_RETURN模式强制回归*/
void xc_game::XCTrackAttack::SetAttackMode(size_t mode)
{
	require_mode = mode;
	if (mode==FORCE_RETURN) {
		SetAttackMode_Inside(FORCE_RETURN);
	}
	if (runtime_mode == FOLLOW_PLAYER_MODE) {
		SetAttackMode_Inside(mode);
	}
}


