// 0812_WinApi_Client.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0812_WinApi_Client.h"
#include <WinSock2.h>
#include <string>
#include <vector>
#pragma comment(lib, "ws2_32.lib")
#define MAX_LOADSTRING 100
#define WM_ASYNC WM_USER + 2
#define WINDOW_WIDTH 300
#define WINDOW_HEIGHT 600
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);


int WinClient();

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
	LoadStringW(hInstance, IDC_MY0812_WINAPI_CLIENT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0812_WINAPI_CLIENT));

	MSG msg;
	//WinClient();
	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
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

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0812_WINAPI_CLIENT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(NULL);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
		CW_USEDEFAULT, 0, WINDOW_WIDTH + 16, WINDOW_HEIGHT + 39, nullptr, nullptr, hInstance, nullptr);

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
	using namespace std;
	static WSADATA wsaData;
	static SOCKET server;
	static TCHAR str[100] = { 0 };
	static char buffer[100];
	static int count = 0;
	static SOCKADDR_IN addr = { 0 };
	static std::vector<TCHAR *> chatLog;
	static HBRUSH charRectBrush = CreateSolidBrush(RGB(40, 170, 220));
	int msgLen = 0;
	switch (message)
	{
	case WM_CREATE:
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
			msgLen = recv(server, buffer, 100, 0);
			buffer[msgLen] = NULL;
			size_t stlength = strlen(buffer);
			TCHAR * newMsg = new TCHAR[stlength + 1];
			sprintf(newMsg, TEXT("%s"), buffer);
			chatLog.push_back(newMsg);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
		}
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps); 
		SetBkMode(hdc, TRANSPARENT);
		SelectObject(hdc, charRectBrush);
		size_t chatLogSize = chatLog.size();
		for (size_t i = 0; i < chatLogSize; i++)
		{
			TextOut(hdc, 10, 520 - (i * 20), chatLog[chatLogSize - 1 - i], _tcslen(chatLog[chatLogSize - 1 - i]));
		}
		Rectangle(hdc, 0, 550, 300, 600);
		RECT charRect = { 20, 550, 300, 600 };
		DrawText(hdc, str, _tcslen(str), &charRect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		// TODO: Add any drawing code that uses hdc here...
		EndPaint(hWnd, &ps);
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
		closesocket(server);
		WSACleanup();
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

