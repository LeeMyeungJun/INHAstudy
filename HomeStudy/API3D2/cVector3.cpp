#include "stdafx.h"
#include "cVector3.h"
#include <cmath>
#include <iostream>
const float EPSILON = 0.00001f;

cVector3::cVector3():m_x(0),m_y(0),m_z(0)
{
}

cVector3::cVector3(float x, float y, float z):m_x(x),m_y(y),m_z(z)
{

}

cVector3::~cVector3()
{
}

bool cVector3::operator==(cVector3 & vec) const
{
	float vec1 = sqrt(powf(this->m_x,2) + powf(this->m_y,2) + powf(this->m_z,2));
	float vec2 = sqrt(powf(vec.m_x, 2) + powf(vec.m_y, 2) + powf(vec.m_z, 2));

	return fabs(vec1 - vec2) < EPSILON ? false : true;
}

bool cVector3::operator!=(cVector3 & vec) const
{
	float vec1 = sqrt(powf(this->m_x, 2) + powf(this->m_y, 2) + powf(this->m_z, 2));
	float vec2 = sqrt(powf(vec.m_x, 2) + powf(vec.m_y, 2) + powf(vec.m_z, 2));

	return fabs(vec1 - vec2) < EPSILON ? true : false;
}

cVector3 cVector3::operator+(cVector3 & vec) const
{
	cVector3 vecTemp;
	vecTemp.m_x = this->m_x + vec.m_x;
	vecTemp.m_y = this->m_y + vec.m_y;
	vecTemp.m_z = this->m_z + vec.m_z;

	return vecTemp;
}

cVector3 cVector3::operator-(cVector3 & vec) const
{
	cVector3 vecTemp;
	vecTemp.m_x = this->m_x - vec.m_x;
	vecTemp.m_y = this->m_y - vec.m_y;
	vecTemp.m_z = this->m_z - vec.m_z;

	return vecTemp;
}

cVector3 cVector3::operator*(float f) const
{
	cVector3 vecTemp;
	vecTemp.m_x = this->m_x * f;
	vecTemp.m_y = this->m_y * f;
	vecTemp.m_z = this->m_z * f;

	return vecTemp;
}

cVector3 cVector3::operator/(float f) const
{
	cVector3 vecTemp;
	vecTemp.m_x = this->m_x / f;
	vecTemp.m_y = this->m_y / f;
	vecTemp.m_z = this->m_z / f;

	return vecTemp;
}



float cVector3::Dot(cVector3 & v1, cVector3 & v2)
{
	return v1.m_x*v2.m_x + v1.m_y*v2.m_y + v1.m_z*v2.m_z;
}

cVector3 cVector3::Cross(cVector3 & v1, cVector3 & v2)
{
	cVector3 vecTemp;
	vecTemp.m_x = v1.m_y * v2.m_z - v1.m_z*v2.m_y;
	vecTemp.m_y = v1.m_z * v2.m_x - v1.m_x * v2.m_z;
	vecTemp.m_z = v1.m_x * v2.m_y - v1.m_y * v2.m_x;

	return vecTemp;
}


float cVector3::Length()
{
	return sqrt(powf(this->m_x, 2) + powf(this->m_y, 2) + powf(this->m_z, 2));
}

cVector3 cVector3::Normlize()
{
	cVector3 vecTemp;
	vecTemp.m_x = this->m_x / Length();
	vecTemp.m_y = this->m_y / Length();
	vecTemp.m_z = this->m_z / Length();

	return vecTemp;
}

float cVector3::Angele(cVector3 & v1, cVector3 & v2)
{
	float temp = Dot(v1, v2) / (v1.Length()*v2.Length());

	return acos(temp) * 180 / 3.14159265359;
}

cVector3 cVector3::TransformCoord(cVector3& v, cMatrix& mat)
{
	cVector3 TransformVector3;
	float w = 1.0f;
	TransformVector3.SetX(v.getX() * mat[0][0] + v.getY() * mat[1][0] + v.getZ() * mat[2][0] + w * mat[3][0]);
	TransformVector3.SetY(v.getX() * mat[0][1] + v.getY() * mat[1][1] + v.getZ() * mat[2][1] + w * mat[3][1]);
	TransformVector3.SetZ(v.getX() * mat[0][2] + v.getY() * mat[1][2] + v.getZ() * mat[2][2] + w * mat[3][2]);
	w = v.getX() * mat[0][3] + v.getY() * mat[1][3] + v.getZ() * mat[2][3] + w * mat[3][3];

	if (w <= EPSILON && w >= -EPSILON) return TransformVector3;

	TransformVector3.SetX(TransformVector3.getX() / w);
	TransformVector3.SetY(TransformVector3.getY() / w);
	TransformVector3.SetZ(TransformVector3.getZ() / w);

	return TransformVector3;
}

cVector3 cVector3::TransformNormal(cVector3& v, cMatrix& mat)
{
	cVector3 newVec(0, 0, 0);
	newVec.SetX(mat[0][0] * v.getX() + mat[1][0] * v.getY() + mat[2][0] * v.getZ() + mat[3][0]);
	newVec.SetY(mat[0][1] * v.getX() + mat[1][1] * v.getY() + mat[2][1] * v.getZ() + mat[3][1]);
	newVec.SetZ(mat[0][2] * v.getX() + mat[1][2] * v.getY() + mat[2][2] * v.getZ() + mat[3][2]);

	return newVec;
}