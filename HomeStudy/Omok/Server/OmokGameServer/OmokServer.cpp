// OmokGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
static char boardState[19][19];




// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);



int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_OMOKGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_OMOKGAME));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_OMOKGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_OMOKGAME);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
	   CW_USEDEFAULT, 0, 400, 800, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//


bool OmokWin(int _x, int _y ,char _stone)
{
	int x = _x, y = _y, count = 0;

	//좌측,위쪽으로 모든걸 다몰아놓고 오른쪽으로가면서 카운트해보자.

	//가로 
	// x값만 감소시켜 stone과 다를때까지 감소
		while (boardState[_y][x - 1] == _stone && x > 0)
	    x--;
	// x값만 증가시켜 stone과 다를때까지 증가
		while (boardState[_y][x++] == _stone && x <= 18)
		    count++;

		if (count == 5)
		{
			return true;
		}
		x = _x, y = _y, count = 0;
	//세로 

		while (boardState[y-1][_x] == _stone && y > 0)
			y--;

		while (boardState[y++][_x] == _stone && y <= 18)
			count++;

		if (count == 5)
		{
			return true;
		}
		x = _x, y = _y, count = 0;
	//우측대각
		while (boardState[y + 1][x-1] == _stone && y <= 18 && x > 0 )
		{
			y++;
			x--;
		}
			
		while (boardState[y--][x++] == _stone && y >0 && x <= 18)
			count++;

		if (count == 5)
		{
			return true;
		}
		x = _x, y = _y, count = 0;

	//좌측대각 
		while (boardState[y - 1][x - 1] == _stone && y > 0 && x > 0)
		{
			y--;
			x--;
		}

		while (boardState[y++][x++] == _stone && y <= 18 && x <= 18)
			count++;

		if (count == 5)
		{
			return true;
		}
	

	return false;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc ;
	//static GameCenter *Gamecenter = nullptr;
	//static int delay;
	static WSADATA wsaData;
	static SOCKET server;
	static vector<SOCKET> clientList;
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static TCHAR msg[1024];
	static int count;
	static TCHAR str[1024];
	static char buffer[1024];
	int position[3];
	int size, msgLen;
	bool bFlag = true;
	static bool gameover = false;
	
	//static vector<POINT> playerOne;
	//static vector<POINT> playerTwo;



	switch (message)
	{
	case WM_CREATE:
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		server = socket(AF_INET, SOCK_STREAM, NULL);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		memset(msg, 0, 300);
		if (bind(server, (LPSOCKADDR)& addr, sizeof(addr)) == -1)
		{
			MessageBox(NULL, _T("bind failed"), _T("Error"), MB_OK);
			return 0;
		}
		WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_ACCEPT);
		if (listen(server, 5) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("listen failed"), _T("Error"), MB_OK);
			return 0;
		}
		memset(boardState, 'a', sizeof(boardState));
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			clientList.push_back(accept(server, (LPSOCKADDR)&c_addr, &size));
			WSAAsyncSelect(clientList.back(), hWnd, WM_ASYNC, FD_READ | FD_CLOSE);
		
			if (clientList.size() == 2 && bFlag)
			{
				send(clientList[0], "_bt", _tcslen("_bt"), NULL);
				send(clientList[1], "_w", _tcslen("_w"), NULL);
				bFlag = false;
			}
			else
			{
				wsprintf(msg, "%s %d", "Your Number is", clientList.back());
				send(clientList.back(), msg, _tcslen(msg), NULL);
			}
			break;
		case FD_READ:
		{
				msgLen = recv(wParam, buffer, 100, 0);
				buffer[msgLen] = NULL;
				if (buffer[0] == '(' && buffer[1] == 't')
				{

					if (wParam == clientList[0])
					{
						send(clientList[1], "(t", _tcslen("(t"), NULL);
					}
					else
					{
						send(clientList[0], "(t", _tcslen("(t"), NULL);
					}
				}
				else if(buffer[0] =='-')
				{
					buffer[0] = ' ';
					wsprintf(msg, "%d :%s", wParam, buffer);
					for (SOCKET client : clientList)
					{
						send(client, msg, _tcslen(msg), NULL);
					}
				}
				else
				{
					position[0] = atoi(buffer);
					position[1] = position[0] % 1000; //y좌표
					position[2] = (position[0] - position[1]) / 1000; //x좌표

					/*if (!gameover)
					{*/
						if (wParam == clientList[0])
						{
							for (SOCKET client : clientList)
							{
								send(client, (LPSTR)buffer, strlen(buffer), 0);
							}
							//	send(clientList[1], (LPSTR)buffer, strlen(buffer), 0);
							boardState[position[1]][position[2]] = 'b';
						}
						else
						{
							for (SOCKET client : clientList)
							{
								send(client, (LPSTR)buffer, strlen(buffer), 0);
							}
							//send(clientList[0], (LPSTR)buffer, strlen(buffer), 0);
							boardState[position[1]][position[2]] = 'w';
						}
					
						

						if (OmokWin(position[2], position[1], 'w'))
						{
							wsprintf(msg, "%d :%s", wParam, "Win");
							for (SOCKET client : clientList)
							{
								send(client, msg, _tcslen(msg), NULL);
							}
							gameover = true;

						}
						else if (OmokWin(position[2], position[1], 'b'))
						{

				
							wsprintf(msg, "%d :%s", wParam, "Win");
							for (SOCKET client : clientList)
							{
								send(client, msg, _tcslen(msg), NULL);
							}
							gameover = true;


						}

					/*}*/
				


			}

			InvalidateRect(hWnd, NULL, TRUE);
		}
			break;
		case FD_CLOSE:
			for (auto it = clientList.begin(); it != clientList.end(); it++)
			{
				if ((*it) == wParam)
				{
					wsprintf(msg, "%d %s", wParam, "user exit");
					closesocket(*it);
					clientList.erase(it);
					break;
				}
			}
			for (SOCKET client : clientList)
			{
				send(client, msg, _tcslen(msg), NULL);
			}
			break;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);
		// TODO: Add any drawing code that uses hdc here...
		if (_tcscmp(msg, _T("")))
			TextOut(hdc, 0, 30, msg, (int)_tcslen(msg));	
		TextOut(hdc, 0, 0, str, _tcslen(str));
		EndPaint(hWnd, &ps);
	}
	break;
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			if (clientList.size() == 0)
				return 0;
			if (clientList.back() == INVALID_SOCKET)
				return 0;
			else
			{
				strcpy_s(buffer, str);
				send(clientList.back(), (LPSTR)buffer, strlen(buffer) + 1, 0);
				count = 0;
				return 0;
			}
		}
		if (wParam == VK_BACK)
		{
			if (clientList.back() == INVALID_SOCKET)
				return 0;
			if (count != 0)
				str[--count] = '\0';
		}
		else
		{
			str[count++] = (TCHAR)wParam;
			str[count] = '\0';
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_DESTROY:
		closesocket(server);
		WSACleanup();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
