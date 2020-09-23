#include "stdafx.h"

extern SoundManager* g_theSoundManager;


LoginScene::LoginScene()
{

}


LoginScene::~LoginScene()
{
}

void LoginScene::Init()
{
	
	StartBtnRect = { 455, 300,650,500 };
	LobbyBtnRect = { 455, 550,650,750 };

	m_startBtn_size = false;
	m_LobbyBtn_size = false;


}

void LoginScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
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

void LoginScene::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);
	//GameCenter::GetInstance()->getUI()->UIRender(hdc);
	

}

void LoginScene::Free()
{

}

void LoginScene::UI(HDC hdc)
{
	BackGroundDraw(hdc);
	StartButtonDraw(hdc);
	LobbyButtonDraw(hdc);
	TitleDraw(hdc);
}

void LoginScene::ClickEvent(LPARAM lParam)
{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);


		if (Clickx >= StartBtnRect.left &&Clickx <= StartBtnRect.right
			&& Clicky >= StartBtnRect.top && Clicky <= StartBtnRect.bottom)
		{
			g_theSoundManager->PlaySFX("Select");
			GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOCALGAME_SCENE);

		}
		else if (Clickx >= LobbyBtnRect.left &&Clickx <= LobbyBtnRect.right
			&& Clicky >= LobbyBtnRect.top && Clicky <= LobbyBtnRect.bottom)
		{
			g_theSoundManager->PlaySFX("Select");
			GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOBBY_SCENE);
		}


		
}

void LoginScene::BackGroundDraw(HDC hdc)
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

void LoginScene::StartButtonDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/StartBtn.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	//Rectangle(hdc, 455, 300,650,500);
	if (m_startBtn_size == false)
	{
		TransparentBlt(hdc, StartBtnRect.left, StartBtnRect.top, bx, by, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
	}
	else
	{
		TransparentBlt(hdc, StartBtnRect.left-30, StartBtnRect.top-30, bx* BtnZoom, by * BtnZoom, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
	}
	

	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LoginScene::LobbyButtonDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/StartBtn.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	//Rectangle(hdc, 455, 300,650,500);
	if (m_LobbyBtn_size == false)
	{
		TransparentBlt(hdc, LobbyBtnRect.left, LobbyBtnRect.top, bx, by, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
	}
	else
	{
		TransparentBlt(hdc, LobbyBtnRect.left - 30, LobbyBtnRect.top - 30, bx* BtnZoom, by * BtnZoom, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
	}


	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LoginScene::TitleDraw(HDC hdc)
{
	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/Title.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;

	//StretchBlt(hdc, 0, 0, bx, by, hBackDC, 0, 0, bx, by, SRCCOPY);   //각 블럭의 색
	TransparentBlt(hdc,0, 0, bx, by, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.


	DeleteDC(hBackDC);

	DeleteObject(hBackGround);
}

void LoginScene::BtnAnimaition(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (Clickx >= StartBtnRect.left &&Clickx <= StartBtnRect.right
		&& Clicky >= StartBtnRect.top && Clicky <= StartBtnRect.bottom)
	{
		m_startBtn_size = true;

	}
	else if (Clickx >= LobbyBtnRect.left &&Clickx <= LobbyBtnRect.right
		&& Clicky >= LobbyBtnRect.top && Clicky <= LobbyBtnRect.bottom)
	{
		m_LobbyBtn_size = true;

	}
	else
	{
		m_startBtn_size = false;
		m_LobbyBtn_size = false;
	}

}
