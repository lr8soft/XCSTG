#pragma once
#ifndef _XCDEFAULT_TEXTURE_POSITION_H_
#define _XCDEFAULT_TEXTURE_POSITION_H_
#include <GL/glcorearb.h>
void PlayerTexture8x3Init(GLuint program,GLuint *vao, GLuint *vbo);
void BossTexture4x3Init(GLuint program, GLuint *vao, GLuint *vbo);
void EnemyTexture8x1Init(GLuint program, GLuint *vao, GLuint *vbo);
#endif