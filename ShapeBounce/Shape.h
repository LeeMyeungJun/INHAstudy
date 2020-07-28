#pragma once

#include <tchar.h>
#include <math.h>
#include <stdlib.h>
#include <vector>
#include <ctime>

using namespace std;
#define PI 3.141592


class Shape
{
protected:

	bool Collision(double OtherObjectX, double OtherObjectY, double size, double OtherDirection)
	{
		double dLength = (double)sqrt(pow(this->PositionX - OtherObjectX, 2) + pow(PositionY - OtherObjectY, 2));

		if (size + this->dSize > dLength) //충돌
		{
			return true;
		}

		return false;
	}

	double getRadian(int num)
	{return num*(3.1415926535897 / 180);}
	

public:
	enum TYPE { CIRCLE, RECT, STAR };
	double PositionX, PositionY,dSize;
	TYPE Ttype;
	double dSpeed;
	int Direction;
	int degree = 10;
	Shape(double x, double y, double r, double speed , TYPE type):PositionX(x),PositionY(y), dSize(r),dSpeed(speed), Ttype(type)
	{
		srand((unsigned int)time(NULL));
		Direction = 0;
		Direction = rand() % 4 + 1;
	}

	virtual void update(int,int, vector<Shape*> )
	{
	}

	virtual void Draw(HDC hdc)
	{
	}
};

class Circle : public Shape
{

public:

	void Draw(HDC hdc)
	{
		Ellipse(hdc, PositionX - dSize, PositionY - dSize, PositionX + dSize, PositionY + dSize);
	}

	Circle(double x,double y,double r,double speed):Shape(x,y,r,speed,CIRCLE)
	{
	}
	void update(int RectX, int RectY, vector<Shape*> vecShape)
	{
		//위 아래 양옆 벽에 부딛혔을경우.
		if (
			PositionX - dSize <= 0 ||
			PositionX + dSize >= RectX ||
			PositionY <= 0 ||
			PositionY >= RectY
			)
		{

			Direction *= -1;
		}
		/*Move*/
		{

			if (Direction == 1)
			{
				PositionX -= 5;
				PositionY -= 5;

			}
			else if (Direction == 2)
			{
				PositionY -= 5;
			}
			else if (Direction == 3)
			{
				PositionY -= 5;
				PositionX += 5;
			}
			else if (Direction == 4)
			{
				PositionX += 5;
			}
			else if (Direction == -1)
			{
				PositionX += 5;
				PositionY += 5;
			}
			else if (Direction == -2)
			{
				PositionY += 5;
			}
			else if (Direction == -3)
			{
				PositionX -= 5;
				PositionY += 5;
			}
			else if (Direction == -4)
			{
				PositionX -= 5;
			}

		}

		//객체끼리의 충돌
		bool bFlag = false;
		for (Shape *i : vecShape)
		{
			bFlag = Collision(i->PositionX, i->PositionY, i->dSize, i->Direction);

			if (bFlag)
			{
				swap(this->Direction, i->Direction);
			}
			bFlag = false;
		}
	}
	
};

class Rect : public Shape
{


public:
	POINT pointrt[4];
	
	virtual void Draw(HDC hdc)
	{
		/*일반처리*/
		//pointrt[0].x = PositionX - dSize; pointrt[0].y = PositionY - dSize;
		//pointrt[1].x = PositionX + dSize; pointrt[1].y = PositionY - dSize;
		//pointrt[2].x = PositionX + dSize; pointrt[2].y = PositionY + dSize;
		//pointrt[3].x = PositionX - dSize; pointrt[3].y = PositionY + dSize;

		
		pointrt[0].x = (PositionX)+-cos(getRadian(degree))* dSize; pointrt[0].y =  (PositionY)+sin(getRadian(degree)) * dSize;
		pointrt[1].x = (PositionX)+ sin(getRadian(degree))* dSize; pointrt[1].y = (PositionY)+cos(getRadian(degree))  * dSize;
		pointrt[2].x = (PositionX)+ cos(getRadian(degree))* dSize; pointrt[2].y = (PositionY)+-sin(getRadian(degree)) * dSize;
		pointrt[3].x = (PositionX)+-sin(getRadian(degree))* dSize; pointrt[3].y = (PositionY)+ -cos(getRadian(degree))* dSize;

		Polygon(hdc, pointrt, 4);
		degree += 10;

		if (degree >= 360)
		{
			degree = 10;
		}
	}

	Rect(double x, double y, double r, double speed) :Shape(x, y, r, speed, RECT)
	{
		
	}
	void update(int RectX,int RectY , vector<Shape*> vecShape)
	{
		 //위 아래 양옆 벽에 부딛혔을경우.
			if (
				pointrt[0].x <= 0 ||
				pointrt[1].x >= RectX ||
				pointrt[2].x >= RectX ||
				pointrt[3].x <= 0 ||

				pointrt[0].y <= 0 ||
				pointrt[1].y <= 0 ||
				pointrt[2].y >= RectY ||
				pointrt[3].y >= RectY
				)
			{

				Direction *= -1;
			}
			/*Move*/
			{

				if (Direction == 1)
				{
					PositionX -= 5;
					PositionY -= 5;

				}
				else if (Direction == 2)
				{
					PositionY -= 5;
				}
				else if (Direction == 3)
				{
					PositionY -= 5;
					PositionX += 5;
				}
				else if (Direction == 4)
				{
					PositionX += 5;
				}
				else if (Direction == -1)
				{
					PositionX += 5;
					PositionY += 5;
				}
				else if (Direction == -2)
				{
					PositionY += 5;
				}
				else if (Direction == -3)
				{
					PositionX -= 5;
					PositionY += 5;
				}
				else if (Direction == -4)
				{
					PositionX -= 5;
				}

			}
	
		//객체끼리의 충돌
			bool bFlag = false;
			for (Shape *i : vecShape)
			{
				bFlag = Collision(i->PositionX, i->PositionY, i->dSize ,i->Direction);

				if (bFlag)
				{
					swap(this->Direction, i->Direction);
				}
				bFlag = false;
			}
	}
};

class Star : public Shape
{

private:


public:


	POINT starPoint[10];

	Star(double x, double y, double r, double speed) :Shape(x, y, r, speed, STAR)
	{
	}

	//for (CShape *cRect : cShapes)
	//{
	//	for (int i = 0; i < cRect->vertexNum; i++)      //도형 회전
	//	{
	//		float xTmp = cRect->points[i].x - cRect->x;
	//		float yTmp = cRect->points[i].y - cRect->y;
	//		cRect->points[i].x = cos(20 * PI / 180) * xTmp - sin(20 * PI / 180) * yTmp + cRect->x;
	//		cRect->points[i].y = sin(20 * PI / 180) * xTmp + cos(20 * PI / 180) * yTmp + cRect->y;
	//	}
	//}

	virtual void Draw(HDC hdc)
	{
		int x = PositionX;
		int y = PositionY;
		int r = dSize;
		//MoveToEx(hdc, x, y, NULL); //중점을 옮겨주는 함수다.

		for (int i = 0; i < 9; i += 2)
		{
			starPoint[i].x = x + (r * sin(72 * (i / 2) * PI / 180));
			starPoint[i].y = y - (r * cos(72 * (i / 2) * PI / 180));
		}

		float a = starPoint[0].y - starPoint[4].y;
		float b = -(starPoint[0].x - starPoint[4].x);
		float c = starPoint[2].y - starPoint[8].y;
		float d = -(starPoint[2].x - starPoint[8].x);
		float e = a * starPoint[0].x + b * starPoint[0].y;
		float f = c * starPoint[2].x + d * starPoint[2].y;

		starPoint[1].x = (e*d - b*f) / (a*d - b*c);
		starPoint[1].y = (a*f - e*c) / (a*d - b*c);

		double r2 = pow(pow(x - starPoint[1].x, 2) + pow(y - starPoint[1].y, 2), 0.5);

		for (int i = 3; i < 10; i += 2)
		{
			starPoint[i].x = x + (r2 * sin((72 * (i / 2) + 36) * PI / 180));
			starPoint[i].y = y - (r2 * cos((72 * (i / 2) + 36) * PI / 180));
		}



			for (int i = 0; i < 10; i++)      //도형 회전
			{
				/*float xTmp = cRect->points[i].x - cRect->x;
				float yTmp = cRect->points[i].y - cRect->y;*/
				/*double xTmp = (starPoint[i].x - PositionX);
				double yTmp = (starPoint[i].y - PositionY);
				starPoint[i].x =  cos(degree * PI / 180) * xTmp - sin(degree * PI / 180) * yTmp + PositionX;
				starPoint[i].y = sin(degree * PI / 180) *  xTmp + cos(degree * PI / 180) * yTmp + PositionY;*/

				starPoint[i].x = cos(degree * PI / 180) * (starPoint[i].x - PositionX) - sin(degree * PI / 180) * (starPoint[i].y - PositionY) + PositionX;
				starPoint[i].y = sin(degree * PI / 180) * (starPoint[i].x - PositionX) + cos(degree * PI / 180) *(starPoint[i].y - PositionY) + PositionY;
			}


			degree += 10;

			if (degree >= 360)
			{
				degree = 10;
			}
		Polygon(hdc, starPoint, 10);
	}

	void update(int RectX, int RectY, vector<Shape*> vecShape)
	{
		//위 아래 양옆 벽에 부딛혔을경우.
		if (
			starPoint[0].x <= 0 ||
			starPoint[2].x >= RectX ||
			starPoint[4].x >= RectX ||
			starPoint[6].x <= 0 ||
			starPoint[8].x <= 0 ||

			starPoint[0].y <= 0 ||
			starPoint[4].y >= RectY ||
			starPoint[6].y >= RectY
			)
		{

			Direction *= -1;
		}
	
		{

			if (Direction == 1)
			{
				PositionX -= 5;
				PositionY -= 5;

			}
			else if (Direction == 2)
			{
				PositionY -= 5;
			}
			else if (Direction == 3)
			{
				PositionY -= 5;
				PositionX += 5;
			}
			else if (Direction == 4)
			{
				PositionX += 5;
			}
			else if (Direction == -1)
			{
				PositionX += 5;
				PositionY += 5;
			}
			else if (Direction == -2)
			{
				PositionY += 5;
			}
			else if (Direction == -3)
			{
				PositionX -= 5;
				PositionY += 5;
			}
			else if (Direction == -4)
			{
				PositionX -= 5;
			}

		}

		//객체끼리의 충돌
		bool bFlag = false;
		for (Shape *i : vecShape)
		{
			bFlag = Collision(i->PositionX, i->PositionY, i->dSize, i->Direction);

			if (bFlag)
			{
				swap(this->Direction, i->Direction);
			}
			bFlag = false;
		}
	}
	

};
