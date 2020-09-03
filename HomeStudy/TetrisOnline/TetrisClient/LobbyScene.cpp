#include "stdafx.h"

extern SoundManager* g_theSoundManager;
extern NetWorkManager *g_NetworkManager;

extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;
extern Packet pk_Packet;

LobbyScene::LobbyScene()
{
	g_NetworkManager = NetWorkManager::GetInstance();
	g_NetworkManager->setHwnd(GameCenter::GetInstance()->getHwnd());
	g_NetworkManager->Connect();
}


LobbyScene::~LobbyScene()
{
}

void LobbyScene::Init(void)
{
	ExitBtn = {900,0,900+245,105};
	RoomMakeBtn = {700 , 450 , 700 + 165 , 450 + 165 };

	memset(pk_Lobby_Message.Buffer, '\0', 64 * sizeof(char));
	//pk_Lobby.User_Position = 100;

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
	case WM_CHAR:
		InputProcess(wParam);
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


	//size_t UserListSize = 0;
	//UserListSize = g_NetworkManager->userList.size();
	//if (UserListSize > 6)
	//{
	////	NetWorkManager::GetInstance()->chatLog.erase(NetWorkManager::GetInstance()->chatLog.begin());
	//	UserListSize = 6;
	//}

	//for (size_t i = 0; i < UserListSize; i++)
	//{
	//	TextOut(hdc, 0, 720 - (i * 20), (LPCWSTR)g_NetworkManager->userList.front()+i, 4);
	//}

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

	size_t chatLogSize = 0;
	chatLogSize = NetWorkManager::GetInstance()->getChatLogSize();
	if (chatLogSize > 6)
	{
		NetWorkManager::GetInstance()->chatLog.erase(NetWorkManager::GetInstance()->chatLog.begin());
		chatLogSize = 6;
	}

	for (size_t i = 0; i < chatLogSize; i++)
	{
		TextOut(hdc, 140, 720 - (i * 20), g_NetworkManager->chatLog[chatLogSize - 1 - i], _tcslen(g_NetworkManager->chatLog[chatLogSize - 1 - i]));
	}
	

	RECT charRect = { 135, 740, 1009, 783 };
	DrawText(hdc, NetWorkManager::GetInstance()->str, _tcslen(NetWorkManager::GetInstance()->str), &charRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

}

void LobbyScene::InputProcess(WPARAM wParam)
{
	if (wParam == VK_RETURN)
	{
		if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
			return ;

		WideCharToMultiByte(CP_ACP, 0, NetWorkManager::GetInstance()->str, 64, pk_Lobby_Message.Buffer, 64, NULL, NULL);
	
		pk_Packet.Protocal = LOBBY_MESSAGE;
		char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pkLobbyMessage)];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], pk_Lobby_Message.Buffer, sizeof(pkLobbyMessage));
		
		if (send(NetWorkManager::GetInstance()->server, buffer, _msize(buffer), 0) == -1)
		{
			exit(-1);
		}
		else
		{
			NetWorkManager::GetInstance()->count = 0;
			NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count] = NetWorkManager::GetInstance()->str[1] = '\0';
		}

		/*
		pk_header.Protocal = LOBBY_MESSAGE;
		pk_header.size = sizeof(pkLobby);
		if (send(NetWorkManager::GetInstance()->server, (char*)&pk_header, sizeof(pkHeader), 0) == SOCKET_ERROR)
		{
			exit(1);
		}
		else
		{
			pk_header.Protocal = 0;
			pk_header.size = 0;
		}

		WideCharToMultiByte(CP_ACP, 0, NetWorkManager::GetInstance()->str, 64, pk_Lobby.Buffer, 64, NULL, NULL);
		if (send(NetWorkManager::GetInstance()->server, (char*)&pk_Lobby, sizeof(pkLobby), 0) == -1)
		{
			exit(-1);
		}
		else
		{
			NetWorkManager::GetInstance()->count = 0;
			NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count] = NetWorkManager::GetInstance()->str[1] = '\0';
		}*/

	}
	else if (wParam == VK_BACK)
	{
		if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
			return;
		if (NetWorkManager::GetInstance()->count != 0)
			NetWorkManager::GetInstance()->str[--NetWorkManager::GetInstance()->count] = '\0';
	}
	else if(wParam != 0)
	{
		if (NetWorkManager::GetInstance()->count < 40)
		{
			NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count++] = (TCHAR)wParam;
			NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count] = '\0';
		}
	}
}
