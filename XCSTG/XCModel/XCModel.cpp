#include "XCModel.h"
#include <GL3/gl3w.h>
void XCModel::InitModel()
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(XCVertex), nullptr);//position offset=0
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, Normal));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, TexCoord));
	glEnableVertexAttribArray(2);

}

XCModel::XCModel(std::vector<XCVertex> vertex, std::vector<size_t> index, std::vector<XCTexture> tex)
{
	vertexGroup = vertex; 
	indexGroup = index;
	textureGroup = tex;
	InitModel();
}

void XCModel::RenderModel(GLuint programHandle)
{

}
