#pragma once
class GameScene :public Scene
{
private:
	
	char boardState[19][19];

public:
	GameScene();
	~GameScene();

	
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void BlackStone(HDC hdc,POINT);
	void WhiteStone(HDC hdc,POINT);
	void DrawChat(HDC hdc);
	void StoneRender(HDC hdc);
	int Distance(const POINT& p1, const POINT& p2);
	void ChatLog(WPARAM wParam);
	void ClickEvent(UINT message , LPARAM lParam);

	HBRUSH charRectBrush = CreateSolidBrush(RGB(40, 170, 220));
	HBRUSH charRectTitleBrush = CreateSolidBrush(RGB(100, 250, 150));

	struct boardPoint
	{
		int x;
		int y;
	};

public:
	int Clickx;
	int Clicky;
	WCHAR tcharx[30];
	WCHAR tchary[30];
	boardPoint board[19][19];
	TCHAR str[100] = { 0 };
	TCHAR tchturn[3] = { 0 };
	int count;


	HBRUSH myBrush, oldBrush;

};

