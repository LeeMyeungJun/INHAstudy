// 0710study.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>
using namespace std;

class Shape
{
protected:
	int x, y;


public:
	void setOrigin(int x, int y)
	{
		this -> x = x;
		this -> y = y;
	}
	virtual void draw()
	{
		cout << "Shape Draw" << endl;
	}



};


class Rectangle :public Shape
{

private:
	int width, height;

public:
	void setWidth(int w)
	{
		width = w;
	}
	void setHeight(int h)
	{
		height = h;
	}

	void draw()
	{
		cout << "Rectangle Draw" << endl;
	}
};


class Circle :public Shape
{
private:
	int radius;
public:
	void setRadius(int r)
	{
		radius = r;
	}

	void draw()
	{
		cout << "Cirlce Draw" << endl;
	}

};



int main()
{
	//SportCar sc;
	//cout << "마력: " << sc.getHP();
	//Car sc2;
	//cout << "마력 :" << sc2.getHP();

	//Car *pd = new SportCar();
	//cout<<pd->getHP();
	//cout<<((SportCar*)pd)->getPH();
	//SportCar *pb = (SportCar*)pd;
	//cout<<pb->getPH();

	//Car *pd = new Car();
	//SportCar *pd = new Car();
	//cout<<pd->getPH();
	//cout << ((SportCar*)pd)->getHP();

	Shape *ps = new Rectangle();
	ps->draw();
	delete ps;

	Shape *ps1 = new Circle();
	ps1->draw();
	delete ps1;


    return 0;
}

