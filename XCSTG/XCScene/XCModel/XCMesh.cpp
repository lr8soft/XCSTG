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

	glUniform1i(glGetUniformLocation(program, "texture_diffuse1"), 0);
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
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textureGroup.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0+i);
		string number;
		string name = textureGroup[i].type;
		if (name == "texture_diffuse")
			number = std::to_string(diffuseNr++);
		else if (name == "texture_specular")
			number = std::to_string(specularNr++); // transfer unsigned int to stream
		else if (name == "texture_normal")
			number = std::to_string(normalNr++); // transfer unsigned int to stream
		else if (name == "texture_height")
			number = std::to_string(heightNr++); // transfer unsigned int to stream
		glUniform1i(glGetUniformLocation(program, (name + number).c_str()), i);
		glBindTexture(GL_TEXTURE_2D, textureGroup[i].id);
	}

	// draw mesh
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indexGroup.size(), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}


