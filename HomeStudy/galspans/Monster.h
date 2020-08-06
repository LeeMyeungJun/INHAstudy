#pragma once

class Monster
{
private :
	enum SPEED
	{
		SPEED_ONE = 10,
		SPEED_TWO = 8,
		SPEED_THREE= 5
	};
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

public:
	void setSpeed(int);
	int getSpeed();

	POINT getPosition();
	void setPosition(POINT);

	void ChangeDirection();
	void setDirection(int);
	int getDirection();

	void setDead(bool);
	bool getDead();



public:
	void ObjectCollide(std::vector<Monster*>);
	bool Collide(POINT,POINT);

	void Update();
	void Render(HDC);
	void reflection(POINT);
	void Move();
	void Init();
	void Free();

};

