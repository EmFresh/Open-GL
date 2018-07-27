#pragma once
#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <assimp/mesh.h>
#include <vector>
#include "GLSLCompiler.h"
#include "StructInfo.h"
#include "ResourceManager.h"

class Mesh
{
public:
	Mesh();
	Mesh(std::vector<Vertex3D>verts,
			   std::vector<GLuint>indicies,
			   std::vector<Texture2D>textures);
	~Mesh();

	void render(GLSLCompiler shader);

private:
	void init();

	GLuint m_vboID, m_vaoID, m_iboID;
	std::vector<Vertex3D> m_verts;
	std::vector<GLuint>   m_indicies;
	std::vector<Texture2D> m_textures;
};

