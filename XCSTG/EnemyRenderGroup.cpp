#include "EnemyRenderGroup.h"

void EnemyRenderGroup::GroupInit()
{
	for (int i = 0; i < 25;i++) {
		test_enemy[i].EnemyInit();
		if(i%2==0)
			test_enemy[i].SetGenerateAndVelocity(rand()/double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		else if(i%3==0)
			test_enemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		else if(i%5==0)
			test_enemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		else
			test_enemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
		AllEnemyInfo.AddEnemyToVector(&test_enemy[i]);
	}
}

void EnemyRenderGroup::GroupRender(float nowFrame)
{
	for (int i = 0; i < 256; i++) 
		test_enemy[i].EnemyRender(nowFrame);
}

void EnemyRenderGroup::GroupKeyCheck(GLFWwindow * screen)
{
	if (glfwGetKey(screen, GLFW_KEY_G) == GLFW_PRESS) {
		for (int i = 0; i < 16;i++) {
			test_enemy[i].EnemyInit();
			if (i % 2 == 0)
				test_enemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			else if (i % 3 == 0)
				test_enemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			else if (i % 5 == 0)
				test_enemy[i].SetGenerateAndVelocity(rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			else
				test_enemy[i].SetGenerateAndVelocity(-rand() / double(RAND_MAX), -rand() / double(RAND_MAX), 0.0f, 0.8f, 0.8f, 0.0f, 0.015f);
			AllEnemyInfo.AddEnemyToVector(&test_enemy[i]);
		}
	}
}

xc_game::XCEnemyInfo * EnemyRenderGroup::GetEnemyInfoGroup()
{
	return &AllEnemyInfo;
}
