#pragma once
#include <GL\glew.h>
#include "StructInfo.h"


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

