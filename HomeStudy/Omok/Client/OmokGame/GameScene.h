#pragma once
class GameScene :public Scene
{
private:
	
	char boardState[19][19];
	char m_player;
public:
	GameScene();
	~GameScene();

	
	char getPlayer(){return m_player;}
	void setPlayer(char player) { m_player = player; }

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
	WCHAR tcharx[30];
	WCHAR tchary[30];
	boardPoint board[19][19];
	
	HBRUSH myBrush, oldBrush;

};

