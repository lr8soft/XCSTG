#include "XCModel.h"
#include "../../util/ImageArrayLoader.h"
#include "../../util/ShaderReader.h"
#include <GL3/gl3w.h>
#include <glfw/glfw3.h>
using namespace xc_ogl;
GLuint XCModel::programHnd = 0;
bool XCModel::have_program_init = false;
void XCModel::Draw()
{
	glUseProgram(programHnd);
	auto convert_mat_loc = glGetUniformLocation(programHnd, "mvp_mat");
	glm::mat4 model_mat, project_mat, view_mat;
	project_mat = glm::perspective(glm::radians(45.0f), 1280.0f / 720.0f, 0.1f, 1000.0f);
	/*view_mat = glm::lookAt(
		glm::vec3(0.0f, 80.0f, 10.0f),
		glm::vec3(0.0f, 78.5f, 5.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);*/
	view_mat = glm::lookAt(
		glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 5.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	);
	model_mat = glm::translate(model_mat, glm::vec3(0.0f, 0.0f,0.0f));
	model_mat = glm::rotate(model_mat, glm::radians((float)glfwGetTime()*15.0f), glm::vec3(0, 1, 0));
	model_mat = glm::scale(model_mat, glm::vec3(0.02f));
	glUniformMatrix4fv(convert_mat_loc, 1, GL_FALSE, glm::value_ptr(project_mat*view_mat*model_mat));
	for (unsigned int i = 0; i < meshes.size(); i++)
	{ 
		meshes[i].MeshRender();
	}
	glUseProgram(0);
}
void XCModel::loadModel(std::string const & path)
{
	if (!have_program_init)
	{
		ShaderReader shaderLoader;
		shaderLoader.loadFromFile("Shader/model/generalModel.vert", GL_VERTEX_SHADER);
		shaderLoader.loadFromFile("Shader/model/generalModel.frag", GL_FRAGMENT_SHADER);
		shaderLoader.linkAllShader();
		programHnd = shaderLoader.getProgramHandle();
		have_program_init = true;
	}
	// read file via ASSIMP
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
	// check for errors
	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) // if is Not Zero
	{
		MessageBox(0, importer.GetErrorString(), "ASSIMP ERROR", MB_ICONERROR);
		return;
	}
	// retrieve the directory path of the filepath
	directory = path.substr(0, path.find_last_of('/'));

	// process ASSIMP's root node recursively
	processNode(scene->mRootNode, scene);
}

void XCModel::processNode(aiNode * node, const aiScene * scene)
{
	// process each mesh located at the current node
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		// the node object only contains indices to index the actual objects in the scene. 
		// the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		meshes.push_back(processMesh(mesh, scene));
	}
	// after we've processed all of the meshes (if any) we then recursively process each of the children nodes
	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}

}

XCMesh XCModel::processMesh(aiMesh * mesh, const aiScene * scene)
{
	// data to fill
	std::vector<XCVertex> vertices;
	std::vector<size_t> indices;
	std::vector<XCTexture> textures;

	// Walk through each of the mesh's vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		XCVertex retvertex;
		glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
		// positions
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		retvertex.Position = vector;
		// normals
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		retvertex.Normal = vector;
		// texture coordinates
		if (mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
		{
			glm::vec2 vec;
			// a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
			// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			retvertex.TexCoords = vec;
		}
		else {
			retvertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		// tangent
		vector.x = mesh->mTangents[i].x;
		vector.y = mesh->mTangents[i].y;
		vector.z = mesh->mTangents[i].z;
		retvertex.Tangent = vector;
		// bitangent
		vector.x = mesh->mBitangents[i].x;
		vector.y = mesh->mBitangents[i].y;
		vector.z = mesh->mBitangents[i].z;
		retvertex.Bitangent = vector;

		vertices.push_back(retvertex);
	}
	// now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		// retrieve all indices of the face and store them in the indices vector
		for (unsigned int j = 0; j < face.mNumIndices; j++)
			indices.push_back(face.mIndices[j]);
	}
	// process texture material
	aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

	// 1. diffuse maps
	std::vector<XCTexture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
	textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
	// 2. specular maps
	std::vector<XCTexture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
	textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	// 3. normal maps
	std::vector<XCTexture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
	textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
	// 4. height maps
	std::vector<XCTexture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
	textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());

	// return a mesh object created from the extracted mesh data
	return XCMesh(programHnd, vertices, indices, textures);
}
unsigned int TextureFromFile(const char *path, const std::string &directory, int count, ImageArrayLoader &loader)
{
	std::string filename = std::string(path);
	filename = directory + '/' + filename;
	loader.loadTextureFromFile(count, filename.c_str());

	return loader.getTextureBufferObjectHandle();
}
std::vector<XCTexture> XCModel::loadMaterialTextures(aiMaterial * mat, aiTextureType type, std::string typeName)
{
	{
		std::vector<XCTexture> textures;
		ImageArrayLoader texLoader;
		for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
		{
			aiString str;
			mat->GetTexture(type, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (unsigned int j = 0; j < textures_loaded.size(); j++)
			{
				if (std::strcmp(textures_loaded[j].path.data, str.C_Str()) == 0)
				{
					textures.push_back(textures_loaded[j]);
					skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{   // if texture hasn't been loaded already, load it
				XCTexture texture;
				texture.id = TextureFromFile(str.C_Str(), this->directory, mat->GetTextureCount(type), texLoader);
				texture.type = typeName;
				texture.path = str.C_Str();
				textures.push_back(texture);
				textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
			}
		}
		return textures;
	}
}

GLuint XCModel::getProgramHandle()
{
	if (have_program_init)
		return programHnd;
	else
		return 0;
}
