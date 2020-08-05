#pragma once
#define MONSTER_SIZE 10

class Monster
{
public :
	enum SPEED
	{
		SPEED_ONE = 10,
		SPEED_TWO = 20,
		SPEED_THREE= 30
	};
private:
	POINT ptMonster_Position;
	int speed;
	bool bDead;
	int pattern;
public:
	Monster(int x, int y);
	~Monster();


	void setSpeed(int);
	void setPosition(POINT);

	int getSpeed();
	POINT getPosition();

	void MonsterPatternUp();


	void Update();
	void Render(HDC);
	void reflection();
	void Move();

};

