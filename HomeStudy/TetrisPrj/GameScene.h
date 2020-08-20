#pragma once
class GameScene :public Scene
{
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
	GameCenter* getGameCenter() { return m_gameCenter; }
};

