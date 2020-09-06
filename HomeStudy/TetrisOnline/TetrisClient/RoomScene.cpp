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
	RoomDraw(hdc);
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

void RoomScene::RoomDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Room.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	StretchBlt(hdc, 0, 0, bx*8, by*5.2, hBackDC, 0, 0, bx, by, SRCCOPY);   //각 블럭의 색

	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}
