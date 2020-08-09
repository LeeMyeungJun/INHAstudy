#pragma once
class LobbyScene :public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
};

