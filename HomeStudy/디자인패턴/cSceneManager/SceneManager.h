#pragma once

#define g_SceneManager SceneManager::GetInstance()


class SceneManager
{
private:
	SceneManager();
	~SceneManager();

public:
	static SceneManager* GetInstance()
	{
		static SceneManager instance;
		return &instance;
	}


public:
	void SceneChange(std::string sceneName);
	void AddScene(std::string SceneName, Scene* scene);
	void EraseScene(std::string SceneName);
	
	Scene* GetCurrentScene();
	
private:
	std::map<std::string,Scene*> m_SceneList;
	Scene* m_CurrentScene;

};

