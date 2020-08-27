#pragma once
class LoginScene :public Scene
{
public:
	LoginScene();
	~LoginScene();

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);

private:
	HBITMAP hBackGround;
	BITMAP bitBackground;
	HDC hBackDC;
	
	RECT clientRect;

};

