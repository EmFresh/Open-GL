#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>
#include <map>
#include "GLSLCompiler.h"
#include "StructInfo.h"
#include "ResourceManager.h"

#include "Mesh.h"

class Model
{
public:
	Model();
	Model(const char* path);
	~Model();

	void render(GLSLCompiler shader);

private:
	std::vector <Mesh> meshes;
	std::string dir;

	GLuint textureFromFile(const char *path);
	std::map<std::string, Texture2D> loadMaterialTextures(aiMaterial *mat, aiTextureType texType, std::string typeName);
	void loadModel(const char* path);
	void processNode(aiNode *node, const aiScene *scene);	
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
};
