#include "Camera3D.h"



Camera3D::Camera3D(Size2D size) :_orthoMat(1.0), _scale(1), _cameraUpdate (true),_position(new Coord3D)
{
	_position->x=-.5;
	init(size);
}

Camera3D::~Camera3D()
{}

void Camera3D::init(Size2D size)
{
	int w, h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
	size.width /= w;
	size.height /= h;
	*_size = size;
	
	_orthoMat = glm::ortho(0.f, _size->width, 0.f, _size->height);
}

bool Camera3D::update()
{
	if(_cameraUpdate)
	{
		_cameraMat = glm::translate(_orthoMat, glm::vec3(-_position->x, -_position->y, -_position->z));
		_cameraMat = glm::scale(_cameraMat, glm::vec3(_scale, _scale, _scale));
		_cameraUpdate = false;
		return true;
	}
	return false;
}

void Camera3D::setPosition(const Coord3D position)
{
	int w, h,d;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
	
	*_position = position;
	_position->x /= w;
	_position->y /= h;
	_cameraUpdate = true;
}

void  Camera3D::moveBy(const Coord3D position)
{
	*_position += position;
	_cameraUpdate = true;
}

void Camera3D::setScale(const float scale)
{
	_scale = scale;
	_cameraUpdate = true;
}


Coord3D& Camera3D::getPosition()
{
	return *_position;
}

float& Camera3D::getScale()
{
	return _scale;
}

glm::mat4 Camera3D::getCameraMatrix()
{
	return _cameraMat;
}
