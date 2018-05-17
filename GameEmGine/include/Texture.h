#pragma once
#include <GL\glew.h>
struct Texture2D
{
	GLuint id;
	int width, height;
};

struct Texture3D
{
	GLuint id;
	int width, height, depth;
};

