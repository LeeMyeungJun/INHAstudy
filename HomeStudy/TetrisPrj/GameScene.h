#pragma once

#define WIDTH 10
#define HEIGHT 20

enum eInputType { NONE, LEFT, RIGHT, UP, DOWN, SPACE, ESC };

class GameScene :public Scene
{
private:
	unsigned char mMap[HEIGHT][WIDTH];
	Block m_NextBlock;
	Block m_CurBlock;
	bool m_Lose;
	HINSTANCE hInst;

	HDC hdc2;
	HBITMAP newBitmap, oldBitmap;

	eInputType inputType;

public:
	GameScene();
	~GameScene();

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

};

