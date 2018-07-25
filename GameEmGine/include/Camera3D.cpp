#include "Camera3D.h"



Camera3D::Camera3D(Size3D size) :_scale(1),_projMat(1),_objMat(1), _cameraUpdate(true), _position(new Quat {0,0,0,0})
{
	//_position = new Coord3D{-.25,-.5,0};
	init(size);
}

Camera3D::~Camera3D()
{}

void Camera3D::init(Size3D size)
{
	int w, h;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h); //window size in pixles
	size.width /= w;
	size.height /= h;
	*_size = size;
	//*_position = {0.f,.0f,0.f};
	//_projMat = glm::ortho(0.f, _size->width, 0.f, _size->height);
	_projMat = glm::perspective(glm::radians(90.f), _size->width/ _size->height, .1f, _size->depth);
	_viewMat = glm::lookAt(glm::vec3{_position->x,_position->y,_position->z}, glm::vec3{_position->x,_position->y,_position->z-.1f}, glm::vec3{0.f,1.f,0.f});
}

bool Camera3D::update()
{
	if(_cameraUpdate)
	{
		
		_objMat = glm::translate(glm::mat4(1.f), glm::vec3(-_position->x, -_position->y, _position->z));
		_objMat = glm::scale(_objMat, glm::vec3(_scale, _scale, _scale));
		
		
		_cameraMat = _projMat * _viewMat;
		_cameraUpdate = false;
		return true;
	}
	return false;
}

void Camera3D::setPosition(Coord3D position)
{
	int w, h, d;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);

	position.x /= w;
	position.y /= h;
	*_position = Quat {position.x,position.y,position.z};
	_cameraUpdate = true;
}

void  Camera3D::moveBy(Coord3D position)
{
	int w, h, d;
	glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
	position.x /= w;
	position.y /= h;
	position.z /= _size->depth;
	*_position += Quat {position.x,position.y,position.z};

	_cameraUpdate = true;
}

void Camera3D::setScale(const float scale)
{
	_scale = scale;
	_cameraUpdate = true;
}

void Camera3D::setAngle(float angle, Coord3D direction)
{}


Quat& Camera3D::getPosition()
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
glm::mat4 Camera3D::getObjectMatrix()
{
	return _objMat;
}
