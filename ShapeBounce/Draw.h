#pragma once
#include "stdafx.h"
#include <tchar.h>
#include <math.h>
#include <stdlib.h>


double getRadian(int num){return num*(3.1415926535897 / 180);}

double CrossX(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

	double a, b, c, d, e, f;
	double x, y;

	a = y1 - y2;
	b = -(x1 - x2);
	c = y3 - y4;
	d = -(x3 - x4);
	e = a*x1 + b*y1;
	f = c*x3 + d*y3;

	x = ((e*d - b*f)) / ((a*d - b*c));
	y = ((a*f - e*c)) / ((a	*d - b*c));

	if (fabs(x) != INFINITY && fabs(y) != INFINITY)
		return x;
	else
		return -1;

	return -1;
}

double CrossY(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

	double a, b, c, d, e, f;
	double x, y;

	a = y1 - y2;
	b = -(x1 - x2);
	c = y3 - y4;
	d = -(x3 - x4);
	e = a*x1 + b*y1;
	f = c*x3 + d*y3;

	x = ((e*d - b*f)) / ((a*d - b*c));
	y = ((a*f - e*c)) / ((a	*d - b*c));

	if (fabs(x) != INFINITY && fabs(y) != INFINITY)
		return y;
	else
		return -1;

	return -1;
}

void DrawGrid(HDC hdc, int xStart, int yStart, int xEnd, int yEnd, int lineThickness)
{
	//hdc 100 100 500 500 50
	int iCount = xEnd - xStart;

	//가운데 세로줄
	for (int i = 0; i <= iCount / lineThickness; i++)
	{
		MoveToEx(hdc, xStart + lineThickness*i, yStart, NULL);
		LineTo(hdc, xStart + lineThickness*i, yEnd);
	}

	//가운데 가로줄
	for (int i = 0; i <= iCount / lineThickness; i++)
	{
		MoveToEx(hdc, xStart, yStart + lineThickness*i, NULL);
		LineTo(hdc, xEnd, yStart + lineThickness*i);
	}

}

void DrawCircle(HDC hdc, int centerX, int centerY, int r)
{
	Ellipse(hdc, centerX - r, centerY - r, centerX + r, centerY + r);
}

void DrawStar(HDC hdc, double x, double y, double r)
{
	double PointX[10] = { x,0,x + (r*cos(getRadian(18))),0,x + (r * sin(getRadian(36))),0,x - (r*sin(getRadian(36))),0,x - (r*cos(getRadian(18))),0 };
	double PointY[10] = { y - r,0,y - (r*sin(getRadian(18))),0,y + (r*cos(getRadian(36))),0,y + (r*cos(getRadian(36))) ,0,y - (r*sin(getRadian(18))),0 };

	PointX[1] = CrossX(PointX[0], PointY[0], PointX[4], PointY[4], PointX[8], PointY[8], PointX[2], PointY[2]);
	PointX[3] = CrossX(PointX[0], PointY[0], PointX[4], PointY[4], PointX[6], PointY[6], PointX[2], PointY[2]);
	PointX[5] = CrossX(PointX[6], PointY[6], PointX[2], PointY[2], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointX[7] = CrossX(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointX[9] = CrossX(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[2], PointY[2]);


	PointY[1] = CrossY(PointX[0], PointY[0], PointX[4], PointY[4], PointX[8], PointY[8], PointX[2], PointY[2]);
	PointY[3] = CrossY(PointX[0], PointY[0], PointX[4], PointY[4], PointX[6], PointY[6], PointX[2], PointY[2]);
	PointY[5] = CrossY(PointX[6], PointY[6], PointX[2], PointY[2], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointY[7] = CrossY(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointY[9] = CrossY(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[2], PointY[2]);

	POINT point[10] = {};

	for (int i = 0; i < 10; i++)
	{
		point[i] = { (int)PointX[i],(int)PointY[i] };
	}

	Polygon(hdc, point, 10);
}
