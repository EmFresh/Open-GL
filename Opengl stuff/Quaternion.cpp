#include "Quaternion.h"

using namespace std;


//Quaternion::Quaternion()
//{}
//
//Quaternion::Quaternion(Quat a_quat) :m_quat(a_quat),
//Matrix(&vector<vector<float>>
//{
//	{
//		a_quat.w, a_quat.x, a_quat.y, a_quat.z
//	}
//})
//{
//
//}
//
//Quaternion::~Quaternion()
//{}
//
//Quat & Quaternion::getQuat()
//{
//	return m_quat;
//}
//
//Quaternion& Quaternion::rotation(float a_ang, float a_dirX, float a_dirY, float a_dirZ)
//{
//
//	float unit(sqrt(pow(a_dirX, 2) + pow(a_dirY, 2) + pow(a_dirZ, 2)));
//
//	Quat
//		q {cos(a_ang / 2),sin(a_ang / 2)*  (a_dirX / unit),sin(a_ang / 2)*  (a_dirY / unit),sin(a_ang / 2)*  (a_dirZ / unit)},
//		qc {cos(a_ang / 2),sin(a_ang / 2)* -(a_dirX / unit),sin(a_ang / 2)* -(a_dirY / unit),sin(a_ang / 2)* -(a_dirZ / unit)},
//		p {0, m_quat.x,m_quat.y,m_quat.z};
//	Quaternion rot = q * p * qc;
//	return rot;
//}
//
//void Quaternion::rotate(float a_ang, float a_dirX, float a_dirY, float a_dirZ)
//{
//	*this = rotation(a_ang, a_dirX, a_dirY, a_dirZ);
//}
//
//void Quaternion::scale(float x, float y, float z)
//{
//	Matrix::scale(x, y, z);
//	for(int a = 0; a < 4; a++)
//		m_quat[a] = m_matrix[0][0][a];
//}
//
//void Quaternion::scale(float xyz)
//{
//	scale(xyz, xyz, xyz);
//}
//
//void Quaternion::shear(float x, float y, float z)
//{}
//
//void Quaternion::shear(float xy)
//{}
//
//void Quaternion::print() const
//{
//	printf("(");
//	for(int a = 0; a < 4; a++)
//		printf(std::string("%f" + std::string(a != 3 ? ", " : "")).c_str(), m_quat[a]);
//	printf(")\n\n");
//}
//
//Quaternion& Quaternion::operator*(Quaternion a_quat)const
//{
//	Quaternion quat({});
//	Quat q1 = m_quat, q2 = a_quat.m_quat;
//	quat.m_quat.w = q1.w*q2.w - q1.x*q2.x - q1.y*q2.y - q1.z*q2.z;
//	quat.m_quat.x = q1.w*q2.x + q1.x*q2.w + q1.y*q2.z - q1.z*q2.y;
//	quat.m_quat.y = q1.w*q2.y - q1.x*q2.z + q1.y*q2.w + q1.z*q2.x;
//	quat.m_quat.z = q1.w*q2.z + q1.x*q2.y - q1.y*q2.x + q1.z*q2.w;
//	return quat;
//}
//
//Quaternion& Quaternion::operator+(Quaternion a_quat)
//{									 
//	Quaternion q1(m_quat + a_quat.m_quat);	
//	return	q1;
//}
//
//void Quaternion::operator+=(Quaternion a_quat)
//{
//	
//		m_quat += a_quat.m_quat;
//	Matrix::operator=(&vector<vector<float>>
//	{
//		{
//			m_quat.w, m_quat.x, m_quat.y, m_quat.z
//		}
//	});
//}
//
//void Quaternion::operator=(Quat a_quat)
//{
//	m_quat = a_quat;
//	Matrix::operator=(&vector<vector<float>>
//	{
//		{
//			a_quat.w, a_quat.x, a_quat.y, a_quat.z
//		}
//	});
//
//}
//
//float Quaternion::operator[](int a_index)const
//{
//	return m_quat[a_index];
//}
