#include "stdafx.h"

extern SoundManager* g_theSoundManager;
LobbyScene::LobbyScene()
{
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init(void)
{
	ExitBtn = {900,0,900+245,105};
	RoomMakeBtn = {700 , 450 , 700 + 165 , 450 + 165 };

	//UnderChatRect;
	//UserChatRect;

	m_ExitBtn_size = false;
	m_RoomBtn_size = false;
}

void LobbyScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		ClickEvent(lParam);
		break;
	case WM_MOUSEMOVE:
		BtnAnimaition(lParam);
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
	ExitBtnDraw(hdc);
	RoomCreateBtnDraw(hdc);
	ChatDraw(hdc);
}

void LobbyScene::ClickEvent(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= ExitBtn.left &&Clickx <= ExitBtn.right
		&& Clicky >= ExitBtn.top && Clicky <= ExitBtn.bottom)
	{
		PostQuitMessage(0);
	}
	else if (Clickx >= RoomMakeBtn.left &&Clickx <= RoomMakeBtn.right
		&& Clicky >= RoomMakeBtn.top && Clicky <= RoomMakeBtn.bottom)
	{
		g_theSoundManager->PlaySFX("Select");
		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::ROOM_SCENE);
	}
	

}

void LobbyScene::BtnAnimaition(LPARAM lParam)
{

	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= ExitBtn.left &&Clickx <= ExitBtn.right
		&& Clicky >= ExitBtn.top && Clicky <= ExitBtn.bottom)
	{
		m_ExitBtn_size = true;

	}
	else if (Clickx >= RoomMakeBtn.left &&Clickx <= RoomMakeBtn.right
		&& Clicky >= RoomMakeBtn.top && Clicky <= RoomMakeBtn.bottom)
	{
		m_RoomBtn_size = true;

	}
	else
	{
		m_ExitBtn_size = false;
		m_RoomBtn_size = false;
	
	}

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

	TransparentBlt(hdc,900, 50, bx*3.5, by*4, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.

	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LobbyScene::ExitBtnDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/ExitBtn.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;
	if (m_ExitBtn_size == false)
	{
		TransparentBlt(hdc, 900, 0, bx * 2, by*1.5, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
	}
	else
	{
		TransparentBlt(hdc, 850, 0, (bx * 2)*BtnZoom, (by*1.5)*BtnZoom, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
	}

	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LobbyScene::RoomCreateBtnDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/RoomMakeBtn.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	if (m_RoomBtn_size == false)
	{
		TransparentBlt(hdc, 700, 450, bx*1.4, by*1.4, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것
	}
	else
	{
		TransparentBlt(hdc, 680, 430, bx*1.4 * BtnZoom, by*1.4 * BtnZoom, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것

	}
	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LobbyScene::ChatDraw(HDC hdc)
{
	Rectangle(hdc, 130, 740, 1009, 783);
}
