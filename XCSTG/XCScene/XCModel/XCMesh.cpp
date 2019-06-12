#include "XCMesh.h"
#include "../../util/ImageLoader.h"
#include <GL3/gl3w.h>
#include <iostream>
using namespace xc_ogl;
using namespace std;
void XCMesh::ModelInit()
{
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		sizeof(XCVertex)*vertexGroup.size(),
		&vertexGroup[0],
		GL_STATIC_DRAW
	);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		sizeof(size_t)*indexGroup.size(),
		&indexGroup[0],
		GL_STATIC_DRAW
	);
	auto position_loc = glGetAttribLocation(program, "aPosition");
	glVertexAttribPointer(position_loc, 3, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, Position));
	glEnableVertexAttribArray(position_loc);
	auto texcoord_loc = glGetAttribLocation(program, "aTexCoords");
	glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, TexCoords));
	glEnableVertexAttribArray(texcoord_loc);
	auto normal_loc = glGetAttribLocation(program, "aNormal");
	glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, Normal));
	glEnableVertexAttribArray(normal_loc);
	auto tangent_loc = glGetAttribLocation(program, "aTangent");
	glVertexAttribPointer(tangent_loc, 2, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, Tangent));
	glEnableVertexAttribArray(tangent_loc);
	auto bitangent_loc = glGetAttribLocation(program, "aBitangent");
	glVertexAttribPointer(bitangent_loc, 2, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, Bitangent));
	glEnableVertexAttribArray(bitangent_loc);

	glUniform1i(glGetUniformLocation(program, "textureGroup"), 0);
}

XCMesh::XCMesh(GLuint pHnd, std::vector<XCVertex> vertex, std::vector<size_t> index, std::vector<XCTexture> tex)
{
	program = pHnd;
	vertexGroup = vertex;
	indexGroup = index;
	textureGroup = tex;
	ModelInit();
}

void XCMesh::MeshRender()
{
	size_t diffuseNr = 0, specularNr = 0, normalNr = 0, heightNr = 0;
	bool texEnable[10] = {false};
	int useTexType[10] = { -1 };
	glEnable(GL_TEXTURE_2D_ARRAY);
	//glActiveTexture(GL_TEXTURE0 + textureGroup.size());
	for (unsigned int i = 0; i < textureGroup.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		string name = textureGroup[i].type;
		if (name == "texture_diffuse") {
			texEnable[i] = true;
			diffuseNr++;
			useTexType[i] = 0;
		}
		else if (name == "texture_specular") {
			texEnable[i] = true;
			specularNr++;
			useTexType[i] = 1;
		}
		else if (name == "texture_normal") {
			texEnable[i] = true;
			normalNr++;
			useTexType[i] = 2;
		}
		else if (name == "texture_height") {
			texEnable[i] = true;
			heightNr++;
			useTexType[i] = 3;
		}
		glBindTexture(GL_TEXTURE_2D_ARRAY, textureGroup[i].id);
	}
	glUniform1iv(glGetUniformLocation(program,"materialInfo.isEnable"),10, (GLint*)texEnable);
	glUniform1iv(glGetUniformLocation(program, "materialInfo.useTexType"), 10, useTexType);
	glUniform1i(glGetUniformLocation(program, "materialInfo.texCount"), textureGroup.size());
	// draw mesh
	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexGroup.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}


