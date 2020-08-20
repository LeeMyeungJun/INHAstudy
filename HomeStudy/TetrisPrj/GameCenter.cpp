#include "stdafx.h"


SoundCenter* GameCenter::m_SoundCeneter =nullptr;
UI * GameCenter::m_UI = nullptr;

GameCenter::GameCenter()
{
	m_Scene = nullptr;
	m_LoginScene = nullptr;
	m_LobbyScene = nullptr;
	m_RoomScene = nullptr;
	m_GameScene = nullptr;

	m_SoundCeneter = new SoundCenter(this);
	m_UI = new UI(this);
	Init();
	
}


GameCenter::~GameCenter()
{
}


void GameCenter::Init()
{
	m_Scene = m_LoginScene = new LoginScene;
	m_Scene_enum = Scene_enum::LOGIN_SCENE;
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

void GameCenter::SceneChange(Scene_enum nextScene)
{
	m_Scene->Free();


	switch (nextScene)
	{
	case Scene_enum::LOGIN_SCENE:
		m_Scene = m_LoginScene;
		m_Scene_enum = Scene_enum::LOGIN_SCENE;
		break;
	case Scene_enum::LOBBY_SCENE:
		if (m_LobbyScene == nullptr)
			m_LobbyScene = new LobbyScene;
		m_Scene = m_LobbyScene;
		m_Scene_enum = Scene_enum::LOBBY_SCENE;
		break;
	case Scene_enum::ROOM_SCENE:
		if (m_RoomScene == nullptr)
			m_RoomScene = new RoomScene;
		m_Scene = m_RoomScene;
		m_Scene_enum = Scene_enum::ROOM_SCENE;
		break;
	case Scene_enum::GAME_SCENE:
		if (m_GameScene == nullptr)
			m_GameScene = new GameScene;
		m_Scene = m_GameScene;
		m_Scene_enum = Scene_enum::GAME_SCENE;
		break;
	case Scene_enum::EXIT:
		if (m_LoginScene != nullptr) delete m_LoginScene;
		if (m_LobbyScene != nullptr) delete m_LobbyScene;
		if (m_RoomScene != nullptr) delete m_RoomScene;
		if (m_GameScene != nullptr) delete m_GameScene;
		if (m_UI != nullptr) delete m_UI;
		if (m_SoundCeneter != nullptr) delete m_SoundCeneter;
		if (m_Scene != nullptr) delete m_Scene;

		PostQuitMessage(0);
		return;
	}

	m_Scene->Init();
	InvalidateRect(getHwnd(), NULL, true);
}
