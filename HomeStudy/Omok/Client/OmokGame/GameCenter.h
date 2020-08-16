#pragma once

class Bitmap;
class Scene;
class GameScene;
class MenuScene;


enum class Scene_enum :size_t
{
	MENU_ENUM,
	GAME_ENUM,
	EXIT_ENUM
};


class GameCenter
{
private:
	HWND hWnd;
	char Player;
private:
	static Bitmap * m_Bitmap;
	Scene * m_Scene;
	GameScene *m_GameScene;
	MenuScene *m_MenuScene;
	
public:
	GameCenter();
	~GameCenter();

	Scene_enum  m_Scene_enum;

	void setPlayer(char player) { this->Player = player; }
	char getPlayer() { return Player; }

	static GameCenter* GetInstance()
	{
		static GameCenter instance;
		return &instance;
	}



	void setHwnd(HWND hWnd)
	{
		this->hWnd = hWnd;
	}
	HWND getHwnd() { return hWnd; }

public:
	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(Scene_enum nextScene);
};
