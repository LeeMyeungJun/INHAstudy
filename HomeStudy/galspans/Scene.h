#pragma once

class UI;
class EndUI;
class MenuUI;
class GameUI;



class Scene
{
public:
	UI		* m_SceneUI = nullptr;
	MenuUI	* m_MenuUI = new MenuUI;
	GameUI  * m_GameUI = new GameUI;
	EndUI	* m_EndUI = new EndUI;

	

	Scene();
	virtual ~Scene();

	virtual void Init(void) = 0;
	virtual void Update(UINT message, WPARAM wParam, LPARAM lParam) = 0;
	virtual void Render(HWND hWnd, HDC hdc) = 0;
	virtual void Free(void) = 0;
};

