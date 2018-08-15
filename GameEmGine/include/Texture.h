#pragma once
#include <GL\glew.h>
#include <string>

struct Texture2D
{
	GLuint id;
	int width, height;
	std::string type="",path="";
	
	bool operator==(Texture2D arg)
	{
		return id == arg.id;
	}
};

struct Texture3D
{
	GLuint id;
	int width, height, depth;
};

