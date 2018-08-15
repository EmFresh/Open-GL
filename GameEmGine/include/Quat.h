#pragma once
#define _USE_MATH_DEFINES 
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include <cmath>
//#include "Matrix.h"

#define degtorad(deg) (deg*M_PI/180)

//complete
struct Quat
{
	float  x, y, z;
	Quat();
	Quat(float x, float y, float z);
	Quat(float w, float x, float y, float z);

	Quat& normal();
	void normalize();

	Quat & rotation(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	Quat & rotation(Quat p, Quat q, Quat qc);

	void rotate(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	static glm::mat4 quatRotationMat(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	void print() const;

	float& operator[](int index)const;
	Quat operator*(Quat a_quat)	const;
	Quat operator+(Quat a_quat)const;
	void operator+=(Quat a_quat)const;
	Quat operator-(Quat a_quat)const;
	void operator-=(Quat a_quat)const;
private:
	float w;
};
