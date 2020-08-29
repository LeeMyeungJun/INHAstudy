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
	//GameCenter::GetInstance()->getUI()->UIRender(hdc);
	UI(hdc);
}

void LobbyScene::Free(void)
{
}

void LobbyScene::UI(HDC hdc)
{
	BackGroundDraw(hdc);
	ChattingDraw(hdc);
	LobbyRoomDraw(hdc);
	LobbyUserBoardDraw(hdc);
}

void LobbyScene::ClickEvent(LPARAM lParam)
{
	//int Clickx = LOWORD(lParam);
	//int Clicky = HIWORD(lParam);

	//if (Clickx >= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().right
	//	&& Clicky >= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getLobby_ExitBtn().bottom)
	//{
	//	PostQuitMessage(0);
	//}
	//else if (Clickx >= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().right
	//	&& Clicky >= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getLobby_RoomMakeBtn().bottom)
	//{
	//	GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::ROOM_SCENE);
	//}
	

}

void LobbyScene::BackGroundDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Login.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	StretchBlt(hdc, 0, 0, bx + 880, by + 644, hBackDC, 0, 0, bx, by, SRCCOPY);   //각 블럭의 색


	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LobbyScene::ChattingDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/LobbyChat.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc, 0, 550, bx*8.7, by*4.5, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LobbyScene::LobbyRoomDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/LobbyChat.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc, 0, 0, bx*7, by * 8, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LobbyScene::LobbyUserBoardDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/LobbyUserBoard.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	TransparentBlt(hdc,900, 0, bx*3.5, by*4, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.

	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}
