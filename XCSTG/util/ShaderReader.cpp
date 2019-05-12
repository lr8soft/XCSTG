#include<iostream>
#include "ShaderReader.h"
#include<string>
#include<fstream>
#include<sstream>
using std::stringstream;
using std::ifstream;
void xc_ogl::ShaderReader::show_failed_info(string sre)
{
	GLsizei len;
	glGetProgramiv(temp_program, GL_INFO_LOG_LENGTH, &len);

	char* log = new char[len + 1];
	glGetProgramInfoLog(temp_program, len, &len, log);
	std::cerr <<"[ERROR]" <<sre <<" failed: " << log << std::endl;
	delete[] log;
}
const GLchar * xc_ogl::ShaderReader::read_from_file(const char* path)
{
	GLchar *ret = nullptr;
	ifstream io(path);
	if (!io) {
#ifdef _DEBUG
		std::cerr << "[ERROR]Unable to open file '" << path << "'" << std::endl;
#endif /* DEBUG */
	}
	else {
		string info, temp_info;
		bool is_first =true;
		while (std::getline(io, temp_info)) {
			if (is_first)
				is_first = false;
			else
				info += '\n';
			info += temp_info;
		}
		io.close();
#ifdef _DEBUG
		std::cout <<"[INFO]Load shader from file " <<path<<std::endl;
#endif
		ret =new GLchar[info.length()+1];
		memcpy_s(ret,info.length(),info.c_str(),info.length());
		ret[info.length()] = '\0';
	}
	return const_cast<GLchar*>(ret);
}
xc_ogl::ShaderReader::ShaderReader()
{
	temp_program = glCreateProgram();
}

xc_ogl::ShaderReader::ShaderReader(GLuint program)
{
	temp_program = program;
}

GLboolean xc_ogl::ShaderReader::load_from_file(const char *path, GLenum type)
{
	auto *source_ptr = read_from_file(path);
	GLuint temp_shader = glCreateShader(type);
	glShaderSource(temp_shader,1,&source_ptr,0);
	glCompileShader(temp_shader);

	GLint success;
	glGetShaderiv(temp_shader, GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef _DEBUG
		char error_log[512] = {'\0'};
		sprintf_s(error_log,"Shader \"%s\" compilation", path);
		show_failed_info(error_log);
#endif // DEBUG Mode
	}
	else {
		glAttachShader(temp_program, temp_shader);
		shader_count++;
	}
	delete[]source_ptr;
	return success;
}

GLboolean xc_ogl::ShaderReader::load_from_info(const char *info,GLenum type)
{
	GLuint temp_shader=glCreateShader(type);//Create shader object
	auto source = const_cast<const GLchar*>(info);
	glShaderSource(temp_shader,1, &source,0);
	glCompileShader(temp_shader);

	GLint success;
	glGetShaderiv(temp_shader,GL_COMPILE_STATUS, &success);
	if (!success) {
#ifdef _DEBUG
		show_failed_info("Shader compilation");
#endif // DEBUG Mode
	}
	else {
		glAttachShader(temp_program, temp_shader);
		shader_count++;	
	}
	
	return success;
}

GLboolean xc_ogl::ShaderReader::add_new_shader(GLuint shader, GLenum type)
{
	GLint success=GL_FALSE;
	if (glIsShader(shader)) {
		glCompileShader(shader);

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
#ifdef _DEBUG
			show_failed_info("Shader compilation");
#endif // DEBUG Mode
		}
		else {
			glAttachShader(temp_program, shader);
			shader_count++;
		}
	}
	return success;
}

GLboolean xc_ogl::ShaderReader::link_all_shader()
{
	if (shader_count>0) {
		glLinkProgram(temp_program);
		GLint success;
		glGetProgramiv(temp_program, GL_LINK_STATUS, &success);
		if (!success) {
#ifdef _DEBUG
			show_failed_info("Shader linking");
#endif /* DEBUG */
			return GL_FALSE;
		}
		else {
#ifdef _DEBUG
			std::cout << "[INFO]Link all shader files" << std::endl;
#endif /* DEBUG */
			return GL_TRUE;
		}
	}
	return GL_FALSE;
}

GLuint xc_ogl::ShaderReader::get_program()
{
	return temp_program;
}
