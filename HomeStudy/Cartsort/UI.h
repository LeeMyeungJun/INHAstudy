#pragma once
class UI
{
public:
	UI();
	virtual ~UI();

	virtual void Draw(HWND hWnd, HDC hdc) = 0;
	virtual void Free(void) = 0;
};

