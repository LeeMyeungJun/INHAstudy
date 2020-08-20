#include "stdafx.h"


LoginScene::LoginScene()
{
}


LoginScene::~LoginScene()
{
}

void LoginScene::Init(void)
{
}

void LoginScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
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

void LoginScene::Render(HWND hWnd, HDC hdc)
{
	getGameCenter()->getUI()->UIRender(hdc);
}

void LoginScene::Free(void)
{

}

void LoginScene::UI(HDC hdc)
{
}

void LoginScene::ClickEvent(LPARAM lParam)
{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);

		if (Clickx >= getGameCenter()->getUI()->getRCExitBtn().left &&Clickx <= getGameCenter()->getUI()->getRCExitBtn().right
			&& Clicky >= getGameCenter()->getUI()->getRCExitBtn().top && Clicky <= getGameCenter()->getUI()->getRCExitBtn().bottom)
		{
			PostQuitMessage(0);
		}
		else if (Clickx >= getGameCenter()->getUI()->getRcLocalBtn().left &&Clickx <= getGameCenter()->getUI()->getRcLocalBtn().right
			&& Clicky >= getGameCenter()->getUI()->getRcLocalBtn().top && Clicky <= getGameCenter()->getUI()->getRcLocalBtn().bottom)
		{
			getGameCenter()->SceneChange(GameCenter::Scene_enum::GAME_SCENE);
		}
		else if (Clickx >= getGameCenter()->getUI()->getRcOnlineBtn().left &&Clickx <= getGameCenter()->getUI()->getRcOnlineBtn().right
			&& Clicky >= getGameCenter()->getUI()->getRcOnlineBtn().top && Clicky <= getGameCenter()->getUI()->getRcOnlineBtn().bottom)
		{
			getGameCenter()->SceneChange(GameCenter::Scene_enum::GAME_SCENE);
		}

		
}
