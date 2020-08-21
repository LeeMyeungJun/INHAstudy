#pragma once

#define WIDTH 12
#define HEIGHT 20

enum eInputType { NONE, LEFT, RIGHT, UP, DOWN, SPACE, ESC };

class GameScene :public Scene
{
private:
	unsigned char mMap[HEIGHT][WIDTH];
	wstring tetromino[7];
	bool m_Lose;



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
	int Rotate(int px, int py, int r);

};


