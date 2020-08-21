#include "stdafx.h"


RoomScene::RoomScene()
{
}


RoomScene::~RoomScene()
{
}

void RoomScene::Init(void)
{
}

void RoomScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		ClickEvent(lParam);
		break;
	default:
		break;
	}
}

void RoomScene::Render(HWND hWnd, HDC hdc)
{
	GameCenter::GetInstance()->getUI()->UIRender(hdc);
}

void RoomScene::Free(void)
{
}

void RoomScene::UI(HDC hdc)
{
}

void RoomScene::ClickEvent(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= GameCenter::GetInstance()->getUI()->getRoom_ReadyBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRoom_ReadyBtn().right
		&& Clicky >= GameCenter::GetInstance()->getUI()->getRoom_ReadyBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRoom_ReadyBtn().bottom)
	{
		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::GAME_SCENE);

	}
	else if (Clickx >= GameCenter::GetInstance()->getUI()->getRoom_ExitBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRoom_ExitBtn().right
		&& Clicky >= GameCenter::GetInstance()->getUI()->getRoom_ExitBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRoom_ExitBtn().bottom)
	{
		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOBBY_SCENE);
	}
}
