#pragma once

#define WIDTH 10
#define HEIGHT 20


class GameScene :public Scene
{


private:
	unsigned char mMap[HEIGHT][WIDTH];

public:
	GameScene();
	~GameScene();

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);

};

