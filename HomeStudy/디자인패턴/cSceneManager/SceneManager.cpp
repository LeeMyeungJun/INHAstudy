#include "stdafx.h"
#include "SceneManager.h"


SceneManager::SceneManager()
	: m_CurrentScene(NULL)
{

}


SceneManager::~SceneManager()
{
}

void SceneManager::SceneChange(string sceneName)
{
	if (m_SceneList.find(sceneName) == m_SceneList.end())
	{
		cout << "�ش������" << endl;
		return;
	}
	m_CurrentScene = m_SceneList[sceneName];
}

void SceneManager::AddScene(std::string SceneName, Scene* Scene)
{
	if (m_SceneList.find(SceneName) == m_SceneList.end())
	{
		if(m_SceneList[SceneName] != nullptr)
		{
			cout << "�̹� �ش���� �ֽ��ϴ�." << endl;
			return;
		}
	}
	m_SceneList[SceneName] = Scene;
}

void SceneManager::EraseScene(std::string SceneName)
{
	if (m_SceneList.find(SceneName) == m_SceneList.end())
	{
		cout << "�ش������" << endl;
		return;
	}
	
	m_SceneList[SceneName] = nullptr;
}

Scene* SceneManager::GetCurrentScene()
{
	return m_CurrentScene;
}

