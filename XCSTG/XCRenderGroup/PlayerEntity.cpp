#include "PlayerEntity.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include <GLFW/glfw3.h>
#include "../XCShape/XCTextureFucntions.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <sstream>
#define _USE_TRACE_ATTACK_
using namespace xc_ogl;
void PlayerEntity::EveryRenderInit()
{
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
	program[PLAYERTEX] = gltx.get_program();//player texture

	glpr.load_from_file("shader/player/vertex_player.glsl", GL_VERTEX_SHADER);
	glpr.load_from_file("shader/player/fragment_player.glsl", GL_FRAGMENT_SHADER);
	glpr.link_all_shader();
	program[DECISIONTEX] = glpr.get_program();//decision texture

}
void PlayerEntity::TextureLoader()
{
	ImageLoader TXLoader,PlayerTex;
	TXLoader.LoadTextureData("image/se/decision.png");
	PlayerTex.LoadTextureData("image/rin/rin.png");
	tbo_deci = TXLoader.GetTBO();
	tbo_player = PlayerTex.GetTBO();
	glUniform1i(glGetUniformLocation(program[DECISIONTEX],"tex"),0);
	glUniform1i(glGetUniformLocation(program[PLAYERTEX], "tex"), 0);
}
void PlayerEntity::SetPlayerDirection(int direction)
{
	PlayerNowState = direction;
	if (PlayerNowState==PlayerLastState) {
		if (PlayerSameStateTime < 7.9) {
			PlayerSameStateTime += 0.08;
		}
		else {
			PlayerSameStateTime = 0;
		}
	}
}
void PlayerEntity::GroupInit()
{
	ShaderLoader();
	TextureLoader();
	//////////////////////////判定点初始化///////////////////////////////////////////////////
	glGenVertexArrays(1, &vao_deci);
	glGenBuffers(1, &vbo_deci);
	glBindVertexArray(vao_deci);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_deci);
	glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);
	auto player_loc = glGetAttribLocation(program[DECISIONTEX], "player_pos");
	glVertexAttribPointer(player_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(player_loc);
	//////////////////////////玩家贴图初始化///////////////////////////////////////////////////
	glGenVertexArrays(24, vao_player);
	glGenBuffers(24, vbo_player);
	PlayerTexture8x3Init(program[PLAYERTEX], vao_player, vbo_player);
	//////////////////////////玩家贴图初始化///////////////////////////////////////////////////
		//////////////////////////攻击初始化///////////////////////////////////////////////////
	auto attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
	for (int i = 0; i < attack_count; i++) {
		base_attack[i].AttackInit();
	}
	//////////////////////////攻击初始化///////////////////////////////////////////////////
	dead_se.SpecialEffectInit(dead_se.RingPlayerDead);
	playerParticle.SetGroupRenderType(playerParticle.DISPERSE_COORD);
	playerParticle.GroupInit(playerParticle.CIRCLE_PARTICLE,1,100);
	/////////////////////////读取玩家配置文件/////////////////////////////////////////////////
	playercfg = new xc_std::ConfigManager("xcstg.cfg");
	if (playercfg->IsFirstRun()) {
		std::stringstream tempss;
		tempss << GLFW_KEY_UP;
		playercfg->AddNewInfo("keyup", tempss.str());
		tempss.clear(); tempss.str(""); tempss << GLFW_KEY_DOWN;
		playercfg->AddNewInfo("keydown", tempss.str());
		tempss.clear();  tempss.str(""); tempss << GLFW_KEY_LEFT;
		playercfg->AddNewInfo("keyleft", tempss.str());
		tempss.clear();  tempss.str(""); tempss << GLFW_KEY_RIGHT;
		playercfg->AddNewInfo("keyright", tempss.str());
		tempss.clear();  tempss.str(""); tempss << GLFW_KEY_Z;
		playercfg->AddNewInfo("keyshoot", tempss.str());
		tempss.clear();  tempss.str(""); tempss << GLFW_KEY_LEFT_SHIFT;
		playercfg->AddNewInfo("keyslowdown", tempss.str());
		tempss.clear();  tempss.str(""); tempss << GLFW_KEY_X;
		playercfg->AddNewInfo("keysa", tempss.str());
		tempss.clear();  tempss.str(""); tempss << GLFW_KEY_C;
		playercfg->AddNewInfo("keyitem", tempss.str());
#ifdef _DEBUG
		std::cout << "key evironment setup." << std::endl;
#endif
	}
	else {
		auto upss=playercfg->GetValue("keyup");
		auto downss = playercfg->GetValue("keydown");
		auto leftss = playercfg->GetValue("keyleft");
		auto rightss = playercfg->GetValue("keyright");
		auto shootss = playercfg->GetValue("keyshoot");
		auto slowdss = playercfg->GetValue("keyslowdown");
		auto sass= playercfg->GetValue("keysa");
		auto itemss= playercfg->GetValue("keyitem");
		upss>>keyup;
		downss >> keydown;
		leftss >> keyleft;
		rightss >> keyright;
		shootss >> keyshoot;
		slowdss >> keyslowdown;
		sass >> keyspecialattack;
		itemss >> keyitem;
	}
	/////////////////////////读取玩家配置文件/////////////////////////////////////////////////
}

void PlayerEntity::GroupRender(float nowFrame)
{
	OGLSettingRenderStart();
	glm::mat4 change_matrix, tx_matrix, change_matrix_anti;
	
/////////////////////////////////////先渲染玩家贴图///////////////////////////////
	glUseProgram(program[PLAYERTEX]);
	
	switch (PlayerNowState) {
	case PLAYER_STANDBY:
		glBindVertexArray(*(vao_player + (size_t)PlayerSameStateTime));
		glBindBuffer(GL_ARRAY_BUFFER, *(vbo_player + (size_t)PlayerSameStateTime));
		break;
	case PLAYER_TURNRIGHT:
		glBindVertexArray(*(vao_player + (size_t)PlayerSameStateTime+16));
		glBindBuffer(GL_ARRAY_BUFFER, *(vbo_player + (size_t)PlayerSameStateTime + 16));
		break;
	case PLAYER_TURNLEFT:
		glBindVertexArray(*(vao_player + (size_t)PlayerSameStateTime + 8));
		glBindBuffer(GL_ARRAY_BUFFER, *(vbo_player + (size_t)PlayerSameStateTime + 8));
		break;
	}
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tbo_player);
	tx_matrix = glm::translate(tx_matrix, glm::vec3(NowX, NowY, NowZ));
	tx_matrix = glm::scale(tx_matrix, glm::vec3(0.08, 0.1, 0.1));//玩家w/h比例是0.8
	auto tx_loc = glGetUniformLocation(program[PLAYERTEX], "transform_mat");
	glUniformMatrix4fv(tx_loc, 1, GL_FALSE, glm::value_ptr(tx_matrix));
	glDrawArrays(GL_TRIANGLES, 0, 6);
	OGLSettingRenderEnd();
////////////////////////////////////////渲染判定点贴图/////////////////////////////////
	OGLSettingRenderStart();
	if (RenderDecisionPoint)
	{
		glUseProgram(program[DECISIONTEX]);
		glBindVertexArray(vao_deci);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_deci);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tbo_deci);
		change_matrix = glm::translate(change_matrix, glm::vec3(NowX, NowY, NowZ));
		change_matrix = glm::rotate(change_matrix, glm::radians((float)glfwGetTime()*180.0f), glm::vec3(0, 0, 1));
		change_matrix = glm::scale(change_matrix, glm::vec3(0.14, 0.14, 0.14));
		auto rotate_loc = glGetUniformLocation(program[DECISIONTEX], "rotate_mat");
		glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, glm::value_ptr(change_matrix));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));

		change_matrix_anti = glm::translate(change_matrix_anti, glm::vec3(NowX, NowY, NowZ));
		change_matrix_anti = glm::rotate(change_matrix_anti, glm::radians(-(float)glfwGetTime()*180.0f + 90.0f), glm::vec3(0, 0, 1));
		change_matrix_anti = glm::scale(change_matrix_anti, glm::vec3(0.14, 0.14, 0.14));
		glUniformMatrix4fv(rotate_loc, 1, GL_FALSE, glm::value_ptr(change_matrix_anti));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));

	}


	OGLSettingRenderEnd();
	OGLSettingRenderStart();
	auto attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
	for (int i = 0; i < attack_count; i++) {
		base_attack[i].AttackRender(nowFrame);
	}
	if (dead_time) {
		dead_time=!dead_se.SpecialEffectRender(NowX,NowY,NowZ);
	}
	playerParticle.GroupRender(NowX, NowY, NowZ);
	OGLSettingRenderEnd();
}

void PlayerEntity::PlayerCollisonEvent(xc_game::XCEnemyInfo *enemy_info)
{
	pEnemyInfo = enemy_info;
	auto enemy_render = enemy_info->GetRenderingEnemy();
	int base_attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
	if (enemy_render->empty()) {//当没有敌人的时候
		;
	}else {
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
	playerTimer.Tick();
	bool have_player_change_state = false;
	if (glfwGetKey(screen, GLFW_KEY_ESCAPE)) {
		glfwSetWindowShouldClose(screen, true);
	}
	float moveSpeed = base_speed * playerTimer.getDeltaFrame(); // adjust accordingly
	if (glfwGetKey(screen, keyslowdown) == GLFW_PRESS) {
		moveSpeed = moveSpeed / 1.5f * 0.40f;
		RenderDecisionPoint = true;
	}
	if (glfwGetKey(screen, keyup) == GLFW_PRESS) {
		if (NowY+moveSpeed<1.0f)//防止越界
			NowY += moveSpeed;
		SetPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, keydown) == GLFW_PRESS) {
		if (NowY - moveSpeed > -1.0f)
			NowY -= moveSpeed;
		SetPlayerDirection(PLAYER_STANDBY);
		have_player_change_state = true;
	}
	if (glfwGetKey(screen, keyright) == GLFW_PRESS) {
		if (NowX + moveSpeed <1.0f)
			NowX += moveSpeed;
		SetPlayerDirection(PLAYER_TURNRIGHT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, keyleft) == GLFW_PRESS) {
		if (NowX - moveSpeed > -1.0f)
			NowX -= moveSpeed;
		SetPlayerDirection(PLAYER_TURNLEFT);
		have_player_change_state = true;
	}

	if (glfwGetKey(screen, keyshoot) == GLFW_PRESS) {
		auto attack_count = sizeof(base_attack) / sizeof(xc_game::XCAttack);
		for (int i = 0; i < attack_count; i++) {//deltaX, deltaY + 0.12+0.3*i, deltaZ,12.0f
			base_attack[i].SetPositionAndVelocity(NowX, NowY + (1+i)*0.3, NowZ, player_fire_power);
			base_attack[i].SetAttack();
		}
	}
	if (glfwGetKey(screen, keyitem) == GLFW_PRESS) {
		player_fire_power +=0.1f;
	}
	if (!have_player_change_state) {
		if(PlayerNowState!= PLAYER_TURNRIGHT&& PlayerNowState != PLAYER_TURNLEFT)
			SetPlayerDirection(PlayerNowState);
		else
			SetPlayerDirection(PLAYER_STANDBY);
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
	const static float *playerCoord[3];
	playerCoord[0] = &NowX;
	playerCoord[1] = &NowY;
	playerCoord[2] = &NowZ;
	return playerCoord;
}
