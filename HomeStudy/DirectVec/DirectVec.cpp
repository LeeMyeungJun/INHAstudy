// DirectVec.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cVector3.h"
#include <iostream>

using namespace std;


ostream& operator <<(ostream& outputStream, const cVector3& A) {
	cout << "(" << A.getX() << ", " << A.getY() << ", " << A.getZ() << ")";

	return outputStream;
}


int main()
{
	cVector3 uVector(1.0f,0.0f,1.0f);
	cVector3 vVector(0.0f,1.0f,0.0f);


	//if (uVector == vVector)
	//{
	//	cout << "���� �ΰ��� ����"<<endl;
	//}


	//if (uVector != vVector)
	//{
	//	cout << "���� �ΰ��� �ٸ���" << endl;
	//}


	//float fTemp;

	////uVector.setVector(4,10,3);
	////vVector.setVector(2,4,1);
	////51 ����


	//fTemp = cVector3::Dot(uVector, vVector);

	//cout << fTemp << endl;


	uVector.setVector(5, 1, 4);
	vVector.setVector(-1,0,2);

	cVector3 Vectortemp;

	Vectortemp = cVector3::Cross(uVector, vVector);

	cout << Vectortemp << endl;

    return 0;
}

