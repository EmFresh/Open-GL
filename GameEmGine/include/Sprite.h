#pragma once
#include "ResourceManager.h"
#include "GLSLCompiler.h"
#include "Quaternion.h"
#include <cstdio>
#include <cstddef>

struct Coord2D
{
	float x = 0, y = 0;
	float& operator[](int index)
	{
		float *error = nullptr;
		switch(index)
		{
		case 0:
			return static_cast<float&>(x);
		case 1:
			return static_cast<float&>(y);
		}
		return *error;
	}

	Coord2D operator+(Coord2D coord)
	{
		return {x + coord.x, y + coord.y};
	}
	Coord2D operator-(Coord2D coord)
	{
		return {x - coord.x, y - coord.y};
	}
	void operator-=(Coord2D coord)
	{
		x - coord.x;
		y - coord.y;
	}
	void operator+=(Coord2D coord)
	{
		x + coord.x;
		y + coord.y;
	}
};

struct Size2D
{
	float width = 0, height = 0;
	float& operator[](int index)
	{
		float *error = nullptr;
		switch(index)
		{
		case 0:
			return static_cast<float&>(width);
		case 1:
			return static_cast<float&>(height);
		}
		return *error;
	}
};

struct Colour
{
	GLubyte r = 255, g = 255, b = 255, a = 255;
	GLubyte& operator[](int index)
	{
		GLubyte *error = nullptr;
		switch(index)
		{
		case 0:
			return static_cast<GLubyte&>(r);
		case 1:
			return static_cast<GLubyte&>(g);
		case 2:
			return static_cast<GLubyte&>(b);
		case 3:
			return static_cast<GLubyte&>(a);
		}
		return *error;
	}
};

struct UV
{
	float u = 0, v = 0;
};

struct VboInfo2D
{
	VboInfo2D(Coord2D c= {0,0}, Size2D s= {0,0})
	{
		position = c;
		size = s;
	}

	Coord2D position;
	Size2D size;
protected:
	float _angle;
};

struct Vertex2D
{
	Coord2D coord;
	Colour	colour;
	UV uv;

	void setCoord2D(float x, float y)
	{
		coord.x = x;
		coord.y = y;
	}
	//uses the 0-255 representation instead of 0-1
	void setColour(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 255)
	{
		colour.r = r;
		colour.g = g;
		colour.b = b;
		colour.a = a;
	}
	//sets uv
	void setUV(float u, float v)
	{
		uv.u = u;
		uv.v = v;
	}

	void print()
	{
		printf("Coord2D: (%f, %f)\n", coord.x, coord.y);
		printf("Colour : (%d, %d, %d, %d)\n", colour.r, colour.g, colour.b, colour.a);
		printf("UV     : (%f, %f)\n\n", uv.u, uv.v);
	}
};

class Sprite : protected VboInfo2D
{
public:
	Sprite();
	Sprite(VboInfo2D);
	Sprite(VboInfo2D, const char* path);
	~Sprite();
	void draw();
	void setPosition(float, float);
	void setRotation(float);
	void rotateBy(float);

private:
	void init();
	void init(const char* path);
	GLuint _vboID,_bound;
	Texture2D _texture;
	Vertex2D _vertData[6];
	static GLSLCompiler* _textureShader;
};

