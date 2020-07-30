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
	POINT ptTemp; //�����ε������� ���ư����Ϸ��� ���� ����

	int iDirection; //< LEFT 0  UP 1 RIGHT 2 DOWN 3
	int tempDirection;

	int PlayerLinePosition;
};

