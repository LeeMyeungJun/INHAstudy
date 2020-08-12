#include "stdafx.h"


Scene* GameCenter::Scene_;

void GameCenter::provid(Scene * Scene)
{
	if (Scene_ == NULL)
		Scene_ = new LobbyScene(GameCenter::GetScene());
	else
		Scene_ = Scene;

}

GameCenter::GameCenter()
{
	//Scene *scene = GameCenter::GetScene();
	//m_LobbyScene = nullptr;
	//m_GameScene = nullptr;
	//m_EndScene = nullptr;

	//*Scene_ = GameCenter::GetScene();
	Init();
	
}


GameCenter::~GameCenter()
{
}

void GameCenter::Init()
{
	/*if(Scene_ == nullptr)
		Scene_ = new LobbyScene(GameCenter::GetScene());*/
	GameCenter::provid(Scene_);
	Scene_->Init();
}

void GameCenter::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	Scene_->Update(message, wParam, lParam);
}

void GameCenter::Render(HWND hWnd, HDC hdc)
{
	Scene_->Render(hWnd, hdc);
}

void GameCenter::SceneChange(SceneState nextScene)
{

	Scene_->Free();

	switch (nextScene)
	{
	case SceneState::Enum_Lobby:
		Scene_ = new LobbyScene(GameCenter::GetScene());
		GameCenter::provid(Scene_);
		break;
	case SceneState::Enum_Game:
		Scene_ = new GameScene(GameCenter::GetScene());
		GameCenter::provid(Scene_);
		break;
	case SceneState::Enum_End:
		Scene_ = new EndScene(GameCenter::GetScene());
		GameCenter::provid(Scene_);
		break;
	case SceneState::Enum_Quit:
		Scene_ = nullptr;
		PostQuitMessage(0);
		return;
		break;
	}
	Scene_->Init();
}
