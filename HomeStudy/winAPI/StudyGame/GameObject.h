#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "stdafx.h"
#include <vector>
#include <stdlib.h>



//총알 객체안에 몬스터 정보를 넘겨준다.
//Rect객체안에는 몬스터 객체의 정보를 넘겨준다.

class GameManager
{
protected:
	
public:
	double str;
	double rect_hp;
	double monster_hp;
	//int Monnster;

	GameManager()
	{
		DataLoad();
	}
	void DataLoad()
	{

		string text;
		string temp;
		string num;
		ifstream inFile;


		inFile.open("gameSetting.txt");
		if (inFile.is_open())
		{
			while (getline(inFile, text))
			{
				cout << text << endl;
				int fin;
				fin = text.find(":");
				temp = "";
				num = "";
				for (int i = 0; i < fin; i++)
				{
					temp += text[i];
				}

				if (temp == "STR")
				{
					for (int i = fin + 1; i < text.length(); i++)
					{
						num += text[i];
					}

					str = stod(num);
				}
				else if (temp == "RECT_HP")
				{
					for (int i = fin + 1; i < text.length(); i++)
					{
						num += text[i];
					}

					rect_hp = stod(num);
				}
				else if (temp == "MONSTER_HP")
				{
					for (int i = fin + 1; i < text.length(); i++)
					{
						num += text[i];
					}
					monster_hp = stod(num);
				}
				
			}
		}
		inFile.close();
	}
};

static GameManager *manager = new GameManager;


class Monster;
class PlayerBullet;
class Rect;

class  GameAdmin
{


public:
	
	virtual void update()
	{

	}
	virtual void Draw(HDC hdc)
	{

	}

	virtual bool CollisionCheck()
	{
		return false;
	}

};

//static vector<Rect*> vecRect;
//static vector<PlayerBullet*> vecBullet;
//static vector<Monster*> vecMonster;


class PlayerRank
{

public:
	int Score;
	string name;
private:

};


