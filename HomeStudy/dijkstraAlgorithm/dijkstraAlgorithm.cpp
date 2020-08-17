// dijkstraAlgorithm.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

//#define INF ((size_t) - 1) 
//#define MAX_NODE 10
//
//using namespace std;
//
//size_t nodeNum = 0;
//unsigned int map[MAX_NODE][MAX_NODE];
//
//void InitMap();
//void ReadMapFromFile();
//void ReadMapBasic();
//void PrintMap();
//size_t InputStartNode();
//size_t InputEndNode();
//void DijkstraPathFiding(size_t & startNode, size_t & endNode);
//void DijkstraInit(bool * &visitedNode, size_t * &distanceFromStart, size_t * &shortestNode, const size_t & startNode);
//
//int main()
//{
//	InitMap();
//	//ReadMapFromFile();
//	ReadMapBasic();
//	PrintMap();
//	size_t startNode = InputStartNode();
//	size_t endNode = InputEndNode();
//	DijkstraPathFiding(startNode, endNode);
//	return 0;
//}
//
//void InitMap()
//{
//	for (size_t i = 0; i < MAX_NODE; i++)
//	{
//		for (size_t j = 0; j < MAX_NODE; j++)
//		{
//			map[i][j] = 0;
//		}
//	}
//}
//
//void ReadMapFromFile()
//{
//	char buffer[512];
//	FILE * mapFile = fopen("map.txt", "r");
//	fgets(buffer, 512, mapFile);
//	nodeNum = atoi(buffer);
//	for (size_t i = 0; i < nodeNum; i++)
//	{
//		fgets(buffer, 512, mapFile);
//		char * token = strtok(buffer, "\t");
//		for (size_t j = 0; j < nodeNum; j++)
//		{
//			size_t cell = atoi(token);
//			token = strtok(NULL, "\t");
//			map[i][j] = cell;
//		}
//	}
//}
//
//void ReadMapBasic()
//{
//	nodeNum = 8;
//	int aEdgeCost[8][8] =
//	{
//		{ 0,2,INF,INF,INF,3,INF,INF }, //1
//		{ 2,0,4,1,INF,INF,INF,INF }, //2
//		{ INF,4,0,INF,3,INF,INF,INF }, //3
//		{ INF,1,INF,0,3,INF,2,INF }, //4
//		{ INF,INF,3,3,0,INF,INF,4 }, //5
//		{ 3,INF,INF,INF,INF,0,6,INF }, //6
//		{ INF,INF,INF,2,INF,6,0,4 }, //7
//		{ INF,INF,INF,INF,4,INF,4,0 } // 8
//	};
//	for (size_t i = 0; i < nodeNum; i++)
//	{
//		for (size_t j = 0; j < nodeNum; j++)
//		{
//			map[i][j] = aEdgeCost[i][j];
//		}
//	}
//}
//
//void PrintMap()
//{
//	for (size_t i = 0; i < nodeNum; i++)
//	{
//		for (size_t j = 0; j < nodeNum; j++)
//		{
//			if (map[i][j] == INF)
//				printf("INF\t");
//			else
//				printf("%3d\t", map[i][j]);
//		}
//		cout << endl;
//	}
//}
//
//size_t InputStartNode()
//{
//	size_t startNode = 0;
//	cout << "Input Start Node : ";
//	cin >> startNode;
//	return startNode - 1;
//}
//
//size_t InputEndNode()
//{
//	size_t endNode = 0;
//	cout << "Input End Node : ";
//	cin >> endNode;
//	return endNode - 1;
//}
//
//void DijkstraPathFiding(size_t & startNode, size_t & endNode)
//{
//	bool * visitedNode = NULL;
//	size_t * distanceFromStart = NULL;
//	size_t * shortestNode = NULL;
//	size_t currentNode = startNode;
//
//	DijkstraInit(visitedNode, distanceFromStart, shortestNode, startNode);
//
//	while (visitedNode[endNode] == false && currentNode != nodeNum)
//	{
//		for (size_t i = 0; i < nodeNum; i++)
//		{
//			if (visitedNode[i] == false)
//			{
//				if (map[currentNode][i] == INF)
//					continue;
//				size_t pathThoughcurNode = distanceFromStart[currentNode] + map[currentNode][i];
//				if (pathThoughcurNode < distanceFromStart[i])
//				{
//					distanceFromStart[i] = pathThoughcurNode;
//					shortestNode[i] = currentNode;
//				}
//			}
//		}
//		visitedNode[currentNode] = true;
//		currentNode = nodeNum;
//		size_t minDis = distanceFromStart[endNode];
//		for (size_t i = 0; i < nodeNum; i++)
//		{
//			if (visitedNode[i] == false && distanceFromStart[i] < minDis)
//			{
//				currentNode = i;
//				minDis = distanceFromStart[i];
//			}
//		}
//	}
//
//	if (distanceFromStart[endNode] == INF)
//		cout << "There is no way" << endl;
//	else
//	{
//		cout << "Distance : " << distanceFromStart[endNode] << endl;
//		cout << "PATH : ";
//		size_t searchNode = endNode;
//		cout << endNode + 1;
//		while (searchNode != startNode)
//		{
//			cout << " - " << shortestNode[searchNode] + 1;
//			searchNode = shortestNode[searchNode];
//		}
//		cout << endl;
//	}
//	delete[] shortestNode;
//	delete[] visitedNode;
//	delete[] distanceFromStart;
//}
//
//void DijkstraInit(bool * &visitedNode, size_t * &distanceFromStart, size_t * &shortestNode, const size_t & startNode)
//{
//	visitedNode = new bool[nodeNum];
//	shortestNode = new size_t[nodeNum];
//	distanceFromStart = new size_t[nodeNum];
//	for (size_t i = 0; i < nodeNum; i++)
//	{
//		visitedNode[i] = false;
//		shortestNode[i] = INF;
//		if (i == startNode)
//			distanceFromStart[i] = 0;
//		else
//			distanceFromStart[i] = INF;
//	}
//}

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
	{ MX ,MX ,MX ,MX ,4 ,MX ,4  ,0 }
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
	int path[MAXLOAD] = { 0, };
	//vector<int>path;
	int lengthSum = 0;
	bool bFlag[MAXLOAD] = { false, };

	int cnt = 0;
	int start = _start;
	int end = _end;
	int small = 0;

	int temp = MX;
	int IndexTemp = 0;

	memset(bFlag, false, sizeof(bFlag));
	memset(smallLength, MX, sizeof(smallLength));
	smallLength[_start] = 0;

//	path.push_back(start + 1);
//	patch[start] = start + 1;

	while (1)
	{
		cnt = 0;
		temp = MX;
	
		bFlag[start] = true;
		IndexTemp = start;
		for (int i = 0; i < MAXLOAD; i++)
		{
			if (bFlag[i])
				continue;

			if (smallLength[i] > dijkstra[start][i] + small)
			{
				smallLength[i] = dijkstra[start][i] + small;

			}
		}

		for (int i = 0; i < MAXLOAD; i++)
		{
			if (bFlag[i])
				continue;

			if (temp > smallLength[i])
			{
				temp = smallLength[i];
				small = smallLength[i];
				start = i;
				
			}
		}

		path[start] = IndexTemp;

		

		for (int i = 0; i < MAXLOAD; i++)
		{
			if (bFlag[i])
				cnt += 1;
		}
		if (cnt == MAXLOAD)
			break;
	
		//path[start] = start;
		//path.push_back(start + 1);
		
	}

	start = _start;
	end = _end;
	//cout << start +1 <<" - ";
	//while (true)
	//{
	//	if (path[start] == end + 1)
	//	{
	//		cout << path[start] ;
	//		break;
	//	}
	//		

	//	cout << path[start] << " - ";
	//	start = path[start]-1;
	//	
	//}


	//while (true)
	//{
	//	if (path[start] == _end+1)
	//	{
	//		cout << path[start];
	//		break;
	//	}
	//	cout << path[start] << " - ";
	//	start = path[start];

	//}




}

