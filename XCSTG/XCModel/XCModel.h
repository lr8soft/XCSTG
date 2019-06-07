#pragma once
#ifndef _XCMODEL_H_
#define _XCMODEL_H_
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glcorearb.h>
#include <string>
#include <vector>
struct XCVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoord;
};
struct XCTexture {
	size_t id;
	std::string type;
};
class XCModel {
protected:
	GLuint vao, vbo, ebo;
	void InitModel();
public:
	std::vector<XCVertex> vertexGroup;
	std::vector<size_t> indexGroup;
	std::vector<XCTexture> textureGroup;
	XCModel(std::vector<XCVertex> vertex, std::vector<size_t> index, std::vector<XCTexture> tex);
	void RenderModel(GLuint programHandle);

};
#endif