#pragma once
#define COLOR_COUNT 6
//
//struct Point
//{
//	int x;
//	int y;
//
//	Point operator += (Point another)
//	{
//		x += another.x;
//		y += another.y;
//		return *this;
//	}
//
//	Point operator + (Point another)
//	{
//		return Point{ x + another.x,y += another.y };
//	}
//};
//


class Block
{

private:
	char mTileData[4][4];// 블록정보 저장
	
	char mColor; //컬러정보
	int mType;  //블록의 타입
	int mColorRandTemp;//Rand돌리는용도.

public:
	void Init();
	void CreateBlock();
	void CopyBlock(Block& block);

	POINT mPosition[4];//위치정보
	//void GetEachTilePosition(Point nextPosition, Point* outPoint);	// 맵상의 타일 각각의 위치를 구해준다.
	//void GetEachTileVecPosition(Point* outPoint);	// 타일 각각의 상대위치를 구해준다.
	//void SetEachTilePosition(Point inPosition[4]);


	void GetBlockData(char outData[4][4]);
	void SetBlockData(char data[4][4]);

	int GetBlockType();
	void SetBlockType(int type);

	char GetBlockColor();



public:
	Block();
	~Block();

};

