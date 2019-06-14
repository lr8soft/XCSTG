#pragma once
#ifndef _XCMODEL_H_
#define _XCMODEL_H_
#include "XCMesh.h"
#include <vector>
class XCModel {
private:
	/*  Model Data */
	std::vector<XCTexture> textures_loaded;	// stores all the textures loaded so far, optimization to make sure textures aren't loaded more than once.
	std::vector<XCMesh> meshes;
	std::string directory;
	bool gammaCorrection;
	static GLuint programHnd;
	static bool have_program_init;
public:

	/*  Functions   */
	// constructor, expects a filepath to a 3D model.
	XCModel(std::string const &path, bool gamma = false) : gammaCorrection(gamma)
	{
		loadModel(path);
	}

	static GLuint getProgramHandle();

	// draws the model, and thus all its meshes
	void Draw();

private:
	/*  Functions   */
	// loads a model with supported ASSIMP extensions from file and stores the resulting meshes in the meshes vector.
	void loadModel(std::string const &path);

	// processes a node in a recursive fashion. Processes each individual mesh located at the node and repeats this process on its children nodes (if any).
	void processNode(aiNode *node, const aiScene *scene);

	XCMesh processMesh(aiMesh *mesh, const aiScene *scene);

	// checks all material textures of a given type and loads the textures if they're not loaded yet.
	// the required info is returned as a Texture struct.
	std::vector<XCTexture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
};



#endif