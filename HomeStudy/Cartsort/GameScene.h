#pragma once
class GameScene :public Scene
{

public:
	GameScene() {};
	~GameScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
};

