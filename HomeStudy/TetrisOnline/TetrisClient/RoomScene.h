#pragma once
class RoomScene :public Scene
{

public:
	RoomScene();
	~RoomScene();

private:
	HBITMAP hBackGround;
	BITMAP bitBackground;
	HDC hBackDC;

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);

public:
	void RoomDraw(HDC hdc);
	void CharacterDraw(HDC hdc);
		
};

