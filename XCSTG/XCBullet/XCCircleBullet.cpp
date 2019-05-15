#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include "XCCircleBullet.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint xc_bullet::XCCircleBullet::temp_tbo[5];
GLuint xc_bullet::XCCircleBullet::program_static;
bool xc_bullet::XCCircleBullet::have_resource_init = false;
bool xc_bullet::XCCircleBullet::have_program_init = false;
void xc_bullet::XCCircleBullet::SetRenderTBO(GLuint in_tbo)
{
	tbo = in_tbo;
}

void xc_bullet::XCCircleBullet::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader BulletReader;
		BulletReader.load_from_file("shader/bullet/GeneralBullet.vert", GL_VERTEX_SHADER);
		BulletReader.load_from_file("shader/bullet/GeneralBullet.frag", GL_FRAGMENT_SHADER);
		BulletReader.link_all_shader();
		program_static= BulletReader.get_program();
		have_program_init = true;
	}
	program = program_static;
}

void xc_bullet::XCCircleBullet::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader TexLoader;
		TexLoader.LoadTextureData("image/bullet/normal_circle_bullet_0.png");
		temp_tbo[0] = TexLoader.GetTBO();
		have_resource_init = true;
	}
	SetRenderTBO(temp_tbo[0]);
	glUniform1i(glGetUniformLocation(program,"tex"),0);
}

void xc_bullet::XCCircleBullet::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(covered_plane_vertex), covered_plane_vertex,GL_STATIC_DRAW);
	auto vert_loc = glGetAttribLocation(program,"in_coord");
	glVertexAttribPointer(vert_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
	glEnableVertexAttribArray(vert_loc);
}

void xc_bullet::XCCircleBullet::DataInit()
{
	rotate_angle = 0.0f; 
	deltaTime = 0.0f;
	if (have_start_pos == true && have_velocity == true && have_xyfunc == true) {
		should_render = true;
	}
	else {
		should_render = false;
	}
}

void xc_bullet::XCCircleBullet::BulletRender(float nowFrame)
{
	if (should_render)
	{
		/////////////////OGL TIME!!!//////////////////
		XCBullet::BulletRender(nowFrame);
		glEnable(GL_BLEND);
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tbo);
		/////////////////////////////////////////////
		UpdateAimToPlayerCoord();//if set AimToPlayer
		NowX = coordx_func(NowX, NowY, nowFrame, deltaTime, velocity, 0);
		NowY = coordy_func(NowX, NowY, nowFrame, deltaTime, velocity, 0);

		if (NowX>1.15f||NowX<-1.15f||NowY>1.15f||NowY<-1.15f) 
		{
			should_render = false;
		}
		glm::mat4 transform_mat;
		transform_mat = glm::rotate(transform_mat, glm::radians(rotate_angle*nowFrame), glm::vec3(0,0,1));
		transform_mat = glm::translate(transform_mat, glm::vec3(NowX,NowY,NowZ));
		transform_mat = glm::scale(transform_mat,glm::vec3(0.03f,0.03f,0.03f));
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
		glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));
	}
	else {
		DataReset();
	}
}

void xc_bullet::XCCircleBullet::BulletCollisionWithPlayer(PlayerEntity * player)
{
	if (player == nullptr) return;
	if (should_render)
	{
		auto player_coord = player->GetPlayerCoord();
		float x = **player_coord,y=**(player_coord+1), z = **(player_coord + 2);
		float dist = sqrt(pow(x-NowX,2)+pow(y-NowY,2));
		if (dist< attack_radius) {
			player->SetDead();
			should_render = false;
		}
	}
	xc_bullet::XCBullet::BulletCollisionWithPlayer(player);
}
