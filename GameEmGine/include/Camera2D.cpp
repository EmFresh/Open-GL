#include "Camera2D.h"



Camera2D::Camera2D(Size2D size) :Camera3D(size)
{

}


Camera2D::~Camera2D()
{}

void Camera2D::init(Size2D size)
{
	Camera3D::init(size);
	_size;
}

void Camera2D::setPosition(Coord3D pos)
{
	*_position = {pos.x,pos.y,0};
}


