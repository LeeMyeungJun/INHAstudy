#include "stdafx.h"




Block::Block()
{
}


Block::~Block()
{
}

void Block::Init()
{
	memset(mTileData, '\0', sizeof(char));
	ZeroMemory(mPosition, sizeof(POINT) * 4);
	mType = 0;
	mColorRandTemp = 0;
}

void Block::CreateBlock()
{
	Init();

	mType = rand() % 7;
	mColorRandTemp = rand() % 7;

	//mColor = eTileInfo((rand() % COLOR_COUNT) + 101);
	 //'P',YELLOW = 'Y', GREEN = 'G', SKY = 'S', ORANGE = 'O', BLUE = 'B',RED = 'R', GUIDE = 199 };
	switch (mColorRandTemp)
	{
	case 0:
		mColor = 'P';
		break;
	case 1:
		mColor = 'Y';
		break;
	case 2:
		mColor = 'G';
		break;
	case 3:
		mColor = 'S';
		break;
	case 4:
		mColor = 'O';
		break;
	case 5:
		mColor = 'B';
		break;
	case 6:
		mColor = 'R';
		break;
	default:
		break;
	}

	switch (mType)
	{
	case 0:
		/*
		¡á¡á¡à
		¡à¡á¡á
		¡à¡à¡à	*/
		mTileData[0][0] = mColor; mPosition[0] = { 5,0 };
		mTileData[0][1] = mColor; mPosition[1] = { 6,0 };
		mTileData[1][1] = mColor; mPosition[2] = { 6,1 };
		mTileData[1][2] = mColor; mPosition[3] = { 7,1 };
		break;

	case 1:
		/*
		¡à¡á¡á
		¡á¡á¡à
		¡à¡à¡à	*/
		mTileData[0][1] = mColor; mPosition[0] = { 6,0 };
		mTileData[0][2] = mColor; mPosition[1] = { 7,0 };
		mTileData[1][0] = mColor; mPosition[2] = { 5,1 };
		mTileData[1][1] = mColor; mPosition[3] = { 6,1 };
		break;

	case 2:
		/*
		¡á¡á¡à
		¡à¡á¡à
		¡à¡á¡à	*/
		mTileData[0][0] = mColor; mPosition[0] = { 5,0 };
		mTileData[0][1] = mColor; mPosition[1] = { 6,0 };
		mTileData[1][1] = mColor; mPosition[2] = { 6,1 };
		mTileData[2][1] = mColor; mPosition[3] = { 6,2 };
		break;

	case 3:
		/*
		¡à¡á¡á
		¡à¡á¡à
		¡à¡á¡à	*/
		mTileData[0][1] = mColor; mPosition[0] = { 6,0 };
		mTileData[0][2] = mColor; mPosition[1] = { 7,0 };
		mTileData[1][1] = mColor; mPosition[2] = { 6,1 };
		mTileData[2][1] = mColor; mPosition[3] = { 6,2 };
		break;

	case 4:
		/*
		¡à¡á¡à
		¡á¡á¡á
		¡à¡à¡à	*/
		mTileData[0][1] = mColor; mPosition[0] = { 6,0 };
		mTileData[1][0] = mColor; mPosition[1] = { 5,1 };
		mTileData[1][1] = mColor; mPosition[2] = { 6,1 };
		mTileData[1][2] = mColor; mPosition[3] = { 7,1 };
		break;

	case 5:
		/*
		¡à¡à¡à¡à
		¡à¡á¡á¡à
		¡à¡á¡á¡à
		¡à¡à¡à¡à	*/
		mTileData[1][1] = mColor; mPosition[0] = { 6,1 };
		mTileData[1][2] = mColor; mPosition[1] = { 7,1 };
		mTileData[2][1] = mColor; mPosition[2] = { 6,2 };
		mTileData[2][2] = mColor; mPosition[3] = { 7,2 };
		break;

	case 6:
		/*
		¡à¡à¡à¡à
		¡á¡á¡á¡á
		¡à¡à¡à¡à
		¡à¡à¡à¡à	*/
		mTileData[1][0] = mColor; mPosition[0] = { 5,1 };
		mTileData[1][1] = mColor; mPosition[1] = { 6,1 };
		mTileData[1][2] = mColor; mPosition[2] = { 7,1 };
		mTileData[1][3] = mColor; mPosition[3] = { 8,1 };
		break;
	}
}

void Block::CopyBlock(Block& block)
{
	//eTileInfo tempTiles[4][4];
	//block.GetBlockData(tempTiles);
	//SetBlockData(tempTiles);
	//mType = block.GetBlockType();
	//mColor = block.GetBlockColor();
	//mPosition = block.GetPosition();
}


void Block::GetBlockData(char outData[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			outData[i][j] = mTileData[i][j];
		}
	}
}

void Block::SetBlockData(char data[4][4])
{
	//memcpy(mTileData, data, sizeof(eTileInfo) * 4 * 4);
}

int Block::GetBlockType()
{
	return mType;
}

void Block::SetBlockType(int type)
{
	mType = type;
}

char Block::GetBlockColor()
{
	return mColor;
}
//
//void Block::GetEachTilePosition(Point nextPosition, Point* outPoint)
//{
//	//int pointerIndex = 0;
//
//	//for (int y = 0; y < 4; y++)
//	//{
//	//	if (pointerIndex >= 4)
//	//		break;
//	//	for (int x = 0; x < 4; x++)
//	//	{
//	//		if (mTileData[y][x] != eTileInfo::EMPTY)
//	//		{
//	//			outPoint[pointerIndex].x = x;
//	//			outPoint[pointerIndex].y = y;
//	//			outPoint[pointerIndex] += nextPosition;
//	//			pointerIndex++;
//	//		}
//	//	}
//	//}
//}
//
//void Block::GetEachTileVecPosition(Point* outPoint)
//{
//	GetEachTilePosition(Point{ 0,0 }, outPoint);
//}
//
//void Block::SetEachTilePosition(Point inPosition[4])
//{
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	for (int j = 0; j < 4; j++)
//	//	{
//	//		mTileData[i][j] = eTileInfo::EMPTY;
//	//	}
//	//}
//
//	//for (int i = 0; i < 4; i++)
//	//{
//	//	mTileData[inPosition[i].y][inPosition[i].x] = mColor;
//	//}
//}