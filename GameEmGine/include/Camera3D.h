#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "StructInfo.h"
#include "Quat.h"

class Camera3D
{
public:
	Camera3D(Size3D = {});
	~Camera3D();

	void init(Size3D);
	bool update();

	void setPosition(Coord3D);
	void moveBy(Coord3D position);
	void setScale(const float);
	void setAngle(float angle,Coord3D direction);

	Quat& getPosition();
	float& getScale();
	glm::mat4 getCameraMatrix();

	glm::mat4 getObjectMatrix();
	
protected:
	bool _cameraUpdate;
	float _scale;
	Size3D *_size = new Size3D;
	Quat *_position;

	glm::mat4 _cameraMat;
	glm::mat4 _projMat;
	glm::mat4 _viewMat;
	glm::mat4 _objMat;
};

