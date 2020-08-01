#include "stdafx.h"

extern GameManager * g_GameManager;


GameManager::GameManager()
{
	m_Scene = nullptr;
	m_MenuScene = nullptr;
	m_GameScene = nullptr;
	m_EndScene = nullptr;
	Init();

	//Scene		* m_Scene;
	//MenuScene	* m_MenuScene;
	//GameScene	* m_GameScene;
	//EndScene	* m_EndScene;

}


GameManager::~GameManager()
{


}

void GameManager::Init()
{
	m_Scene_enum = Scene_enum::SCENE_MENU;
	m_Scene = m_MenuScene = new MenuScene; 
	m_Scene->Init();
}

void GameManager::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	m_Scene->Update(message, wParam, lParam);
}

void GameManager::Render(HWND hWnd, HDC hdc)
{
	m_Scene->Render(hWnd,hdc);
}

void GameManager::SceneChange(Scene_enum nextScene)
{
	m_Scene->Free();
	switch (nextScene)
	{
	case Scene_enum::SCENE_MENU:
		m_Scene = m_MenuScene;
		m_Scene_enum = Scene_enum::SCENE_MENU;
		break;
	case Scene_enum::SCENE_GAME:
		if (m_GameScene == nullptr)
			m_GameScene = new GameScene;
		m_Scene = m_GameScene;
		m_Scene_enum = Scene_enum::SCENE_GAME;
		break;
	case Scene_enum::SCENE_END:
		if (m_EndScene == nullptr)
			m_EndScene = new EndScene;
		m_Scene = m_EndScene;
		m_Scene_enum = Scene_enum::SCENE_END;
		break;
	case Scene_enum::SCENE_EXIT:
		if (m_EndScene != nullptr) delete m_EndScene;
		if (m_GameScene != nullptr) delete m_GameScene;
		if (m_MenuScene != nullptr) delete m_MenuScene;
		m_Scene = nullptr;
		delete g_GameManager;
		PostQuitMessage(0);
		break;
	}


	m_Scene->Init();

}
