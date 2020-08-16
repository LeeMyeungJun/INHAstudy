// dijkstraAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



#define MAXLOAD 8

#define MX 999999

int dijkstra[MAXLOAD][MAXLOAD] =
{
	{ 0  ,2  ,MX ,MX ,MX ,3  ,MX  ,MX },
	{ 2  ,0  ,4  ,1  ,MX ,MX ,MX ,MX },
	{ MX ,4  ,0  ,MX ,3  ,MX ,MX ,MX },
	{ MX ,1  ,MX ,0  ,3  ,MX ,2  ,MX },
	{ MX ,MX ,3  ,3  ,0  ,MX ,MX ,4 },
	{ 3  ,MX ,MX ,MX ,MX ,0  ,6  ,MX },
	{ MX ,MX ,MX ,2  ,MX ,6  ,0  ,4 },
	{ MX ,MX ,MX ,4  ,MX ,MX ,4  ,0 }
};
int arrlength[MAXLOAD]; // �Ÿ��迭
int arrIndex[MAXLOAD]; //��� �迭
bool bFlag[MAXLOAD] = { false, }; //��ȴ����� �n

int startPoint = 0;
int endPoint = 0;
int temp = 0, i = 0, j = 0;

void SmallLength();
void Init();
void Sort();

int main()
{
	memset(arrlength, 0, sizeof(arrlength));
	memset(arrIndex, 0, sizeof(arrIndex));
	{
		for (i = 0; i < MAXLOAD; i++)
		{
			for (j = 0; j < MAXLOAD; j++)
			{
				cout << dijkstra[i][j]<<" ";
			}
			cout << endl;
		}

		//cin >> startPoint;
		//
		//for (i = 0; i < MAXLOAD; i++)
		//{
		//	arrlength[i] = dijkstra[startPoint - 1][i];
		//}


		//temp = 999;
		//for (i = 0; i < MAXLOAD; i++)
		//{
		//	if (temp > arrlength[i] && i != startPoint-1)
		//		temp = arrlength[i];
		//}
		//
		//for (i = 0; i < MAXLOAD; i++)
		//{
		//	if(arrlength[i] >temp +dijkstra[temp-1][i])
		//		arrlength[i] = temp + dijkstra[temp-1][i];
		//}

		//temp = 999;
		//for (i = 0; i < MAXLOAD; i++)
		//{
		//	if (temp > arrlength[i] && i != startPoint - 1)
		//		temp = arrlength[i];
		//}


		//for (i = 0; i < MAXLOAD; i++)
		//{
		//	if (arrlength[i] >temp + dijkstra[temp - 1][i])
		//		arrlength[i] = temp + dijkstra[temp - 1][i];
		//}
	}
	
	cout << "���� ���� , ������ ������� �Է������.";
	cin >> startPoint >> endPoint;
	for (i = 0; i < MAXLOAD; i++)
	{
		arrlength[i] = dijkstra[startPoint - 1][i];
	}


    return 0;
}

void SmallLength()
{
	temp = MX;
	for (i = 0; i < MAXLOAD; i++)
	{
		if (temp > arrlength[i] && i != startPoint - 1 && !bFlag[i])
		{
			temp = arrlength[i];
			arrIndex[MAXLOAD] = i;
		}
			

	}
	
}

void Init()
{

}

void Sort()
{
	
	
}