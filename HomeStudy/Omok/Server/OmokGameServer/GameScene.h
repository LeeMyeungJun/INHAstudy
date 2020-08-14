#pragma once
class GameScene :public Scene
{
private:
	std::vector<POINT> ClientOnePoint;
	std::vector<POINT> ClientTwoPoint;
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
	void StoneRender(HDC hdc);
	int Distance(const POINT& p1, const POINT& p2);

	struct boardPoint
	{
		int x;
		int y;
	};

public:
	int Clickx;
	int Clicky;
	TCHAR tcharx[30];
	TCHAR tchary[30];
	boardPoint board[19][19];

	HBRUSH myBrush, oldBrush;

};

