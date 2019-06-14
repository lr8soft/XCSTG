#include "XCMountainScene.h"
#include <GL3/gl3w.h>
XCMountainScene::XCMountainScene()
{
	SceneInit();
}
void XCMountainScene::SceneInit()
{
	pCamera = new XCCamera;
	pCamera->Position = glm::vec3(0.0f, 80.0f, 10.0f);
	sceneModel = new XCModel("Model/Mountains/Mountains2.obj");
	sceneTimer.Clear();
}

void XCMountainScene::SceneRender(float nowFrame)
{
	sceneTimer.Tick(nowFrame);
	auto backgroundHandle = sceneModel->getProgramHandle();
	/////////////////////Model pre-render init////////////////////
	glUseProgram(backgroundHandle);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	auto convert_mat_loc = glGetUniformLocation(backgroundHandle, "mvp_mat");
	glm::mat4 model_mat, project_mat, view_mat;
	project_mat = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
	view_mat = pCamera->GetViewMatrix();
	/*
	view_mat = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);*/
	model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.0f, 0.0f));
	model_mat = glm::rotate(model_mat, glm::radians((float)sceneTimer.getAccumlateTime()*15.0f), glm::vec3(0, 1, 0));
	//model_mat = glm::scale(model_mat, glm::vec3(0.03f));
	glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(project_mat*view_mat*model_mat));
	/////////////////////////////////////////////////////////////
	sceneModel->Draw();
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glUseProgram(0);
}

void XCMountainScene::SceneRelease()
{
	delete pCamera, sceneModel;
}
