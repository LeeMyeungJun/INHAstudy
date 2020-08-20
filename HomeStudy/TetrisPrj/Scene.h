#pragma once
//class GameCenter;

class Scene
{
protected:
	GameCenter* m_gameCenter;
public:
	Scene(GameCenter*);
	Scene();
	virtual ~Scene();

	virtual void Init(void) = 0;
	virtual void Update(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Render(HWND hWnd, HDC hdc) = 0;
	virtual void Free(void) = 0;
	virtual void UI(HDC hdc) = 0;

public:
	GameCenter* getGameCenter() { return m_gameCenter; }


};

