#pragma once

class Scene;
class EndScene;
class GameScene;
class LobbyScene;
class DataManager;
enum class SceneState;

class GameCenter
{
	
private:
	Scene		* m_Scene;
	LobbyScene	* m_LobbyScene;
	GameScene	* m_GameScene;
	EndScene	* m_EndScene;
	
	SceneState	 m_SceneState;

	DataManager  *m_Data;
	
	UI			* m_UI;
	//LobbyUI		* m_LobbyUI;
	//GameUI      * m_GameUI;


public:
	GameCenter();
	~GameCenter();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(SceneState nextScene);

	
};

