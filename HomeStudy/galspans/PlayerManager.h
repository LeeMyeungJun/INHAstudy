#pragma once
class PlayerManager
{
public:
	enum Direction : size_t
	{
		LEFT = 0 ,
		UP = 1,
		RIGHT = 2,
		DOWN = 3
	};


public:
	PlayerManager();
	~PlayerManager();
	void DrawPlayerCharacter(HDC hdc);


public:
	POINT ptPosition;
	POINT ptTemp; //꼬리부딛혓을떄 돌아가게하려는 저장 변수

	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
	int tempDirection;

	int PlayerLinePosition;
};

