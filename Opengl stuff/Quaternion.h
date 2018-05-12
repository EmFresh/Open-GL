#pragma once
#define _USE_MATH_DEFINES  
#include <vector>
#include <iostream>
#include <cmath>
#include "Matrix.h"

#define degtorad(deg) (deg*M_PI/180)

//complete
struct Quat
{
	float w, x, y, z;
	float& operator[](int index)const
	{
		float *e = nullptr;
		switch(index)
		{
		case 0:
			return const_cast<float&>(w);
		case 1:
			return const_cast<float&>(x);
		case 2:
			return const_cast<float&>(y);
		case 3:
			return const_cast<float&>(z);
		}
		return *e;
	}

	Quat operator*(Quat a_quat)	const
	{
		Quat quat;
		Quat q2 = a_quat;
		quat.w = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
		quat.x = w * q2.x + x * q2.w + y * q2.z - z * q2.y;
		quat.y = w * q2.y - x * q2.z + y * q2.w + z * q2.x;
		quat.z = w * q2.z + x * q2.y - y * q2.x + z * q2.w;

		return quat;
	}
	Quat operator+(Quat a_quat)
	{
		Quat q1;
		for(int a = 0; a < 4; a++)
			q1[a] = this[0][a] + a_quat[a];
		return q1;
	}
	void operator+=(Quat a_quat)
	{
		for(int a = 0; a < 4; a++)
			this[0][a] += a_quat[a];

	}
};

class Quaternion : public Matrix
{
public:

	Quaternion();
	Quaternion(Quat);
	~Quaternion();

	Quaternion & rotation(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	void rotate(float a_ang, float a_dirX, float a_dirY, float a_dirZ);

	void scale(float x, float y, float z = 1);
	void scale(float xyz);
	void shear(float x, float y, float z = 1);
	void shear(float xy);

	void print()const;

	Quaternion& operator*(Quaternion a_quat)const;
	Quaternion& operator+(Quaternion a_quat);
	void operator+=(Quaternion quat);
	void operator=(Quat);
	float operator[](int)const;

private:
	Quat m_quat;
};

