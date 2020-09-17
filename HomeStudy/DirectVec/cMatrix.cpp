#include "stdafx.h"
#include "cMatrix.h"
#include <random>

using namespace std;

cMatrix::cMatrix()
{
}

cMatrix::~cMatrix()
{
}

cMatrix::cMatrix(int nDimension):dimension(nDimension)
{
	std::vector<float> insert;
 	for (int i = 0; i < nDimension; i++)
	{
		matrix.push_back(insert);

		for (int j = 0; j < nDimension; j++)
		{
			matrix[i].push_back(float(rand() % 2));
		}
	}



}

void cMatrix::Print()
{
	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			cout << matrix[i][j]<<"  ";
		}
		cout << endl;
	}
}

void cMatrix::Resize(int nDimension)
{
}

cMatrix cMatrix::Identity(int nDimension)
{
	return cMatrix();
}

bool cMatrix::operator==(cMatrix & mat)
{
	if (this->dimension != mat.dimension)
		return false;

	if (this->matrix != mat.matrix)
		return false;

	return true;
}

bool cMatrix::operator!=(cMatrix & mat)
{
	if (this->dimension != mat.dimension)
		return true;

	if (this->matrix != mat.matrix)
		return true;

	return false;

}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix temp(dimension);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] + mat.matrix[i][j];
		}
	}

	return temp;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix temp(dimension);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j] - mat.matrix[i][j];
		}
	}

	return temp;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{
	cMatrix temp(dimension);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			float element = 0;
			for (int k = 0; k < dimension; k++)
			{
				element += matrix[i][k] * mat.matrix[k][j];
			}
			temp.matrix[i][j] = element;
		}
	}

	return temp;
}

cMatrix cMatrix::operator*(float & f)
{
	cMatrix temp(dimension);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			temp.matrix[i][j] = this->matrix[i][j];
			temp.matrix[i][j] *= f;
		}
	}

	return temp;
}

cMatrix cMatrix::Transpose() //전치행렬
{
	cMatrix temp(dimension);

	for (int i = 0; i < dimension; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			temp.matrix[j][i] = this->matrix[i][j];
		}
	}

	return temp;
}

cMatrix cMatrix::Inverse(OUT float & fDeterminant)
{
	return cMatrix();
}

float cMatrix::Determinant()
{
	return 0.0f;
}

cMatrix cMatrix::Adjoint()
{
	return cMatrix();
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	return pow(-1, nRow + nCol) * Minor(nRow, nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{


	
	return 0.0f;
}

