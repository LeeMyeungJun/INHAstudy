#pragma once
#include "stdafx.h"
#include "PlayerBullet.h"
#include "GameObject.h"
#include "Monster.h"



class Monster;
class Rect;

class PlayerBullet :public GameAdmin
{
private:

	/*
	void DrawBullet(HDC hdc, int i)
	{
	HPEN hpen, oldpen;
	HBRUSH hBrush, oldBursh;

	hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
	oldpen = (HPEN)SelectObject(hdc, hpen);
	hBrush = CreateSolidBrush(RGB(0, 0, 0));
	oldBursh = (HBRUSH)SelectObject(hdc, hBrush);

	Ellipse(hdc, 305 + (100 * i), 10, 345 + (100 * i), 90);

	SelectObject(hdc, oldBursh);
	DeleteObject(hBrush);

	SelectObject(hdc, oldpen);
	DeleteObject(hpen);
	}
	*/

	void DrawShootBullet(HDC hdc, double move, int degree)
	{
		double CenterX = 400;
		double CenterY = 850;


		point[0] = { 390,640 };
		point[1] = { 410,640 };
		point[2] = { 410,700 };
		point[3] = { 390,700 };

		for (int i = 0; i < 4; i++)
		{
			double xTmp = (point[i].x - CenterX);
			double yTmp = (point[i].y - CenterY);
			point[i].x = cos(degree * PI / 180) * xTmp - sin(degree * PI / 180) * yTmp + CenterX;
			point[i].y = sin(degree * PI / 180) *  xTmp + cos(degree * PI / 180) * yTmp + CenterY;

		}



		double x2 = (point[0].x + point[1].x) / 2;
		double y2 = (point[0].y + point[1].y) / 2;

		double m = (y2 - CenterY) / (x2 - CenterX);

		//y - point
		for (int i = 0; i < 4; i++)
		{
			point[i].y -= move;
			point[i].x -= move / m;
		}


		rcBullet.top = point[0].y;
		rcBullet.left = point[0].x;
		rcBullet.right = point[2].x;
		rcBullet.bottom = point[2].y;

		if (point[0].x <= 0 || point[0].y <= 100 || point[1].y <= 100 || point[1].x >= 800)
		{
			bulletCheck = 0;
			moveBullet = 0;
			rcBullet.top    = 0;
			rcBullet.left   = 0;
			rcBullet.right  = 0;
			rcBullet.bottom = 0;

			point[0] = { 0,0 };
			point[1] = { 0,0 };
			point[2] = { 0,0 };
			point[3] = { 0,0 };

		}


 		Polygon(hdc, point, 4);
	}
	bool CollisionRect(RECT rectBullet, RECT rectMonster)
	{
		bool bVertical = false;
		bool bHorizontal = false;

		if (rectBullet.left <rectMonster.right && rectBullet.right > rectMonster.left)
		{
			bHorizontal = true;
		}

		if (rectBullet.top < rectMonster.bottom && rectBullet.bottom > rectMonster.top)
		{
			bVertical = true;
		}

		if (bVertical && bHorizontal)
		{
			rectBullet.left = 0;
			rectBullet.right = 0;
			rectBullet.top = 0;
			rectBullet.bottom = 0;
			point[0] = { 0,0 };
			point[1] = { 0,0 };
			point[2] = { 0,0 };
			point[3] = { 0,0 };

			return true;
		}
		return false;
	}

public:
	int iBullet_id;
	double str;
	double moveBullet;
	bool bulletCheck;
	int bulletDegree;
	POINT point[4];
	RECT rcBullet;


	void setDegree(int degree) { bulletDegree = degree; }
	void setBulletFlag() { bulletCheck = 1; }
	int getFlag() { return bulletCheck; }

	PlayerBullet(int i) :iBullet_id(i), moveBullet(0), bulletCheck(0)
	{
		str = manager->str;
	}

	virtual void update(vector<Monster*> monster)
	{

		for (Monster *i : monster)
		{
			if (i->monster_Flag)
			{

				if (CollisionRect(rcBullet, (i->rcMonster)))
				{
					bulletCheck = 0;
					moveBullet = 0;
					i->setMonster_false_Flag();


					
				}
			}
		}
	}

	virtual void Draw(HDC hdc)
	{
		//DrawBullet(hdc, iBullet_id);
		if (bulletCheck == 1)
		{
			moveBullet += 10;
			DrawShootBullet(hdc, moveBullet, bulletDegree);
		}
	}

};