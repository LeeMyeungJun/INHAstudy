#pragma once
class EndUI :public UI
{
public:
	EndUI();
	~EndUI();

	void Draw(HWND hWnd, HDC hdc);
	void Free(void);
};

