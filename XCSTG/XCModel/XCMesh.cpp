#include "XCMesh.h"
#include "../util/ImageLoader.h"
#include "../util/ShaderReader.h"
#include <GL3/gl3w.h>
bool XCMesh::have_program_init = false;
GLuint XCMesh::program = 0;
using namespace xc_ogl;
void XCMesh::ModelInit()
{
	if (!have_program_init)
	{
		ShaderReader shaderLoader;
		shaderLoader.loadFromFile("Shader/model/generalModel.vert", GL_VERTEX_SHADER);
		shaderLoader.loadFromFile("Shader/model/generalModel.frag", GL_FRAGMENT_SHADER);
		shaderLoader.linkAllShader();
		program = shaderLoader.getProgramHandle();
		have_program_init = true;
	}
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
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(XCVertex), (void*)offsetof(XCVertex, TexCoords));
	glEnableVertexAttribArray(2);

}

XCMesh::XCMesh(std::vector<XCVertex> vertex, std::vector<size_t> index, std::vector<XCTexture> tex)
{
	vertexGroup = vertex;
	indexGroup = index;
	textureGroup = tex;
	ModelInit();
}

void XCMesh::MeshRender()
{
	glUseProgram(program);
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;
	unsigned int normalNr = 1;
	unsigned int heightNr = 1;
	for (unsigned int i = 0; i < textureGroup.size(); i++)
	{
		glActiveTexture(GL_TEXTURE0); // + iZ active proper texture unit before binding
		// retrieve texture number (the N in diffuse_textureN)
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

												 // now set the sampler to the correct texture unit
		glUniform1i(glGetUniformLocation(program, "tex"), 0);
		//glUniform1i(glGetUniformLocation(program, (name + number).c_str()), i);
		// and finally bind the texture
		glBindTexture(GL_TEXTURE_2D, textureGroup[i].id);
	}

	// draw mesh
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glDrawElements(GL_TRIANGLES, indexGroup.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// always good practice to set everything back to defaults once configured.
	glActiveTexture(GL_TEXTURE0);
}

