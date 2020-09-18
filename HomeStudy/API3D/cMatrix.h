#pragma once
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include <Windows.h>



class cMatrix
{
public:
	cMatrix();
	~cMatrix();

	// >> : 
private:
	class cRow
	{
	private:
		std::vector<float> m_vecData;

	public:
		cRow();
		cRow(int nDimension);
		~cRow() {}
		void Resize(int nDimension);
		float& operator[](int nIndex);
	};

	std::vector<cRow> m_vecData;

public:

	// >> : 
	cMatrix(int nDimension);

	void	Print();
	void	Resize(int nDimension);
	int		Dimension();

	static	cMatrix Identity(int nDimension);

	cRow&	operator[](int nIndex);
	bool	operator==(cMatrix& mat);
	bool	operator!=(cMatrix& mat);
	cMatrix operator+(cMatrix& mat);
	cMatrix operator-(cMatrix& mat);
	cMatrix operator*(cMatrix& mat);
	cMatrix operator*(float f);

	cMatrix Inverse(OUT float& fDeterminant);
	float	Determinant();
	cMatrix Adjoint();
	cMatrix Transpose();
	float	Cofactor(int nRow, int nCol);
	float	Minor(int nRow, int nCol);


	//>>:
	static cMatrix Translation(float x, float y, float z);
	static cMatrix Translation(cVector3& v);
	static cMatrix RotatinX(float Angle);
	static cMatrix RotatinY(float Angle);
	static cMatrix RotatinZ(float Angle);
	
	static cMatrix View(cVector3& vEye,cVector3& vLookAt,cVector3& vUp);
	static cMatrix Projection(float fFovY, float fAspect, float fNearZ, float fFarZ);
	static cMatrix ViewPort(float x, float y, float w, float h, float minz, float maxz);





};

