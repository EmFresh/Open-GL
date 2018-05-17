#pragma once
#define _USE_MATH_DEFINES  
#include <vector>
#include <iostream>
#include <cmath>
//#include "Matrix.h"

#define degtorad(deg) (deg*M_PI/180)

//complete
struct Quat
{
	float w, x, y, z;


	Quat & rotation(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	void rotate(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	void scale(float x, float y, float z);

	void scale(float xyz);

	void shear(float x, float y, float z);

	void shear(float xy);

	void print() const;

	float& operator[](int index)const;

	Quat operator*(Quat a_quat)	const;
	Quat operator+(Quat a_quat);
	void operator+=(Quat a_quat);
};
