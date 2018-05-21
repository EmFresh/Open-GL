#include "Quat.h"

using namespace std;

Quat::Quat()
{}

Quat::Quat(float x, float y, float z) :w(0), x(x), y(y), z(z)
{}

Quat::Quat(float w, float x, float y, float z) : w(w), x(x), y(y), z(z)
{}

Quat & Quat::rotation(float a_ang, float a_dirX, float a_dirY, float a_dirZ)
{

	float unit(sqrt(pow(a_dirX, 2) + pow(a_dirY, 2) + pow(a_dirZ, 2)));

	Quat
		q {cos(a_ang / 2),sin(a_ang / 2)*  (a_dirX / unit),sin(a_ang / 2)*  (a_dirY / unit),sin(a_ang / 2)*  (a_dirZ / unit)},
		qc {cos(a_ang / 2),sin(a_ang / 2)* -(a_dirX / unit),sin(a_ang / 2)* -(a_dirY / unit),sin(a_ang / 2)* -(a_dirZ / unit)},
		p {0, x,y,z};
	Quat rot = q * p * qc;
	return rot;
}

void Quat::rotate(float a_ang, float a_dirX, float a_dirY, float a_dirZ)
{
	*this = rotation(a_ang, a_dirX, a_dirY, a_dirZ);
}

void Quat::scale(float x, float y, float z)
{

}

void Quat::scale(float xyz)
{
	scale(xyz, xyz, xyz);
}

void Quat::shear(float x, float y, float z)
{}

void Quat::shear(float xy)
{}

void Quat::print() const
{
	printf("(");
	for(int a = 0; a < 4; a++)
		printf(std::string("%f" + std::string(a != 3 ? ", " : "")).c_str(), this[0][a]);
	printf(")\n\n");
}

float& Quat::operator[](int index)const
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

Quat Quat::operator*(Quat a_quat)	const
{
	Quat quat;
	Quat q2 = a_quat;
	quat.w = w * q2.w - x * q2.x - y * q2.y - z * q2.z;
	quat.x = w * q2.x + x * q2.w + y * q2.z - z * q2.y;
	quat.y = w * q2.y - x * q2.z + y * q2.w + z * q2.x;
	quat.z = w * q2.z + x * q2.y - y * q2.x + z * q2.w;

	return quat;
}
Quat Quat::operator+(Quat a_quat)
{
	Quat q1;
	for(int a = 0; a < 4; a++)
		q1[a] = this[0][a] + a_quat[a];
	return q1;
}
void Quat::operator+=(Quat a_quat)
{
	for(int a = 0; a < 4; a++)
		this[0][a] += a_quat[a];

}

Quat Quat::operator-(Quat a_quat)
{
	Quat q1;
	for(int a = 0; a < 4; a++)
		q1[a] = this[0][a] - a_quat[a];
	return q1;
}

void Quat::operator-=(Quat a_quat)
{
	for(int a = 0; a < 4; a++)
		this[0][a] -= a_quat[a];
}
