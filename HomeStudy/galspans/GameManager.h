#pragma once


class Scene;
class EndScene;
class GameScene;
class MenuScene;

enum class Scene_enum : size_t
{
	SCENE_NONE,
	SCENE_MENU,
	SCENE_GAME,
	SCENE_NEXT_STAGE,
	SCENE_END,
	SCENE_EXIT
};


class GameManager
{



private:
	Scene		* m_Scene;
	MenuScene	* m_MenuScene;
	GameScene	* m_GameScene;
	EndScene	* m_EndScene;

	Scene_enum	  m_Scene_enum;
 
public:
	GameManager();
	~GameManager();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(Scene_enum nextScene);




	static GameManager* GetInstance()
	{
		static GameManager ins;
		return &ins;
	}

//private:
//	static GameManager* ins;
//public:
//	static GameManager& GetInstance()
//	{
//		if (ins == NULL)
//		{
//			ins = new GameManager();
//		}
//		return *ins;
//	}

//static GameManager& GetInstance()
//{
//	static GameManager *instance = new GameManager();
//	return *instance;
//}


}; 


