#include "PlayerEntity.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
void PlayerEntity::EveryRenderInit()
{
	MoveTexSet(TboPL[0]);
	RenderDecisionPoint = false;
}
void PlayerEntity::EveryFinishRender()
{
	pEnemyInfo = nullptr;
}
void PlayerEntity::OGLSettingRenderStart()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
}
void PlayerEntity::OGLSettingRenderEnd()
{
	glDisable(GL_BLEND);
}
void PlayerEntity::ShaderLoader()
{
	ShaderReader glpr,gltx;
	gltx.load_from_file("shader/player/vertex_tx.glsl", GL_VERTEX_SHADER);
	gltx.load_from_file("shader/player/fragment_tx.glsl", GL_FRAGMENT_SHADER);
	gltx.link_all_shader();
	program[TX] = gltx.get_program();

	glpr.load_from_file("shader/player/vertex_player.glsl", GL_VERTEX_SHADER);
	glpr.load_from_file("shader/player/fragment_player.glsl", GL_FRAGMENT_SHADER);
	glpr.link_all_shader();
	program[DECISION] = glpr.get_program();

}
void PlayerEntity::TextureLoader()
{
	ImageLoader PRNormal, PRRight, PRLeft,TXLoader;
	PRNormal.LoadTextureData("image/rin/rin_0.png");
	PRRight.LoadTextureData("image/rin/rin_1.png");
	PRLeft.LoadTextureData("image/rin/rin_2.png");
	TXLoader.LoadTextureData("image/se/decision.png");
    TboPL[0] = PRNormal.GetTBO();
	TboPL[1] = PRRight.GetTBO();
	TboPL[2] = PRLeft.GetTBO();
	tboDecision = TXLoader.GetTBO();
	MoveTexSet(TboPL[0]);
	glUniform1i(glGetUniformLocation(program[DECISION],"tex"),0);
	glUniform1i(glGetUniformLocation(program[TX], "tex"), 0);
}
void PlayerEntity::MoveTexSet(GLuint id)
{
	tboPL = id;
}
void PlayerEntity::GroupInit()
{
	ShaderLoader();
	TextureLoader();
	glGenVertexArrays(2, vao);
	glGenBuffers(2, vbo);

	glBindVertexArray(vao[DECISION]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[DECISION]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);
	auto player_loc = glGetAttribLocation(program[DECISION], "player_pos");
	glVertexAttribPointer(player_loc,2,GL_FLOAT,GL_FALSE,0,nullptr);
	glEnableVertexAttribArray(player_loc);
	

	glBindVertexArray(vao[TX]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TX]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex,GL_STATIC_DRAW);
	auto tx_loc = glGetAttribLocation(program[TX], "in_vertex");
	glVertexAttribPointer(tx_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(tx_loc);
	auto tx_tex_loc = glGetUniformLocation(program[TX], "tex");
	glUniform1i(tx_tex_loc, 0);
	auto attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
	auto trace_count = sizeof(trace_attack) / sizeof(xc_game::XCTrackAttack);
	for (int i = 0; i < attack_count; i++) {
		base_attack[i].AttackInit();
	}	
	for (int j = 0; j < trace_count; j++) {
		trace_attack[j].AttackInit();
		trace_attack[j].SetPlayerPosition(&NowX, &NowY, &NowZ);
		trace_attack[j].SetVelocity(0.006f);
		if (j %2==0)
			trace_attack[j].SetOffsizeX((j +1)*(0.035));
		else
			trace_attack[j].SetOffsizeX(-j *(0.035));
	}
	dead_se.SpecialEffectInit(dead_se.RingPlayerDead);
}

void PlayerEntity::GroupRender(float nowFrame)
{
	OGLSettingRenderStart();
/////////////////////////////////////先渲染玩家贴图///////////////////////////////
	glUseProgram(program[TX]);
	glBindVertexArray(vao[TX]);
	glBindBuffer(GL_ARRAY_BUFFER, vbo[TX]);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tboPL);
	glm::mat4 change_matrix, tx_matrix,change_matrix_anti;
	tx_matrix = glm::translate(tx_matrix, glm::vec3(NowX, NowY, NowZ));
	tx_matrix = glm::scale(tx_matrix, glm::vec3(0.08, 0.1, 0.1));//玩家w/h比例是0.8
	auto tx_loc = glGetUniformLocation(program[TX], "transform_mat");
	glUniformMatrix4fv(tx_loc, 1, GL_FALSE, glm::value_ptr(tx_matrix));
	glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
	///////////////////////////////////渲染判定点贴图/////////////////////////////////
	if (RenderDecisionPoint) 
	{
		glUseProgram(program[DECISION]);
		glBindVertexArray(vao[DECISION]);
		glBindBuffer(GL_ARRAY_BUFFER, vbo[DECISION]);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tboDecision);
		change_matrix = glm::translate(change_matrix, glm::vec3(NowX, NowY, NowZ));
		change_matrix = glm::rotate(change_matrix, glm::radians((float)glfwGetTime()*180.0f), glm::vec3(0, 0, 1));
		change_matrix = glm::scale(change_matrix, glm::vec3(0.14, 0.14, 0.14));
		auto rotate_loc = glGetUniformLocation(program[DECISION], "rotate_mat");
		glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, glm::value_ptr(change_matrix));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));

		change_matrix_anti = glm::translate(change_matrix_anti, glm::vec3(NowX, NowY, NowZ));
		change_matrix_anti = glm::rotate(change_matrix_anti, glm::radians(-(float)glfwGetTime()*180.0f+90.0f), glm::vec3(0, 0, 1));
		change_matrix_anti = glm::scale(change_matrix_anti, glm::vec3(0.14, 0.14, 0.14));
		glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, glm::value_ptr(change_matrix_anti));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
		
	}
	OGLSettingRenderEnd();
	OGLSettingRenderStart();
	auto attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
	auto trace_count = sizeof(trace_attack)/sizeof(xc_game::XCTrackAttack);
	for (int i = 0; i < attack_count; i++) {
		base_attack[i].AttackRender(nowFrame);
	}
	for (int j = 0; j < trace_count; j++) {
		trace_attack[j].AttackRender(nowFrame);
	}
	if (dead_time) {
		dead_time=!dead_se.SpecialEffectRender(NowX,NowY,NowZ);
	}
	OGLSettingRenderEnd();
}

void PlayerEntity::PlayerCollisonEvent(xc_game::XCEnemyInfo *enemy_info)
{
	pEnemyInfo = enemy_info;
	auto enemy_render = enemy_info->GetRenderingEnemy();
	int base_attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
	int trace_attack_count = sizeof(trace_attack) / sizeof(xc_game::XCTrackAttack);
	if (enemy_render->empty()) {//当没有敌人的时候
#pragma omp parallel for
		for (int k = 0; k < trace_attack_count; k++) {
			trace_attack[k].SetAttackMode(xc_game::XCTrackAttack::FOLLOW_PLAYER_MODE);
		}
	}
	else {
		for (auto iter = enemy_render->begin(); iter != enemy_render->end(); iter++) {//Get each alive enemy
			auto enemy = *(iter);
#pragma omp parallel for
			for (int k = 0; k < trace_attack_count; k++) {
				trace_attack[k].CheckCollisionWithEnemy(enemy);
			}
		}
		for (auto iter = enemy_render->begin(); iter != enemy_render->end(); iter++) {
			auto enemy = *(iter);
#pragma omp parallel for
			for (int i = 0; i < base_attack_count; i++) {
				if (base_attack[i].IsRunning())
					base_attack[i].CheckCollisionWithEnemy(enemy);
			}
		}
	}

}

void PlayerEntity::GroupKeyCheck(GLFWwindow* screen)
{
	EveryRenderInit();
	float currentFrame = glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	if (glfwGetKey(screen, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
	float moveSpeed = base_speed *deltaTime; // adjust accordingly
	if (glfwGetKey(screen, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.40f;
		RenderDecisionPoint = true;
	}
	if (glfwGetKey(screen, GLFW_KEY_UP) == GLFW_PRESS) {
		if (NowY+moveSpeed<1.0f)//防止越界
			NowY += moveSpeed;
		MoveTexSet(TboPL[0]);
	}

	if (glfwGetKey(screen, GLFW_KEY_DOWN) == GLFW_PRESS) {
		if (NowY - moveSpeed > -1.0f)
			NowY -= moveSpeed;
		MoveTexSet(TboPL[0]);
	}
	if (glfwGetKey(screen, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		if (NowX + moveSpeed <1.0f)
			NowX += moveSpeed;
		MoveTexSet(TboPL[2]);
	}

	if (glfwGetKey(screen, GLFW_KEY_LEFT) == GLFW_PRESS) {
		if (NowX - moveSpeed > -1.0f)
			NowX -= moveSpeed;
		MoveTexSet(TboPL[1]);
	}

	if (glfwGetKey(screen, GLFW_KEY_Z) == GLFW_PRESS) {
		auto attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
		for (int i = 0; i < attack_count; i++) {//deltaX, deltaY + 0.12+0.3*i, deltaZ,12.0f
			base_attack[i].SetPositionAndVelocity(NowX, NowY + 0.3*i, NowZ, player_fire_power);
			base_attack[i].SetAttack();
		}
		auto trace_count = sizeof(trace_attack) / sizeof(xc_game::XCTrackAttack);
		if (pEnemyInfo!=nullptr)
		{
			for (int i = 0; i < trace_count; i++) {
				auto enemy_ptr = pEnemyInfo->GetRenderingEnemy();
				for (auto ptr = enemy_ptr->begin(); ptr != enemy_ptr->end(); ptr++) {
					if (!(*ptr)->IsDead()) {
						float **temp_coord = (*(ptr))->GetNowCoord();
						float *x = *(temp_coord), *y = *(temp_coord + 1), *z = *(temp_coord + 2);
						trace_attack[i].SetTarget(x, y, z);
						trace_attack[i].SetAttackMode(xc_game::XCTrackAttack::MOVEING_MODE);
					}
				}
			}
		}
	}
	EveryFinishRender();
}

void PlayerEntity::SetDead()
{
	std::cout << "AWSL" << std::endl;
	dead_time = true;
}

const float ** PlayerEntity::GetPlayerCoord()
{
	const float *playerCoord[3];
	playerCoord[0] = &NowX;
	playerCoord[1] = &NowY;
	playerCoord[2] = &NowZ;
	return playerCoord;
}
