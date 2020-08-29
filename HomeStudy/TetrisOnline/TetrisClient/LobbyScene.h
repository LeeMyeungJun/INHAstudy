#pragma once
class LobbyScene :public Scene
{
private:
	HBITMAP hBackGround;
	BITMAP bitBackground;
	HDC hBackDC;
public:
	LobbyScene();
	~LobbyScene();

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);

private:
	void BackGroundDraw(HDC hdc);
	void ChattingDraw(HDC hdc);
	void LobbyRoomDraw(HDC hdc);
	void LobbyUserBoardDraw(HDC hdc);


};

