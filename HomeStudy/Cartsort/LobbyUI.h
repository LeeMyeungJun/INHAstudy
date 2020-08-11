#pragma once
class LobbyUI : public UI
{
public:
	LobbyUI();
	~LobbyUI();

	void Draw(HWND hWnd, HDC hdc);
	void Free(void);
};

