// TetrisPrj.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "TetrisPrj.h"

#define MAX_LOADSTRING 100


// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
//extern NetWorkManager *g_NetworkManager;
extern SoundManager* g_theSoundManager;

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
    LoadStringW(hInstance, IDC_TETRISPRJ, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TETRISPRJ));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= 0;
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON));

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
      300, 30, 1150, 905, nullptr, nullptr, hInstance, nullptr);

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
	static GameCenter *Gamecenter = nullptr;
    switch (message)
    {
	case WM_CREATE:
		srand(time(NULL));



		if (g_theSoundManager == nullptr)
		{
			g_theSoundManager = new SoundManager();
			g_theSoundManager->AddBGM("sound/bgm.mp3");
			g_theSoundManager->AddSFX("sound/effBBam.mp3", "BBam");
			g_theSoundManager->AddSFX("sound/effMelem.mp3", "Melem");
			g_theSoundManager->AddSFX("sound/effSelect.mp3", "Select");
		}
		g_theSoundManager->PlayBGM();
		Gamecenter = GameCenter::GetInstance();
		//g_NetworkManager = NetWorkManager::GetInstance();
		
		Gamecenter->setHwnd(hWnd);
		Gamecenter->setHInstance(hInst);
		SetTimer(hWnd, 1, 1000/30 , NULL);
		
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
			HDC hdc = BeginPaint(hWnd, &ps);

			HDC back;
			back = CreateCompatibleDC(hdc);
			HBITMAP backHBIT = CreateCompatibleBitmap(hdc, ps.rcPaint.right - ps.rcPaint.left, ps.rcPaint.bottom - ps.rcPaint.top);
			SelectObject(back, backHBIT);
			
			SetBkMode(back, TRANSPARENT); //글자배경색 투명으로만듬
			Gamecenter->Render(hWnd, back);

			BitBlt(hdc, 0, 0, ps.rcPaint.right, ps.rcPaint.bottom, back, 0, 0, SRCCOPY);
			DeleteDC(back);
			DeleteObject(backHBIT);



			EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
		{
			int time = GetTickCount();

			if (Gamecenter->getMoveTime() + MOVE_DELAY < time)
			{
				Gamecenter->setMoveTime(time);

				Gamecenter->Update(message, wParam, lParam);
				InvalidateRgn(hWnd, NULL, false);
			}
		}
		break;
	case WM_LBUTTONDOWN:
		{
			Gamecenter->Update(message, wParam, lParam);
			InvalidateRgn(hWnd, NULL, false);
		}
		break;
	case WM_MOUSEMOVE:
		{
			if (Gamecenter->getScene() == GameCenter::Scene_enum::LOGIN_SCENE ||
				Gamecenter->getScene() == GameCenter::Scene_enum::LOCALGAME_SCENE||
				Gamecenter->getScene() == GameCenter::Scene_enum::LOBBY_SCENE)
			{
				Gamecenter->Update(message, wParam, lParam);
			}
		}
		break;
	case WM_TIMER:
	{
		switch (wParam)
		{
		case 1:
		{
			Gamecenter->Update(message, wParam, lParam);
			InvalidateRgn(hWnd, NULL, false);
		}
		break;
		}
	}
	break;
    case WM_DESTROY:
		g_theSoundManager->Stop();
		delete g_theSoundManager;
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
