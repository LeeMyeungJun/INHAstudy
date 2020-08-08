#pragma once

class Monster
{
private :
	enum DIRECTION
	{
		DIR_LT = 0,
		DIR_T,
		DIR_RT,
		DIR_L,
		DIR_R,
		DIR_LB,
		DIR_B,
		DIR_RB = 7
	};
	enum SIDE
	{
		SIDE_LEFT,
		SIDE_TOP,
		SIDE_RIGHT,
		SIDE_BOTTOM
	};
private:
	POINT ptMonster_Position;
	POINT ptTemp_Position;
	int speed;
	bool bDead;
	int pattern;
	int Direction;
	
public:
	Monster(int,int);
	~Monster();
	int iTimeCheck;
public:
	void setSpeed(int);
	int getSpeed();

	POINT getPosition();
	void setPosition(POINT);


	void setDirection(int);
	int getDirection();

	void setDead(bool);
	bool getDead();



public:
	void ObjectCollide(std::vector<Monster*>);
	bool Collide(POINT,POINT);
	void PolygonCollide(int);
	void TimeCheck();


	void Update();
	void Render(HDC);
	void reflection(POINT);
	void Move();
	void Init();
	void Free();

};

