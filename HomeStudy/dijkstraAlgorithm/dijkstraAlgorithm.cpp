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


void dikstraFun(int, int);

int main()
{
	int startPoint = 0;
	int endPoint = 0;

	cout << "출발노드  , 목적 노드  ";
	cin >> startPoint >> endPoint;

	dikstraFun(startPoint-1, endPoint-1);

    return 0;
}

void dikstraFun(int _start, int _end)
{
	int smallLength[MAXLOAD] = {0,};
	int pathroad[MAXLOAD] = { 0, };
	vector<int> path;
	int lengthSum = 0;
	bool bFlag[MAXLOAD] = { false, };
	int cnt = 0;
	int start = 0;
	int end = _end;
	int small = 0;
	int roadCnt = 0;
	int temp = _start;
	memset(smallLength, MX, sizeof(smallLength));
	smallLength[_start] = 0;
	//path.push_back(_start+1);

	while (cnt != MAXLOAD)
	{
		cnt = 0;

		start = temp;
		temp = MX;
		pathroad[roadCnt] = start;
		bFlag[start] = true;
		
		for (int i = 0; i < MAXLOAD; i++)
		{
			if (bFlag[i])
				cnt += 1;
		}

		roadCnt++;
	}

}

