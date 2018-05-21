#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "StructInfo.h"
#include "GLSLCompiler.h"

class Camera3D
{
public:
	Camera3D(Size2D = {});
	~Camera3D();

	void init(Size2D);
	bool update();

	void setPosition(const Coord3D);
	void moveBy(const Coord3D position);
	void setScale(const float);

	Coord3D& getPosition();
	float& getScale();
	glm::mat4 getCameraMatrix();

protected:
	bool _cameraUpdate;
	float _scale;
	Size2D *_size = new Size2D;
	Coord3D *_position = new Coord3D;
	glm::mat4 _cameraMat;
	glm::mat4 _orthoMat;
};

