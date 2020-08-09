#include "stdafx.h"



GameCenter::GameCenter()
{
	m_Scene = nullptr;
	m_LobbyScene = nullptr;
	m_GameScene = nullptr;
	m_EndScene = nullptr;
	m_Data = new DataManager;
	Init();
}


GameCenter::~GameCenter()
{
}

void GameCenter::Init()
{
	m_SceneState = SceneState::Enum_Lobby;
	m_Scene = m_LobbyScene = new LobbyScene;
	m_Scene->Init();
}

void GameCenter::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	m_Scene->Update(message, wParam, lParam);
}

void GameCenter::Render(HWND hWnd, HDC hdc)
{
	m_Scene->Render(hWnd, hdc);
}

void GameCenter::SceneChange(SceneState nextScene)
{
	m_Scene->Free();
	switch (nextScene)
	{
	case SceneState::Enum_Lobby:
		m_Scene = m_LobbyScene;
		break;
	case SceneState::Enum_Game:
		if (m_GameScene == nullptr)
			m_GameScene = new GameScene;
		m_Scene = m_GameScene;
		break;
	case SceneState::Enum_End:
		if (m_EndScene == nullptr)
			m_EndScene = new EndScene;
		m_Scene = m_EndScene;
		break;
	case SceneState::Enum_Quit:
		if (m_EndScene != nullptr) delete m_EndScene;
		if (m_GameScene != nullptr) delete m_GameScene;
		if (m_LobbyScene != nullptr) delete m_LobbyScene;
		m_Scene = nullptr;
		PostQuitMessage(0);
		return;
		break;
	}
	m_Scene->Init();
}
