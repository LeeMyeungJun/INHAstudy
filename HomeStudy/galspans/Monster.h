#pragma once

class Monster
{
private :
	enum SPEED
	{
		SPEED_ONE = 10,
		SPEED_TWO = 20,
		SPEED_THREE= 30
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
	int speed;
	bool bDead;
	int pattern;
	int Direction;
public:
	Monster(int x, int y);
	~Monster();

public:
	void setSpeed(int);
	int getSpeed();

	POINT getPosition();
	void setPosition(POINT);

	void ChangeDirection();
	int getDirection();


public:
	void MonsterPatternUp();

	void ObjectCollide(std::vector<Monster*>);
	bool Collide(POINT,POINT);


	void Update();
	void Render(HDC);
	void reflection(POINT);
	void Move();
	void Init();
	void Free();

};

