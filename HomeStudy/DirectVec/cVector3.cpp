#include "stdafx.h"
#include "cVector3.h"
#include <cmath>
#include <iostream>
const float EPSILON = 0.001f;

cVector3::cVector3()
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

	return fabs(vec1 - vec2) < EPSILON ? true : false;
}

bool cVector3::operator!=(cVector3 & vec) const
{
	float vec1 = sqrt(powf(this->m_x, 2) + powf(this->m_y, 2) + powf(this->m_z, 2));
	float vec2 = sqrt(powf(vec.m_x, 2) + powf(vec.m_y, 2) + powf(vec.m_z, 2));

	return fabs(vec1 - vec2) < EPSILON ? false : true;
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
