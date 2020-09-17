#pragma once
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
//	std::vector<cRow> matrix;
	std::vector<std::vector<float>> matrix;
	int dimension;
public:
	cMatrix(int nDimension);   //�������

	void Print();
	void Resize(int nDimension);

	static cMatrix Identity(int nDimension);   //�׵����
	//cRow &operator[](int nIndex);

	// =  = = = = = ===================================
	bool operator == (cMatrix& mat);
	bool operator != (cMatrix& mat);
	cMatrix operator + (cMatrix &mat);
	cMatrix operator - (cMatrix &mat);
	cMatrix operator * (cMatrix &mat);
	cMatrix operator * (float &f);
	cMatrix Transpose();
	cMatrix Inverse(OUT float& fDeterminant);
	float Determinant();
	cMatrix Adjoint();
	float Cofactor(int nRow, int nCol);
	float Minor(int nRow, int nCol);   //minor ����� determinant ���ϱ�
};

