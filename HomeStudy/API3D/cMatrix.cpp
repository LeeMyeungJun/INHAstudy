#include "stdafx.h"
#include "cMatrix.h"


#define EPSILON 0.00001f
#define PI 3.141592
cMatrix::cMatrix()
{
}


cMatrix::~cMatrix()
{
}

cMatrix::cRow::cRow()
{
}

cMatrix::cRow::cRow(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::cRow::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
}

float & cMatrix::cRow::operator[](int nIndex)
{
	return m_vecData[nIndex];
}

cMatrix::cMatrix(int nDimension)
{
	Resize(nDimension);
}

void cMatrix::Print()
{
	for(int i = 0 ; i<Dimension();i++)
	{
		for(int j = 0 ; j<Dimension();j++)
		{
			printf("%8.2f", (*this)[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void cMatrix::Resize(int nDimension)
{
	m_vecData.resize(nDimension);
	for(size_t i = 0; i < nDimension; i++)
	{
		m_vecData[i].Resize(nDimension);
	}
}

int cMatrix::Dimension()
{
	return (int)m_vecData.size();
}

cMatrix cMatrix::Identity(int nDimension)
{
	cMatrix matRet(nDimension);
	for(int i = 0 ; i <nDimension ; i++)
	{
		for(int j = 0 ; j < nDimension; j++)
		{
			matRet[i][j] = (i == j) ? 1 : 0;
		}
	}
	return matRet;
}

cMatrix::cRow & cMatrix::operator[](int nIndex)
{
	return m_vecData[nIndex];
}

bool cMatrix::operator==(cMatrix & mat)
{
	for(int i = 0; i< Dimension();i++) //x
	{
		for(int j = 0 ; j < Dimension();j++)
		{
			if ((*this)[i][j] - EPSILON > mat[i][j])
				return false;
			if ((*this)[i][j] + EPSILON < mat[i][j])
				return false;
		}
	}
	return true;
}

bool cMatrix::operator!=(cMatrix & mat)
{
	return !((*this)==mat);
}

cMatrix cMatrix::operator+(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for(int i = 0 ; i < Dimension();i++)
	{
		for(int j = 0 ; j <Dimension();j++)
		{
			matRet[i][j] = (*this)[i][j] + mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator-(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j <Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] - mat[i][j];
		}
	}
	return matRet;
}

cMatrix cMatrix::operator*(cMatrix & mat)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		
		for (int j = 0; j <Dimension(); j++)
		{
			matRet[i][j] = 0.f;
			for(int k= 0; k<Dimension();k++)
			{
				matRet[i][j] += (*this)[i][k] * mat[k][j];
			}
		}
			
	}
	return matRet;
}

cMatrix cMatrix::operator*(float f)
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j <Dimension(); j++)
		{
			matRet[i][j] = (*this)[i][j] * f;
		}
	}
	return matRet;
}

cMatrix cMatrix::Inverse(OUT float & fDeterminant)//역행렬 
{
	cMatrix matRet = cMatrix::Identity(Dimension());
	fDeterminant = Determinant();
	if(-EPSILON<fDeterminant && fDeterminant < EPSILON) //들가면 0이라는이야기
	{
		std::cout << "역행렬이 존재하지 않음!!" << std::endl;
		return matRet;
	}
	cMatrix matAdj = Adjoint();

	matRet = matAdj*(1 / fDeterminant);
	
	return matRet;
}

float cMatrix::Determinant()
{
	if(Dimension() == 1)
	{
		return (*this)[0][0];
	}

	if(Dimension() == 2)
	{
		return (*this)[0][0] * (*this)[1][1] - (*this)[1][0] * (*this)[0][1];
	}
	float fDeterminant = 0.0f;

	for(int i = 0; i < Dimension();i++)
	{
		fDeterminant += ((*this)[i][0] * Cofactor(i, 0));
	}
	
	return fDeterminant;
}

cMatrix cMatrix::Adjoint()
{
	cMatrix matRet(Dimension());
	for(int i = 0;i<Dimension();i++)
	{
		for(int j = 0;j<Dimension();j++)
		{
			matRet[i][j] = Cofactor(j, i);
		}
	}
	return matRet;
}

cMatrix cMatrix::Transpose() //전치행렬 
{
	cMatrix matRet(Dimension());
	for (int i = 0; i < Dimension(); i++)
	{
		for (int j = 0; j <Dimension(); j++)
		{
			matRet[i][j] = (*this)[j][i];
		}
	}
	return matRet;
}

float cMatrix::Cofactor(int nRow, int nCol)
{
	int nConst = 1;
	if((nRow +nCol) %2 != 0)
		nConst = -1;
	
	
	return nConst*Minor(nRow,nCol);
}

float cMatrix::Minor(int nRow, int nCol)
{
	cMatrix matMinor(Dimension() - 1);
	int nMinorRow = 0; int nMinorCol = 0;
	for(int i = 0 ; i < Dimension();i++)
	{
		if(nRow == i ) continue;
		nMinorCol = 0;
		for(int j = 0; j < Dimension();j++)
		{
			if (nCol == j) continue;
			matMinor[nMinorRow][nMinorCol] = (*this)[i][j];
			++nMinorCol;
		}
		++nMinorRow;
	}
	return matMinor.Determinant();
}

cMatrix cMatrix::Translation(float x, float y, float z)
{
	cMatrix matRet(4);
	for(int i = 0 ; i < 4; i++)
	{
		for(int j = 0 ; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
		matRet[i][i] = 1;
	}

	matRet[3][0] = x;
	matRet[3][1] = y;
	matRet[3][2] = z;

	return matRet;
}

cMatrix cMatrix::Translation(cVector3& v)
{
	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
		matRet[i][i] = 1;
	}


	matRet[0][3] = v.getX();
	matRet[1][3] = v.getY();
	matRet[2][3] = v.getZ();

	return matRet;
}

cMatrix cMatrix::RotatinX(float Angle)
{
	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
		matRet[i][i] = 1;
	}

	matRet[1][1] = cos(Angle * (PI / 180));
	matRet[2][2] = cos(Angle * (PI / 180));
	matRet[1][2] = sin(Angle * (PI / 180));
	matRet[2][1] = sin(Angle * (PI / 180)) * -1;

	return matRet;
}

cMatrix cMatrix::RotatinY(float Angle)
{
	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
		matRet[i][i] = 1;
	}



	matRet[0][0] = cos(Angle * (PI / 180));
	matRet[2][2] = cos(Angle * (PI / 180));
	matRet[0][2] = sin(Angle * (PI / 180)) * -1;
	matRet[2][0] = sin(Angle * (PI / 180));
	return matRet;
}

cMatrix cMatrix::RotatinZ(float Angle)
{
	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
		matRet[i][i] = 1;
	}



	matRet[0][0] = cos(Angle * (PI / 180));
	matRet[1][1] = cos(Angle * (PI / 180));
	matRet[0][1] = sin(Angle * (PI / 180));
	matRet[1][0] = sin(Angle * (PI / 180)) * -1;
	return matRet;
}

//시야시점 벡터랑 내가바라보는 방향의 벡터와 내머리위 
	//뷰에서 > 프로젝션을 > 뷰포트를 프로젝션에 투영  
//내눈위치-5 5 0     0 0 0			 머리위0 1 0
cMatrix cMatrix::View(cVector3& vEye, cVector3& vLookAt, cVector3& vUp)
{
	/*
	*ViewMatrix
	*eye , lookat , up
	*
	*l = look vector
	*r = right vector
	*u = up vector
	*
	*		r.x						u.x		l.x				0
	*		r.y						u.y		l.y				0
	*		r.z						u.z		l.z				0
	*		-r dot eye		-u dot eye		-l dot eye		0
	*		
	* 내가바라볼 지점에서 물건이랑 빼서 외적을해서 right vector가나옴   
	*/

	vLookAt = vLookAt - vEye;
	cVector3 rightVector = cVector3::Cross(vUp, vLookAt);
	vUp = cVector3::Cross(vLookAt, rightVector).Normlize();
	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
	}

	matRet[0][0] = rightVector.getX();
	matRet[1][0] = rightVector.getY();
	matRet[2][0] = rightVector.getZ();
	matRet[3][0] = cVector3::Dot(rightVector*-1,vEye);

	matRet[0][1] = vUp.getX();
	matRet[1][1] = vUp.getY();
	matRet[2][1] = vUp.getZ();
	matRet[3][1] = cVector3::Dot(vUp*-1, vEye);

	matRet[0][2] = vLookAt.getX();
	matRet[1][2] = vLookAt.getY();
	matRet[2][2] = vLookAt.getZ();
	matRet[3][2] = cVector3::Dot(vLookAt*-1, vEye);

	
	return matRet;
}

cMatrix cMatrix::Projection(float fFovY, float fAspect, float fNearZ, float fFarZ) //각도 , 사이즈 , 1 ,1000
{
	/*
	 *sy = cot(fovy/2) = >1.0f / tanf(ffovY /2.0f)
	 *sx = sy/ aspect
	 *		sx		 0		 0				  0
	 *		0		sy		 0				  0
	 *		0		0		 fz/(fz-nz)		  1
	 *		0		0		 -fz*nz / (fz-nz) 0
	 */
	
	float sy =  1.0f / tanf(degreesToRadians(fFovY) / 2.0f);
	float sx = sy / fAspect;
	
	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
	}



	matRet[0][0] = sx;
	matRet[1][1] = sy;
	matRet[2][2] = fFarZ / (fFarZ - fNearZ);
	matRet[3][2] = -fFarZ * fNearZ / (fFarZ - fNearZ);
	matRet[2][3] = 1;

	return matRet;
}

cMatrix cMatrix::ViewPort(float x, float y, float w, float h, float minz, float maxz)
{
	/*
	 *	w/2.0f		 0			0		    0
	 *	0			 -h/2.0f	0			0
	 *	0			 0			maxz-minz   0
	 *	x+(w/2.0f)	 y+(h/2.0f)	minz		1
	 *
	 *	default -> maxz = 1 ,minz = 0
	 */

	cMatrix matRet(4);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			matRet[i][j] = 0;
		}
	}

	matRet[0][0] = w / 2.0f;
	matRet[1][1] = -h / 2.0f;
	matRet[2][2] = maxz - minz;
	
	matRet[3][0] = x+(w/2.0f);
	matRet[3][1] = y + (h/2.0f);
	matRet[3][2] = minz;
	matRet[3][3] = 1;

	return matRet;
}

