// test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
//#include<bits/stdc++.h>

using namespace std;

class Box
{
private:
	int length;
	int breadth;
	int height;
public:
	Box() :length(0), breadth(0), height(0)
	{}
	Box(int l, int b, int h) :length(l), breadth(b), height(h)
	{

	}
	Box(Box& b) :length(b.length), breadth(b.breadth), height(b.height)
	{

	}
	int getLength() { return this->length; }; // Return box's length
	int getBreadth() { return this->breadth; }; // Return box's breadth
	int getHeight() { return this->height; };  //Return box's height
	long long CalculateVolume() {
		
		return (long long)(this->length) * (this->height) * (this->breadth);
	
	}; // Return the volume of the box

																   //Overload operator < as specified
	bool operator<(Box& b)
	{
		if ((this->length) < b.length)
			return true;
		else if ((this->breadth) < b.breadth && (this->length) == b.length)
			return true;
		else if ((this->height) <= b.height && (this->length) == b.length)
			return true;

		return false;
	}

	//Overload operator << as specified
	friend ostream& operator<<(ostream& out, Box& B)
	{
		out << B.length << " " << B.breadth << " " << B.height;
		return out;
	}


};


void check2()
{
	int n;
	cin >> n;
	Box temp;
	for (int i = 0; i<n; i++)
	{
		int type;
		cin >> type;
		if (type == 1)
		{
			cout << temp << endl;
		}
		if (type == 2)
		{
			int l, b, h;
			cin >> l >> b >> h;
			Box NewBox(l, b, h);
			temp = NewBox;
			cout << temp << endl;
		}
		if (type == 3)
		{
			int l, b, h;
			cin >> l >> b >> h;
			Box NewBox(l, b, h);
			if (NewBox<temp)
			{
				cout << "Lesser\n";
			}
			else
			{
				cout << "Greater\n";
			}
		}
		if (type == 4)
		{
			cout << temp.CalculateVolume() << endl;
		}
		if (type == 5)
		{
			Box NewBox(temp);
			cout << NewBox << endl;
		}

	}
}

int main()
{
	check2();
}