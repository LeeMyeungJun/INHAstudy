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
	//Scene		* m_Scene;
	//LobbyScene	* m_LobbyScene;
	//GameScene	* m_GameScene;
	//EndScene	* m_EndScene;

	SceneState	 m_SceneState;

	//static DataManager* data_;
	static Scene* Scene_;
	//static LobbyScene* LobbyScene_;
	//static GameScene* GameScene_;
	//static EndScene* EndScene_;


public:
	static GameCenter* GetInstance()
	{
		static GameCenter * instance = new GameCenter();
		return instance;
	}

	static Scene& GetScene(){return *Scene_;}

	static void provid(Scene* Scene);

public:
	GameCenter();
	~GameCenter();

	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(SceneState nextScene);


	/*
	public:
	static FileSystem& instance()
	{
	if(instance_ ==NULL)
	instance_ = newFileSystem();
	return *instance_;
	}

	private:
	FileSystem(){}
	static FileSystem* instance
	*/
	


};

