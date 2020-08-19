#pragma once
class Player
{
public:
	Player();
	~Player();
public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);

private:
	POINT m_position;

};

