#include "stdafx.h"


LoginScene::LoginScene()
{
	
}


LoginScene::~LoginScene()
{
}

void LoginScene::Init()
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
	UI(hdc);
	GameCenter::GetInstance()->getUI()->UIRender(hdc);
	

}

void LoginScene::Free()
{

}

void LoginScene::UI(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Login.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	StretchBlt(hdc, 0, 0, 1200, 900, hBackDC, 0, 0, bx, by, SRCCOPY);   //각 블럭의 색


	DeleteDC(hBackDC);

	DeleteObject(hBackGround);

}

void LoginScene::ClickEvent(LPARAM lParam)
{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);

		if (Clickx >= GameCenter::GetInstance()->getUI()->getRCLogin_ExitBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRCLogin_ExitBtn().right
			&& Clicky >= GameCenter::GetInstance()->getUI()->getRCLogin_ExitBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRCLogin_ExitBtn().bottom)
		{
			PostQuitMessage(0);
		}
		else if (Clickx >= GameCenter::GetInstance()->getUI()->getRcLogin_LocalBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRcLogin_LocalBtn().right
			&& Clicky >= GameCenter::GetInstance()->getUI()->getRcLogin_LocalBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRcLogin_LocalBtn().bottom)
		{
			GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOCALGAME_SCENE);

		}
		//else if (Clickx >= GameCenter::GetInstance()->getUI()->getRcLogin_OnlineBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRcLogin_OnlineBtn().right
		//	&& Clicky >= GameCenter::GetInstance()->getUI()->getRcLogin_OnlineBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRcLogin_OnlineBtn().bottom)
		//{
		//	GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOBBY_SCENE);
		//}

		
}
