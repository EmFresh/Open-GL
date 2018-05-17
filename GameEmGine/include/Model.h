#pragma once
#include <GL\glew.h>

struct Coord3D
{
	float x, y, z;
	float& operator[] (int index){
		float* error=nullptr;
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

class Model
{
public:
	Model();
	Model(vboInfo3D);
	~Model();

	void init(vboInfo3D);

	void draw();
private:
	vboInfo3D _info;
	GLuint _vboID;
};

