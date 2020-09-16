#include "stdafx.h"

extern SoundManager* g_theSoundManager;
extern NetWorkManager *g_NetworkManager;
extern Packet pk_Packet;
extern pkLobbyMessage pk_Lobby_Message;
extern pkLobby_RQ pk_Lobby_Request;
extern pkUser pk_User;




typedef std::basic_string<TCHAR> tstring;

TCHAR* StringToTCHAR(string& s)
{
	tstring tstr;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);
	return (TCHAR*)t;
}



LobbyScene::LobbyScene()
{

	pk_User.UserID = '\0';
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
	RoomMakeExitBtn = { 645, 315, 663, 333 };
	CrateRoomBtn = { 515, 475, 642, 510 } ;


	memset(pk_Lobby_Message.Buffer, '\0', 64 * sizeof(char));
	//pk_Lobby.User_Position = 100;
	
	m_ExitBtn_size = false;
	m_RoomBtn_size = false;
	m_CreateRoom = false;
	//LobbyUserCall();
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
	memset(NetWorkManager::GetInstance()->str2, 0, sizeof(TCHAR) * 256);
	memset(NetWorkManager::GetInstance()->str, 0, sizeof(TCHAR) * 256);
	NetWorkManager::GetInstance()->count = 0;
	NetWorkManager::GetInstance()->count2 = 0;

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

	RoomCreateDraw(hdc);
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
		m_CreateRoom = !m_CreateRoom;

		memset(NetWorkManager::GetInstance()->str2, 0, sizeof(TCHAR) * 256);
		memset(NetWorkManager::GetInstance()->str, 0, sizeof(TCHAR) * 256);
		NetWorkManager::GetInstance()->count = 0;
		NetWorkManager::GetInstance()->count2 = 0;
	}
	else if (Clickx >= RoomMakeExitBtn.left &&Clickx <= RoomMakeExitBtn.right
		&& Clicky >= RoomMakeExitBtn.top && Clicky <= RoomMakeExitBtn.bottom  &&m_CreateRoom)
	{
		m_CreateRoom = !m_CreateRoom;
		memset(NetWorkManager::GetInstance()->str2, 0, sizeof(TCHAR) * 256);
		memset(NetWorkManager::GetInstance()->str, 0, sizeof(TCHAR) * 256);
		NetWorkManager::GetInstance()->count = 0;
		NetWorkManager::GetInstance()->count2 = 0;
		
	}
	else if (Clickx >= CrateRoomBtn.left &&Clickx <= CrateRoomBtn.right
		&& Clicky >= CrateRoomBtn.top && Clicky <= CrateRoomBtn.bottom  &&m_CreateRoom)
	{

		if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
			return;

 		WideCharToMultiByte(CP_ACP, 0, NetWorkManager::GetInstance()->str2, 64, pk_Lobby_Request.RoomName, 64, NULL, NULL);
		pk_Packet.Protocal = LOBBYRQ;
		pk_Lobby_Request.RoomNum = 99;
		char temp[4] = {0};
		sprintf(temp, "%c", pk_Lobby_Request.RoomNum);
		pk_Packet.size = sizeof(TCHAR)*NetWorkManager::GetInstance()->count2 + 1 + sizeof(unsigned int);
		char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)+ pk_Packet.size];
		memset(buffer, 0, _msize(buffer));
		memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
		memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));
		memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int)], pk_Lobby_Request.RoomName,pk_Packet.size - sizeof(unsigned int));



		if (send(NetWorkManager::GetInstance()->server, buffer, _msize(buffer), 0) == -1)
		{
			exit(-1);
		}
		else
		{
			NetWorkManager::GetInstance()->count2 = 0;
			NetWorkManager::GetInstance()->str2[NetWorkManager::GetInstance()->count2] = NetWorkManager::GetInstance()->str2[1] = '\0';
		}

		GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::ROOM_SCENE);
		
	}
	else if (NetWorkManager::GetInstance()->LobbyRoom.size()>0)
	{
		for (int i = 0; i < NetWorkManager::GetInstance()->LobbyRoom.size(); i++)
		{
			if (Clickx >= 105 && Clickx <= 813 && Clicky >= 112 * (1 + i) && Clicky <= 200 * (1 + i))
			{

				if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
					return;

				pk_Packet.Protocal = ROOMRQ;
				pk_Packet.size = sizeof(unsigned int);

				char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];

				char temp[4] = { 0 };
				sprintf(temp, "%c", pk_Lobby_Request.RoomNum);

				memset(buffer, 0, _msize(buffer));
				memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
				memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
				memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));

				if (send(NetWorkManager::GetInstance()->server, buffer, _msize(buffer), 0) == -1)
				{
					exit(-1);
				}


				GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::ROOM_SCENE);
				break;

			}


		}
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

void LobbyScene::LobbyUserCall()
{
	/*pk_Packet.Protocal = USERLIST;
	char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pkUser)];
	memset(buffer, 0, _msize(buffer));
	memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
	memcpy(&buffer[sizeof(pk_Packet.Protocal)], pk_Lobby_Message.Buffer, sizeof(pkUser));
	if (send(NetWorkManager::GetInstance()->server, buffer, _msize(buffer), 0) == -1)
	{
		exit(-1);
	}
*/
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

	string temp;
	HFONT oldFont = (HFONT)SelectObject(hdc, GameCenter::GetInstance()->getUI()->TitleFont);
	for (int i = 0; i < NetWorkManager::GetInstance()->LobbyRoom.size(); i++)
	{
		Rectangle(hdc, 105, 112*(1+i), 813, 112*(2+i));
		temp = g_NetworkManager->LobbyRoom[i]->RoomNum + g_NetworkManager->LobbyRoom[i]->RoomName;
		TextOut(hdc, 140, 115 - (i * 20), StringToTCHAR(temp), _tcslen(StringToTCHAR(temp)));
	}
	
	SelectObject(hdc, oldFont);



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
	char msg[16];
	TCHAR szUniCode[32] = { 0, };
	memset(msg, 0, 16);
	//유저명단띄우기 하다가 포기
	for (int i = 0; i<g_NetworkManager->userList.size(); i++)
	{
		sprintf(msg, "%d", g_NetworkManager->userList[i]);
		MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, msg, strlen(msg), szUniCode, 32);

		TextOut(hdc, 950, 110 + (i * 20), szUniCode, _tcslen(szUniCode));

	}
	
	

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

void LobbyScene::RoomCreateDraw(HDC hdc)
{
	if (!m_CreateRoom)
	{
		return;
	}

	HBITMAP h01Bitmap;
	int bx, by;

	hBackGround = (HBITMAP)LoadImage(NULL, TEXT("IMG/RoomMakeUI.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBackGround, sizeof(BITMAP), &bitBackground);

	hBackDC = CreateCompatibleDC(hdc);
	h01Bitmap = (HBITMAP)SelectObject(hBackDC, hBackGround);

	bx = bitBackground.bmWidth;
	by = bitBackground.bmHeight;


	TransparentBlt(hdc, 270, 200, bx*2, by*2, hBackDC, 0, 0, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것

	//Rectangle(hdc, 645, 315, 663, 333);

	//Rectangle(hdc, 515, 475, 642, 510);
	
	HFONT oldFont = (HFONT)SelectObject(hdc, GameCenter::GetInstance()->getUI()->CommonFont);
	RECT charRect = { 450, 400, 1009, 450 };
	DrawText(hdc, NetWorkManager::GetInstance()->str2, _tcslen(NetWorkManager::GetInstance()->str2), &charRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
	SelectObject(hdc, oldFont);

	
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
	if (!m_CreateRoom)
	{
		if (wParam == VK_RETURN)
		{
			if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
				return;

			WideCharToMultiByte(CP_ACP, 0, NetWorkManager::GetInstance()->str, 64, pk_Lobby_Message.Buffer, 64, NULL, NULL);

			pk_Packet.Protocal = LOBBY_MESSAGE;
			pk_Packet.size = sizeof(TCHAR)*NetWorkManager::GetInstance()->count;
			char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];
			memset(buffer, 0, _msize(buffer));
			memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
			memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
			memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], pk_Lobby_Message.Buffer, pk_Packet.size);
		

			if (send(NetWorkManager::GetInstance()->server, buffer, _msize(buffer), 0) == -1)
			{
				exit(-1);
			}
			else
			{
				NetWorkManager::GetInstance()->count = 0;
				NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count] = NetWorkManager::GetInstance()->str[1] = '\0';
			}

		}
		else if (wParam == VK_BACK)
		{
			if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
				return;
			if (NetWorkManager::GetInstance()->count != 0)
				NetWorkManager::GetInstance()->str[--NetWorkManager::GetInstance()->count] = '\0';
		}
		else if (wParam != 0)
		{
			if (NetWorkManager::GetInstance()->count < 40)
			{
				NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count++] = (TCHAR)wParam;
				NetWorkManager::GetInstance()->str[NetWorkManager::GetInstance()->count] = '\0';
			}
		}
	}
	else
	{
			if (wParam == VK_RETURN)
			{
				if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
					return;

				WideCharToMultiByte(CP_ACP, 0, NetWorkManager::GetInstance()->str2, 64, pk_Lobby_Request.RoomName, 64, NULL, NULL);
				pk_Packet.Protocal = LOBBYRQ;
				pk_Lobby_Request.RoomNum = 99;
				char temp[4] = { 0 };
				sprintf(temp, "%c", pk_Lobby_Request.RoomNum);
				pk_Packet.size = sizeof(TCHAR)*NetWorkManager::GetInstance()->count2 + 1 + sizeof(unsigned int);
				char * buffer = new char[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + pk_Packet.size];
				memset(buffer, 0, _msize(buffer));
				memcpy(buffer, &pk_Packet.Protocal, sizeof(pk_Packet.Protocal));
				memcpy(&buffer[sizeof(pk_Packet.Protocal)], &pk_Packet.size, sizeof(pk_Packet.size));
				memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size)], temp, sizeof(unsigned int));
				memcpy(&buffer[sizeof(pk_Packet.Protocal) + sizeof(pk_Packet.size) + sizeof(unsigned int)], pk_Lobby_Request.RoomName, pk_Packet.size - sizeof(unsigned int));



				if (send(NetWorkManager::GetInstance()->server, buffer, _msize(buffer), 0) == -1)
				{
					exit(-1);
				}
				else
				{
					NetWorkManager::GetInstance()->count2 = 0;
					NetWorkManager::GetInstance()->str2[NetWorkManager::GetInstance()->count2] = NetWorkManager::GetInstance()->str2[1] = '\0';
				}

				GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::ROOM_SCENE);

			}
			else if (wParam == VK_BACK)
			{
				if (NetWorkManager::GetInstance()->server == INVALID_SOCKET)
					return;
				if (NetWorkManager::GetInstance()->count2 != 0)
					NetWorkManager::GetInstance()->str2[--NetWorkManager::GetInstance()->count2] = '\0';
			}
			else if (wParam != 0)
			{
				if (NetWorkManager::GetInstance()->count2 < 6)
				{
					NetWorkManager::GetInstance()->str2[NetWorkManager::GetInstance()->count2++] = (TCHAR)wParam;
					NetWorkManager::GetInstance()->str2[NetWorkManager::GetInstance()->count2] = '\0';
				}
			}


	}
}
