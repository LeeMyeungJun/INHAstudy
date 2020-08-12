// win32Server.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "win32Server.h"
#include <WinSock2.h>
#include <stdio.h>
#include <vector>
using namespace std;
#pragma comment(lib,"ws2_32.lib")

#define WM_ASYNC	WM_USER+2
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


//int WinServer();
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


std::string TCHARToString(const TCHAR* ptsz)
{
	int len = wcslen((wchar_t*)ptsz);
	char* psz = new char[2 * len + 1];
	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;
	delete[] psz;
	return s;
}


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
    LoadStringW(hInstance, IDC_WIN32SERVER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WIN32SERVER));


	//return WinServer();
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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WIN32SERVER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_WIN32SERVER);
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
	   400, 200, 600, 600, nullptr, nullptr, hInstance, nullptr);

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
	HDC hdc;
	PAINTSTRUCT ps;
	static WSADATA	wsadata;
	static SOCKET	s, cs;
	static TCHAR	msg[200];
	static char		buffer[100];
	static SOCKADDR_IN addr = { 0 }, c_addr;
	static TCHAR str[100];
	static int count;
	int	size, msgLen;
	string name;

	static vector<string> temp;

    switch (message)
    {
	case WM_CREATE:
		WSAStartup(MAKEWORD(2, 2), &wsadata);
		s = socket(AF_INET, SOCK_STREAM, 0);
		addr.sin_family = AF_INET;
		addr.sin_port = 20;
		addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
		if (bind(s, (LPSOCKADDR)& addr, sizeof(addr)))
		{
			MessageBox(NULL, _T("binding faild"), _T("ERROR"), MB_OK);
			return 0;
		}
		else
		{
			MessageBox(NULL, _T("binding success"), _T("Success"), MB_OK);
		}
		WSAAsyncSelect(s, hWnd, WM_ASYNC, FD_ACCEPT);
		//bind >> listen
		if (listen(s, 5) == SOCKET_ERROR)
		{
			MessageBox(NULL, _T("listen faild"), _T("ERROR"), MB_OK);
			return 0;
		}
		else
		{
			MessageBox(NULL, _T("listen success"), _T("Success"), MB_OK);
		}
		break;
	case WM_ASYNC:
		switch (lParam)
		{
		case FD_ACCEPT:
			size = sizeof(c_addr);
			cs = accept(s, (LPSOCKADDR)&c_addr,&size);
			WSAAsyncSelect(cs, hWnd, WM_ASYNC, FD_READ);

			break;
		case FD_READ:
			msgLen = recv(cs, buffer, 100, 0);
			buffer[msgLen] = NULL;
#ifdef _UNICODE
			msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), NULL, NULL);
			
			MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), msg, msgLen);
			name = "Client : " + TCHARToString(msg);
			temp.push_back(name);
			if (temp.size() >= 10)
			{
				temp.erase(temp.begin());
			}
			InvalidateRgn(hWnd, NULL, TRUE);
			msg[msgLen] = NULL;
#else
			strcpy_s(msg, buffer);
#endif
			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		default:
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
            hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
			//if(_tcscmp(msg,_T("")))
			//	TextOut(hdc, 0, 30, msg, (int)_tcslen(msg)); //상대의것 
			TextOut(hdc, 0, 0, str, (int)_tcslen(str));

			for (int i = 0; i < temp.size(); i++)
			{
				TextOut(hdc, 0, 100+50*i, StringToTCHAR(temp[i]), (int)_tcslen(StringToTCHAR(temp[i])));	
			}

            EndPaint(hWnd, &ps);
        } 
        break;
	case WM_CHAR:
		if (wParam == VK_RETURN)
		{
			name = "Server : " + TCHARToString(str);
			temp.push_back(name);
			if (temp.size() >= 10)
			{
				temp.erase(temp.begin());
			}
			//temp.push_back(TCHARToString(str));
			if (cs == INVALID_SOCKET)
				return 0;
			else
			{
#ifdef _UNICODE
				msgLen = WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL);
				WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, msgLen, NULL, NULL);
#else
				strcpy_s(buffer, str);
#endif
				send(cs, (LPSTR)buffer, strlen(buffer) + 1, 0);

				
				InvalidateRect(hWnd, NULL, TRUE);
				count = 0;
				return 0;
			}
		}
		else if (wParam == VK_BACK &&count > 0)
		{
			count--;
			InvalidateRgn(hWnd, NULL, TRUE);
		}
		else
		{
			str[count++] = wParam;
			
		}
		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE);
		return 0;

	break;
    case WM_DESTROY:
		closesocket(s);
		WSACleanup();
        PostQuitMessage(0);
        break;
       
    }
	return DefWindowProc(hWnd, message, wParam, lParam);
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

int WinServer()
{
	WSADATA wsadata;
	SOCKET s;

	TCHAR message[300];
	
	SOCKADDR_IN addr = { 0 };

	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	addr.sin_family = AF_INET;
	addr.sin_port = 20;
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	if (bind(s, (LPSOCKADDR)& addr, sizeof(addr)))
	{
		MessageBox(NULL, _T("binding faild"), _T("ERROR"), MB_OK);
		return 0;
	}
	else
	{
		MessageBox(NULL, _T("binding success"), _T("Success"), MB_OK);
	}

	//bind >> listen
	if (listen(s, 5) == SOCKET_ERROR)
	{
		MessageBox(NULL, _T("listen faild"), _T("ERROR"), MB_OK);
		return 0;
	}
	else
	{
		MessageBox(NULL, _T("listen success"), _T("Success"), MB_OK);
	}

	// ------
	do
	{
		SOCKADDR_IN c_addr;
		char buffer[100];
#ifdef _UNICODE
		TCHAR	wbuffer[100];
#endif
		int		msgLen;
		int		size = sizeof(c_addr);
		SOCKET cs = accept(s, (LPSOCKADDR)&c_addr, &size);
		msgLen = recv(cs, buffer, 100, 0);

		buffer[msgLen] = NULL;
#ifdef _UNICODE
		msgLen = MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer),NULL,NULL);
		MultiByteToWideChar(CP_ACP, 0, buffer, strlen(buffer), wbuffer, msgLen);
		wbuffer[msgLen] = NULL;
		_stprintf_s(message, _T("클라이언트 메시지 : %s , 서버를 종료하시겠습니까?"), wbuffer);
#else
		sprintf_s(message, _T("클라이언트 메시지 : %s , 서버를 종료하시겠습니까?"), buffer);
#endif

	} while (MessageBox(NULL, message,_T("Server 메시지 "),MB_YESNO)==IDNO);

	//----------



	//do
	//{
	//	SOCKADDR_IN c_addr;
	//	int size = sizeof(c_addr);
	//	accept(s, (LPSOCKADDR)& c_addr, &size);
	//} while (MessageBox(NULL, _T("클라이언트 접속 확인 \n서버를 종료하시겠습니까?"), _T("Server 메시지"), MB_YESNO) == IDNO);
	//
	closesocket(s);
	WSACleanup();

	return 1;
}
