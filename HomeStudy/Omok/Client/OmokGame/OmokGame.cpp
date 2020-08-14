// OmokGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"


#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

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
	   CW_USEDEFAULT, 0, BLOCKSIZE*OMOKLINE +500, BLOCKSIZE*OMOKLINE + 120, nullptr, nullptr, hInstance, nullptr);

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
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc ;
	static GameCenter *Gamecenter = nullptr;
	static int delay;


	/*네트웤*/
	static WSADATA wsaData;
	static SOCKET server;
	static TCHAR str[100] = { 0 };
	static char buffer[100];
	static int count = 0;
	static SOCKADDR_IN addr = { 0 };
	static std::vector<TCHAR *> chatLog;
	static HBRUSH charRectBrush = CreateSolidBrush(RGB(40, 170, 220));
	static HBRUSH charRectTitleBrush = CreateSolidBrush(RGB(100, 250, 150));

	int msgLen = 0;


    switch (message)
    {
	case WM_CREATE:
		Gamecenter = GameCenter::GetInstance();
		Gamecenter->setHwnd(hWnd);
		delay = 0;
		SetTimer(hWnd, 1, 1000 / 30, NULL);
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		server = socket(AF_INET, SOCK_STREAM, 0);
		if (server == INVALID_SOCKET)
		{
			MessageBox(NULL, _T("socket faield"), _T("Error"), MB_OK);
			return 0;
		}

		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		if (connect(server, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("connect failed"), _T("Error"), MB_OK);
			return 0;
		}
		WSAAsyncSelect(server, hWnd, WM_ASYNC, FD_READ);
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_READ:
		{
			memset(buffer, 0, sizeof(buffer));
			msgLen = recv(server, buffer, 100, 0); //받아오는곳 
			buffer[msgLen] = NULL;
			size_t stlength = strlen(buffer);
			TCHAR * newMsg = new TCHAR[stlength + 1];
			sprintf(newMsg, TEXT("%s"), buffer);
			if (newMsg[0]=='_')
			{
				Gamecenter->setPlayer(newMsg[1]);
			}
			else
			{
				chatLog.push_back(newMsg);
			}
			
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		}
		break;
		
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            hdc = BeginPaint(hWnd, &ps);
			Gamecenter->Render(hWnd, hdc);

			//채팅부분 밑 
			SetBkMode(hdc, TRANSPARENT);
			
			size_t chatLogSize = chatLog.size();
		
			SelectObject(hdc, charRectTitleBrush);
			Rectangle(hdc, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH + 50, 0, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH + 450, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1) + 50);

			SelectObject(hdc, charRectBrush);
			Rectangle(hdc, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH + 50, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1), BLOCKSIZE*(OMOKLINE-1) + SUBWIDTH + 450, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1) + 50);
			RECT charRect = { 820, 750, 1100, 800 };

			for (size_t i = 0; i < chatLogSize; i++)
			{
				TextOut(hdc, 820, 720 - (i * 20), chatLog[chatLogSize - 1 - i], _tcslen(chatLog[chatLogSize - 1 - i]));
			}
			DrawText(hdc, str, _tcslen(str), &charRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
	{
		Gamecenter->Update(message, wParam, lParam);
			
		InvalidateRect(hWnd, NULL, true);
	}
	break;
	//case WM_MOUSEMOVE:
	//{
	//	Gamecenter->Update(message, wParam, lParam);
	//	InvalidateRect(hWnd, NULL, true);
	//}
	//break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			Gamecenter->Update(message, wParam, lParam);
			
		}
		break;
		}
	}
	break;
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			if (server == INVALID_SOCKET)
				return 0;
			else
			{
				strcpy_s(buffer, str);
				send(server, (LPSTR)buffer, strlen(buffer), 0);
				count = 0;
				str[count] = str[1] = '\0';
			}
		}
		else if (wParam == VK_BACK)
		{
			if (server == INVALID_SOCKET)
				return 0;
			if (count != 0)
				str[--count] = '\0';
		}
		else
		{
			if (count < 40)
			{
				str[count++] = (TCHAR)wParam;
				str[count] = '\0';
			}
		}
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
    case WM_DESTROY:
		KillTimer(hWnd, 1);
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
