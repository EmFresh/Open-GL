#include "Camera3D.h"

Camera3D::Camera3D(Size3D size):m_scale(1), m_projMat(1), m_rotMat(1), m_objMat(1), m_cameraUpdate(true), m_position(new Quat{0,0,0,0})
{
	//m_position = new Coord3D{-.25,-.5,0};
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
	*m_size = size;
	//*m_position = {0.f,.0f,0.f};
	//m_projMat = glm::ortho(0.f, m_size->width, 0.f, m_size->height);

	m_projMat = glm::perspective(glm::radians(90.f), m_size->width / m_size->height, .001f, m_size->depth);
	m_viewMat = glm::lookAt(glm::vec3{m_position->x,m_position->y,m_position->z}, glm::vec3{m_position->x,m_position->y,m_position->z - .1}, glm::vec3{0.f,1.f,0.f});
}

bool Camera3D::update()
{
	if(m_cameraUpdate)
	{
		//m_viewMat = glm::lookAt(glm::vec3{m_position->x,m_position->y,m_position->z + .1}, glm::vec3{m_position->x,m_position->y,m_position->z}, glm::vec3{0.f,1.f,0.f});

		m_transform.setPosition(m_position->x, m_position->y, m_position->z);
		m_transform.setScale(m_scale);
		m_objMat = m_transform.getTranslationMatrix() * m_transform.getScaleMatrix();
		
		m_cameraMat = m_projMat * m_viewMat * m_rotMat;
		m_cameraUpdate = false;

		return true;
	}
	return false;
}

void Camera3D::setPosition(Coord3D position)
{
	//int w, h;
	//glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
	//
	//position.x /= w;
	//position.y /= h;
	//position.z /= m_size->depth;
	*m_position = Quat{position.x,position.y,position.z};

	m_cameraUpdate = true;
}

void  Camera3D::movePositionBy(Coord3D position)
{
	//int w, h;
	//glfwGetFramebufferSize(glfwGetCurrentContext(), &w, &h);
	//position.x /= w;
	//position.y /= h;
	//position.z /= m_size->depth;
	*m_position += Quat{position.x,position.y,position.z};

	m_cameraUpdate = true;
}

void Camera3D::setScale(const float scale)
{
	m_scale = scale;
	m_cameraUpdate = true;
}

void Camera3D::setAngle(float angle, Coord3D direction)
{
	//glm rotation
	//m_rotMat = glm::mat4(1);
	//	m_rotMat = glm::rotate(m_rotMat, glm::radians(-angle), glm::vec3(direction.x, direction.y, direction.z));

	//my rotation
	m_rotMat = Quat::quatRotationMat(glm::radians(angle), -direction.x, direction.y, direction.z);

	m_cameraUpdate = true;
}

void Camera3D::moveAngleBy(float angle, Coord3D direction)
{
	//glm rotation
	//if(angle != 0)
	//	m_rotMat = glm::rotate(m_rotMat, glm::radians(-angle), glm::vec3(direction.x, direction.y, direction.z));

	//my rotation
	if(angle != 0)
		m_rotMat *= Quat::quatRotationMat(glm::radians(angle), -direction.x, direction.y, direction.z);

	m_cameraUpdate = true;
}

Quat& Camera3D::getPosition()
{
	return *m_position;
}

float& Camera3D::getScale()
{
	return m_scale;
}

glm::mat4 Camera3D::getCameraMatrix()
{
	return m_cameraMat;
}

glm::mat4 Camera3D::getObjectMatrix()
{
	return m_objMat;
}
