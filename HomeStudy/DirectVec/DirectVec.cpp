// DirectVec.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cVector3.h"
#include "cMatrix.h"
#include <iostream>
#include <time.h>
using namespace std;


ostream& operator <<(ostream& outputStream, const cVector3& A) {
	cout << "(" << A.getX() << ", " << A.getY() << ", " << A.getZ() << ")";

	return outputStream;
}


int main()
{
	/*
	cVector3 vec1(1 ,0 ,0);
	cVector3 vec2(0 ,1 ,0);
	cout << "vec1 == vec2 : " << (vec1 == vec2) << endl;
	cout << "vec1 != vec2 : " << (vec1 != vec2) << endl;

	cVector3 vec3 = (vec1 + vec2);
	cout << "vec3 = "<< vec3 << endl;

	cVector3 vec4 = (vec1 - vec2);
	cout << "vec4 = "<< vec4 << endl;

	cVector3 vecCross = cVector3::Cross(vec1, vec2);
	cout << "vecCross = " << vecCross << endl;

	cVector3 vecCross2 = cVector3::Cross(vec2, vec1);
	cout << "vecCross2 = " << vecCross2 << endl;

	cVector3 u(-1, 3, 2);
	cVector3 v(3, -4, 1);
		
	//cout << u + v << endl;
	//cout << u - v << endl;
	//cout << (u * 3) + (v * 2) << endl;
	//cout << (u * -2) + v << endl;
	//cout << u.Normlize();

	//두벡터의 사이각을 구하라 .

	//cout << cVector3::Angele(v, u) << endl;
	*/
	/*
	//어떤 좌표계를 기준으로 점 A = (0,0,0) B = (0,1,3) C = (5,1,0)
	//이세점이 하나의 삼각형을 정의한다고 하자 . 
	//이 삼각형에 수직인 벡터를 구하라 

	cVector3 A(0, 0, 0);
	cVector3 B(0, 1, 3);
	cVector3 C(5, 1, 0);

	cVector3 temp = (B - A) - (C - A);
	cout << temp;
	*/
	srand(time(NULL));
	cMatrix test(2);
	cMatrix test2(2);
	//if (test == test2)
	//{
	//	cout << "같다" << endl;
	//}

	test.Print();
	cout << endl;
	test2.Print();
	cout << endl;
	cMatrix test3 = test*test2;
	test3.Print();
	

    return 0;
}

