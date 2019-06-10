#pragma once
#ifndef _XCMESH_H_
#define _XCMESH_H_
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <GL/glcorearb.h>
#include <string>
#include <vector>
struct XCVertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};
struct XCTexture {
	size_t id;
	std::string type;
	aiString path;
};
class XCMesh {
protected:
	GLuint vao, vbo, ebo, program;
	void ModelInit();
public:
	std::vector<XCVertex> vertexGroup;
	std::vector<size_t> indexGroup;
	std::vector<XCTexture> textureGroup;
	XCMesh(GLuint pHnd, std::vector<XCVertex> vertex, std::vector<size_t> index, std::vector<XCTexture> tex);
	void MeshRender();
};
#endif