#pragma once
#include <iostream>
using namespace std;

class cMatrix;

class cVector3
{
public:
	cVector3();
	cVector3(float x, float y, float z);
	~cVector3();

private:
	float m_x, m_y, m_z;

public:
	bool operator==(cVector3& vec) const;
	bool operator!=(cVector3& vec) const;
	cVector3 operator+(cVector3& vec) const;
	cVector3 operator-(cVector3& vec) const;
	cVector3 operator*(float f) const;
	cVector3 operator/(float f) const;
	void print();


	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	float getZ() const { return m_z; }

	void SetX(float x) { m_x = x; }
	void SetY(float y) { m_y = y; }
	void SetZ(float z) { m_z = z; }

	
	void setVector(float x, float y, float z) { this->m_x = x; this->m_y = y; this->m_z = z; }

	float Length();
	cVector3 Normlize();
	static float Angele(cVector3& v1, cVector3& v2);

	static cVector3 TransformCoord(cVector3& v, cMatrix& mat);//점이동
	static cVector3 TransformNormal(cVector3& v, cMatrix& mat);//벡터가 이동


};

