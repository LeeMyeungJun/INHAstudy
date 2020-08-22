#pragma once

#define WIDTH 12
#define HEIGHT 20

enum eInputType { NONE, LEFT, RIGHT, UP, DOWN, SPACE, ESC };

class GameScene :public Scene
{
private:
	unsigned char mMap[HEIGHT][WIDTH];
	//wstring mBlock[7];
	bool m_Lose;
	Block *m_block;
	POINT m_Position[HEIGHT][WIDTH];
	eInputType inputType;

public:
	GameScene();
	~GameScene();
	HDC hBlocksDc;
	HBITMAP hBlocks;
	BITMAP bitBlcok;
	POINT getPosition(int x,int y) { return m_Position[y][x]; }
	void setPosition(POINT position,int x , int y) { m_Position[y][x] = position; }

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);

public:
	void ClickEvent(LPARAM lParam);
	void Input();
	void InputProcess();
	
	void DrawBlcok(HDC hdc);
	void TransBlt(HDC hdc, int x, int y,int Color);
	void MoveBlock();


};


