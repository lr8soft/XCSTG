#include "../ImageLoader.h"
#include "../ShaderReader.h"
#include "../XCShape/XCDefaultShape.h"
#include "XCCircleBullet.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace xc_ogl;
GLuint xc_bullet::XCCircleBullet::temp_tbo[5];
bool xc_bullet::XCCircleBullet::have_resource_init = false;
void xc_bullet::XCCircleBullet::SetRenderTBO(GLuint in_tbo)
{
	tbo = in_tbo;
}

void xc_bullet::XCCircleBullet::ShaderInit()
{
	ShaderReader BulletReader;
	BulletReader.load_from_file("shader/bullet/GeneralBullet.vert",GL_VERTEX_SHADER);
	BulletReader.load_from_file("shader/bullet/GeneralBullet.frag", GL_FRAGMENT_SHADER);
	BulletReader.link_all_shader();
	program = BulletReader.get_program();
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

}

void xc_bullet::XCCircleBullet::BulletRender(float nowFrame)
{
	glEnable(GL_BLEND);
	glUseProgram(program);
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D,tbo);
	glm::mat4 transform_mat;
	auto transform_mat_loc = glGetUniformLocation(program, "transform_mat");
	glUniformMatrix4fv(transform_mat_loc, 1, GL_FALSE, glm::value_ptr(transform_mat));
	glDrawArrays(GL_TRIANGLES, 0, sizeof(covered_plane_vertex) / sizeof(float));

}

void xc_bullet::XCCircleBullet::BulletCollisionWithPlayer(PlayerRenderGroup * player)
{
}
