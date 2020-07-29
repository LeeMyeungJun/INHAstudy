#pragma once
class PlayerManager
{
public:
	PlayerManager();
	~PlayerManager();
	void DrawPlayerCharacter(HDC hdc);


public:
	POINT ptPosition;
	int slope;
};

