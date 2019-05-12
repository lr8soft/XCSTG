#pragma once
#ifndef _GLSL_reader_
#define _GLSL_reader_
#include<GL3/gl3w.h>
#include<iostream>
using std::string;
namespace xc_ogl {
	class ShaderReader {
	private:
		GLuint temp_program=0;
		size_t shader_count=0;
		void show_failed_info(string);
		const GLchar* read_from_file(const char*);
	public:
		ShaderReader();
		ShaderReader(GLuint program);
		GLboolean load_from_file(const char* path,GLenum type);
		GLboolean load_from_info(const char* info, GLenum type);
		GLboolean add_new_shader(GLuint shader, GLenum type);
		GLboolean link_all_shader();
		GLuint get_program();
	};
}
#endif