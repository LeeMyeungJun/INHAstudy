#include "stdafx.h"


LobbyScene::LobbyScene()
{
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init(void)
{
}

void LobbyScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
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

void LobbyScene::Render(HWND hWnd, HDC hdc)
{
	GameCenter::GetInstance()->getUI()->UIRender(hdc);
}

void LobbyScene::Free(void)
{
}

void LobbyScene::UI(HDC hdc)
{

}

void LobbyScene::ClickEvent(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().right
		&& Clicky >= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().bottom)
	{
		PostQuitMessage(0);
	}
	else if (Clickx >= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().right
		&& Clicky >= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().bottom)
	{
		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::ROOM_SCENE);
	}
	

}
