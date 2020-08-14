#include "stdafx.h"

Bitmap * GameCenter::m_Bitmap = nullptr;

GameCenter::GameCenter()
{
	m_Bitmap = new Bitmap(this);
	Player = 'a';
	m_Scene = nullptr;
	m_MenuScene = nullptr;
	m_GameScene = nullptr;
	Init();
}


GameCenter::~GameCenter()
{
}


void GameCenter::Init()
{
	
	m_Scene = m_MenuScene = new MenuScene;
	m_Scene_enum = Scene_enum::MENU_ENUM;
	m_Scene->Init();
}

void GameCenter::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	m_Scene->Update(message, wParam, lParam);
}

void GameCenter::Render(HWND hWnd, HDC hdc)
{
	m_Scene->Render(hWnd,hdc);
}

void GameCenter::SceneChange(Scene_enum nextScene)
{
	m_Scene->Free();
	switch (nextScene)
	{
	case Scene_enum::MENU_ENUM:
		m_Scene = m_MenuScene;
		m_Scene_enum = Scene_enum::MENU_ENUM;
		break;
	case Scene_enum::GAME_ENUM:
		if (m_GameScene == nullptr)
			m_GameScene = new GameScene;
		m_Scene = m_GameScene;
		m_GameScene->setPlayer(getPlayer());
		m_Scene_enum = Scene_enum::GAME_ENUM;
		break;
	case Scene_enum::EXIT_ENUM:
		if (m_GameScene != nullptr) delete m_GameScene;
		if (m_MenuScene != nullptr) delete m_MenuScene;
		m_Scene = nullptr;
		PostQuitMessage(0);
		return;
	}

	m_Scene->Init();
	InvalidateRect(getHwnd(), NULL, true);
}
