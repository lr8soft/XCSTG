#include "XCTextureFucntions.h"
#include "XCDefaultShape.h"
#include <GL3/gl3w.h>
void PlayerTexture8x3Init(GLuint program,GLuint * vao, GLuint * vbo)
{
	glUseProgram(program);
	auto display_coord_pos = glGetAttribLocation(program, "display_coord");
	auto in_tex_coord_pos = glGetAttribLocation(program, "input_tex_pos");
	for (int i = 0; i < 24;i++) {
		glBindVertexArray(*(vao+i));
		glBindBuffer(GL_ARRAY_BUFFER, *(vbo + i));
		if (i >= 0 && i < 8) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(8, 3, i + 1 , 3),GL_STATIC_DRAW);
		}
		else  if(i>=8&&i<16){
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(8, 3, i - 7 , 2), GL_STATIC_DRAW);
		}
		else {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(8, 3, i - 15, 1), GL_STATIC_DRAW);
		}
		glVertexAttribPointer(display_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(in_tex_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(display_coord_pos);
		glEnableVertexAttribArray(in_tex_coord_pos);
	}
}

void BossTexture4x3Init(GLuint program, GLuint * vao, GLuint * vbo)
{
	glUseProgram(program);
	auto vert_pos = glGetAttribLocation(program, "display_coord");
	auto tex_pos = glGetAttribLocation(program, "input_tex_coord");
	for (int i = 0; i < 12;i++) {
		glBindVertexArray(*(vao + i));
		glBindBuffer(GL_ARRAY_BUFFER,*(vbo+i));
		if (i>=0&&i<4) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(4, 3, i + 1, 3), GL_STATIC_DRAW);
		}
		else if (i>=4&&i<8) {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(4, 3, i - 3, 2), GL_STATIC_DRAW);
		}
		else {
			glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(4, 3, i - 7, 1), GL_STATIC_DRAW);
		}
		glVertexAttribPointer(vert_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(tex_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(vert_pos);
		glEnableVertexAttribArray(tex_pos);
	}
}

void EnemyTexture8x1Init(GLuint program, GLuint * vao, GLuint * vbo)
{
	glUseProgram(program);
	auto display_coord_pos = glGetAttribLocation(program, "display_coord");
	auto in_tex_coord_pos = glGetAttribLocation(program, "input_tex_pos");
	for (int i = 0; i < 8;i++) {
		glBindVertexArray(*(vao + i));
		glBindBuffer(GL_ARRAY_BUFFER, *(vbo + i));
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 24, GetSpecificTexture(8, 1, i + 1, 1), GL_STATIC_DRAW);
		glVertexAttribPointer(display_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(in_tex_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(display_coord_pos);
		glEnableVertexAttribArray(in_tex_coord_pos);
	}
}
