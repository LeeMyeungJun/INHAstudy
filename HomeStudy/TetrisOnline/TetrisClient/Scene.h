#pragma once
//class GameCenter;

class Scene
{
public:
	Scene();
	virtual ~Scene();

	virtual void Init(void) = 0;
	virtual void Update(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Render(HWND hWnd, HDC hdc) = 0;
	virtual void Free(void) = 0;
	virtual void UI(HDC hdc) = 0;
	virtual void ClickEvent(LPARAM lParam) = 0;
};

