#pragma once

class Scene;
class RankScene;
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
	RankScene	* m_RankScene;

public:
	GameCenter();
	~GameCenter();

	void Setup();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(SceneState nextScene);


	static GameCenter* GetInstance()
	{
		static GameCenter * instance = new GameCenter();
		return instance;
	}
};

