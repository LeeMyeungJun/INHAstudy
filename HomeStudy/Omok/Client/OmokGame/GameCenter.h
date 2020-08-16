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
//private:
//	HWND hWnd;
	//char Player;
	//char m_turn;
private:
	static Bitmap * m_Bitmap;
	Scene * m_Scene;
	GameScene *m_GameScene;
	MenuScene *m_MenuScene;
	
public:
	GameCenter();
	~GameCenter();

	Scene_enum  m_Scene_enum;

	static GameCenter* GetInstance()
	{
		static GameCenter instance;
		return &instance;
	}


	GameScene* getGameScene() { return m_GameScene; }

public:
	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(Scene_enum nextScene);
};

