#pragma once
#include <GL/glew.h>
#include <string>
#include <cstdio>

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
		x -= coord.x;
		y -= coord.y;
	}
	void operator+=(Coord2D coord)
	{
		x += coord.x;
		y += coord.y;
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

struct Coord3D
{
	float x = 0, y = 0, z = 0;
	float& operator[] (int index)
	{
		float* error = nullptr;
		switch(index)
		{
		case 0:
			return const_cast<float&>(x);
		case 1:
			return const_cast<float&>(y);
		case 2:
			return const_cast<float&>(z);
		}
		return *error;
	}

	Coord3D operator+(Coord3D coord)
	{
		return {x + coord.x, y + coord.y, z + coord.z};
	}
	Coord3D operator-(Coord3D coord)
	{
		return {x - coord.x, y - coord.y, z + coord.z};
	}
	void operator-=(Coord3D coord)
	{
		x -= coord.x;
		y -= coord.y;
	}
	void operator+=(Coord3D coord)
	{
		x += coord.x;
		y += coord.y;
	}
};

struct Size3D
{
	float width, height, depth;

	float& operator[] (int index)
	{
		float* error = nullptr;
		switch(index)
		{
		case 0:
			return const_cast<float&>(width);
		case 1:
			return const_cast<float&>(height);
		case 2:
			return const_cast<float&>(depth);
		}
		return *error;
	}
};

struct vboInfo3D
{
	Coord3D pos;
	Size3D size;
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
	VboInfo2D(Coord2D c = {0,0}, Size2D s = {0,0})
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

struct WindowInfo
{
	std::string *title = new std::string;
	Size3D  *size;
	Coord2D *position;
	int monitor;
	void print()
	{
		printf("Title    : %s\n\n", title->c_str());
		printf("Position : (%f, %f)\n", position->x, position->y);
		printf("Size     : (%d, %d, %d)\n", size->width, size->height, size->depth);
		printf("Monitor  : %d\n\n", monitor);
	}
};