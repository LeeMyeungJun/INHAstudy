#pragma once
class GameUI :public UI
{
public:
	GameUI();
	~GameUI();

	void Draw(HWND hWnd, HDC hdc);
	void Free(void);
};

