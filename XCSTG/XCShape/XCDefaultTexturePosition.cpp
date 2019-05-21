#include "XCDefaultTexturePosition.h"
#include <GL3/gl3w.h>
void PlayerTexture8x3Init(GLuint program,GLuint * vao, GLuint * vbo, size_t size)
{
	char str[] = "One of the most stupid codes.";
	glUseProgram(program);
	auto display_coord_pos = glGetAttribLocation(program, "display_coord");
	auto in_tex_coord_pos = glGetAttribLocation(program, "input_tex_pos");
	for (int i = 0; i < size;i++) {
		glBindVertexArray(*(vao+i));
		glBindBuffer(GL_ARRAY_BUFFER, *(vbo + i));
		switch (i) {
		case 0:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_0_8x3), player_standby_0_8x3, GL_STATIC_DRAW);
			break;
		case 1:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_1_8x3), player_standby_1_8x3, GL_STATIC_DRAW);
			break;
		case 2:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_2_8x3), player_standby_2_8x3, GL_STATIC_DRAW);
			break;
		case 3:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_3_8x3), player_standby_3_8x3, GL_STATIC_DRAW);
			break;
		case 4:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_4_8x3), player_standby_4_8x3, GL_STATIC_DRAW);
			break;
		case 5:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_5_8x3), player_standby_5_8x3, GL_STATIC_DRAW);
			break;
		case 6:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_6_8x3), player_standby_6_8x3, GL_STATIC_DRAW);
			break;
		case 7:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_standby_7_8x3), player_standby_7_8x3, GL_STATIC_DRAW);
			break;
		case 8:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_0_8x3), player_turnleft_0_8x3, GL_STATIC_DRAW);
			break;
		case 9:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_1_8x3), player_turnleft_1_8x3, GL_STATIC_DRAW);
			break;
		case 10:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_2_8x3), player_turnleft_2_8x3, GL_STATIC_DRAW);
			break;
		case 11:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_3_8x3), player_turnleft_3_8x3, GL_STATIC_DRAW);
			break;
		case 12:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_4_8x3), player_turnleft_4_8x3, GL_STATIC_DRAW);
			break;
		case 13:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_5_8x3), player_turnleft_5_8x3, GL_STATIC_DRAW);
			break;
		case 14:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_6_8x3), player_turnleft_6_8x3, GL_STATIC_DRAW);
			break;
		case 15:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnleft_7_8x3), player_turnleft_7_8x3, GL_STATIC_DRAW);
			break;
		case 16:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_0_8x3), player_turnright_0_8x3, GL_STATIC_DRAW);
			break;
		case 17:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_1_8x3), player_turnright_1_8x3, GL_STATIC_DRAW);
			break;
		case 18:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_2_8x3), player_turnright_2_8x3, GL_STATIC_DRAW);
			break;
		case 19:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_3_8x3), player_turnright_3_8x3, GL_STATIC_DRAW);
			break;
		case 20:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_4_8x3), player_turnright_4_8x3, GL_STATIC_DRAW);
			break;
		case 21:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_5_8x3), player_turnright_5_8x3, GL_STATIC_DRAW);
			break;
		case 22:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_6_8x3), player_turnright_6_8x3, GL_STATIC_DRAW);
			break;
		case 23:
			glBufferData(GL_ARRAY_BUFFER, sizeof(player_turnright_7_8x3), player_turnright_7_8x3, GL_STATIC_DRAW);
			break;
		}
		glVertexAttribPointer(display_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(0));
		glVertexAttribPointer(in_tex_coord_pos, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(display_coord_pos);
		glEnableVertexAttribArray(in_tex_coord_pos);
	}
}
