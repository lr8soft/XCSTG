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
bool xc_bullet::XCCircleBullet::use_point_sprite = true;
//#define _NO_POINT_SPRITE_
void xc_bullet::XCCircleBullet::SetRenderTBO(GLuint in_tbo)
{
	tbo = in_tbo;
}

void xc_bullet::XCCircleBullet::ShaderInit()
{
	if (!have_program_init) {
		ShaderReader BulletReader;
		if (use_point_sprite) {
			BulletReader.load_from_file("shader/bullet/GeneralBullet.ps.vert", GL_VERTEX_SHADER);
			BulletReader.load_from_file("shader/bullet/GeneralBullet.ps.frag", GL_FRAGMENT_SHADER);
		}
		else {
			BulletReader.load_from_file("shader/bullet/GeneralBullet.vert", GL_VERTEX_SHADER);
			BulletReader.load_from_file("shader/bullet/GeneralBullet.frag", GL_FRAGMENT_SHADER);
		}
		BulletReader.link_all_shader();
		program_static= BulletReader.get_program();
		have_program_init = true;
	}
	program = program_static;
}

void xc_bullet::XCCircleBullet::TextureInit()
{
	if (!have_resource_init) {
		ImageLoader TexLoader0,TexLoader1,TexLoader2,TexLoader3;
		TexLoader0.LoadTextureData("image/bullet/normal_circle_bullet_0.png");
		TexLoader1.LoadTextureData("image/bullet/largeish_circle_bullet_0.png");
		TexLoader2.LoadTextureData("image/bullet/huge_circle_bullet_0.png");
		TexLoader3.LoadTextureData("image/bullet/tiny_circle_bullet_0.png");
		temp_tbo[NORMAL] = TexLoader0.GetTBO();
		temp_tbo[LARGEISH] = TexLoader1.GetTBO();
		temp_tbo[HUGE]= TexLoader2.GetTBO();
		temp_tbo[TINY] = TexLoader3.GetTBO();
		have_resource_init = true;
	}

	glUniform1i(glGetUniformLocation(program,"tex"),0);
}

void xc_bullet::XCCircleBullet::BufferInit()
{
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	if (use_point_sprite) {
		glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), GetPointSpriteVertex(5.0f), GL_STATIC_DRAW);
		auto vert_loc = glGetAttribLocation(program, "in_coord");
		glVertexAttribPointer(vert_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(vert_loc);
	}
	else {
		glBufferData(GL_ARRAY_BUFFER, sizeof(covered_plane_vertex), covered_plane_vertex, GL_STATIC_DRAW);
		auto vert_loc = glGetAttribLocation(program, "in_coord");
		glVertexAttribPointer(vert_loc, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(vert_loc);
	}
}

void xc_bullet::XCCircleBullet::DataInit()
{
	if (have_start_pos == true && have_velocity == true && have_xyfunc == true) {
		should_render = true;
	}
	else {
		should_render = false;
	}
}

void xc_bullet::XCCircleBullet::SetUsePointSprite(bool use)
{
	if(!have_resource_init&&!have_program_init)
		use_point_sprite = use;
}

void xc_bullet::XCCircleBullet::SetBulletType(size_t type)
{
	SetRenderTBO(temp_tbo[type]);
	bulletType = type;
	attack_radius = attack_radius_group[type];
}

void xc_bullet::XCCircleBullet::BulletRender(float nowFrame)
{
	if (should_render)
	{
		BulletTimer.Tick(nowFrame);
		SetBulletType(bulletType);
		/////////////////OGL TIME!!!//////////////////
		glEnable(GL_BLEND);
		if (use_point_sprite) 
		{
			glEnable(GL_PROGRAM_POINT_SIZE);
		}
		glUseProgram(program);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tbo);
		/////////////////////////////////////////////
		UpdateAimToPlayerCoord();//if set AimToPlayer
		NowX = coordx_func(NowX, NowY, BulletTimer, velocity, 0);
		NowY = coordy_func(NowX, NowY, BulletTimer, velocity, 0);

		if (NowX>right||NowX<left||NowY>top||NowY<bottom) 
		{
			should_render = false;
		}
		glm::mat4 transform_mat;
		auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
		transform_mat = glm::translate(transform_mat, glm::vec3(NowX,NowY,NowZ));
		transform_mat = glm::rotate(transform_mat, glm::radians(rotate_angle), glm::vec3(0, 0, 1));
		if (use_point_sprite) {
			auto bullet_size_loc = glGetUniformLocation(program, "point_size");
			glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
			glUniform1f(bullet_size_loc, tex_point_size[bulletType] * 7);
			glDrawArrays(GL_POINTS, 0, 1);
			glDisable(GL_PROGRAM_POINT_SIZE);
		}
		else {
			transform_mat = glm::scale(transform_mat, glm::vec3(tex_scale_rate[bulletType]));
			glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
			glDrawArrays(GL_TRIANGLES, 0, 6);
		}
	}
	else {
		DataReset();
	}
}

void xc_bullet::XCCircleBullet::BulletRelease()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
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
