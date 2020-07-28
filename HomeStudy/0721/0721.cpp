// 0721.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0721.h"
#include <math.h>
#include <commdlg.h>
#include <cstdio>
#pragma comment(lib,"msimg32.lib")

#define MAX_LOADSTRING 100
#define PI 3.14159
const int Sprite_size_x = 32;
const int sprite_size_y = 32;
int		Run_Frame_max = 0;
int		Run_Frame_min = 0;
int		cur_Frame = Run_Frame_min;
int		moveX = 100;
int		moveY = 100;
int		Position;

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HBITMAP hBackImage;
BITMAP bitBack;

//2��°
HBITMAP hTransParentImage;
BITMAP bitTransparent;

//3����
HBITMAP hAniImage;
BITMAP bitAni;
void updateFrame(HWND hwnd);


RECT rectView;
void DrawRectText(HDC hdc);

HBITMAP HDoubleBufferImage;
void DrawBitMapDoubleBuffering(HWND hWnd, HDC hdc);

void CreateBitmap();
void DrawBitmap(HWND hWnd, HDC hdc);
void DeleteBitmap();


VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);
VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime);

TCHAR sKeyState[128];

void DrawStar(HDC hdc,int PositionX,int PositionY,int dSize)
{
	int x = PositionX;
	int y = PositionY;
	int r = dSize;
	POINT starPoint[10];
	//MoveToEx(hdc, x, y, NULL); //������ �Ű��ִ� �Լ���.

	for (int i = 0; i < 9; i += 2)
	{
		starPoint[i].x = x + (r * sin(72 * (i / 2) * PI / 180));
		starPoint[i].y = y - (r * cos(72 * (i / 2) * PI / 180));
	}

	float a = starPoint[0].y - starPoint[4].y;
	float b = -(starPoint[0].x - starPoint[4].x);
	float c = starPoint[2].y - starPoint[8].y;
	float d = -(starPoint[2].x - starPoint[8].x);
	float e = a * starPoint[0].x + b * starPoint[0].y;
	float f = c * starPoint[2].x + d * starPoint[2].y;

	starPoint[1].x = (e*d - b*f) / (a*d - b*c);
	starPoint[1].y = (a*f - e*c) / (a*d - b*c);

	double r2 = pow(pow(x - starPoint[1].x, 2) + pow(y - starPoint[1].y, 2), 0.5);

	for (int i = 3; i < 10; i += 2)
	{
		starPoint[i].x = x + (r2 * sin((72 * (i / 2) + 36) * PI / 180));
		starPoint[i].y = y - (r2 * cos((72 * (i / 2) + 36) * PI / 180));
	}
	Polygon(hdc, starPoint, 10);

}

void OutFromFile(TCHAR filename[], HWND hWnd)
{
	FILE *fPtr;
	HDC hdc;
	int line;
	TCHAR buffer[500];
	line = 0;
	hdc = GetDC(hWnd);
#ifdef _UNICODE
	_tfopen_s(&fPtr, filename, _T("r, ccs = UNICODE"));
#else
	_tfopen_s(&fPtr, filename, _T("r"));
#endif
	while (_fgetts(buffer, 100, fPtr) != NULL)
	{
		if (buffer[_tcslen(buffer) - 1] == _T('\n'))
			buffer[_tcslen(buffer) - 1] = NULL;
		TextOut(hdc, 0, line * 20, buffer, _tcslen(buffer));
		line++;
	}
	fclose(fPtr);
	ReleaseDC(hWnd, hdc);
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
    LoadStringW(hInstance, IDC_MY0721, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0721));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0721));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0721);
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
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

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
	static bool Selection;
	static bool shape[3];
	static int mx, my;

	CHOOSECOLOR COLOR;
	static COLORREF tmp[16], color;
	HBRUSH hBrush, OldBrush;
	int i;

	OPENFILENAME OFN;
	TCHAR str[100], lpstrFile[100] = _T("");//�޾ƿ��°�
	TCHAR filter[] = _T("Every File(*.*) \0*.*\0Text File\0*.txt;*.doc\0");//� Ȯ���ڸ� ������ �����ϴ°�

	
	static HMENU hMenu, hSubMenu;
    switch (message)
    {
	case WM_CREATE:
		{
		//Selection = false;
		//shape[0] = false;
		//shape[1] = false;
		//shape[2] = false;

		//hMenu = GetMenu(hWnd);
		//hSubMenu = GetSubMenu(hMenu, 2);
		//EnableMenuItem(hSubMenu, ID_DRAW_CIRCLE, MF_GRAYED);
		//EnableMenuItem(hSubMenu, ID_DRAW_RECT, MF_GRAYED);
		//EnableMenuItem(hSubMenu, ID_DRAW_STAR, MF_GRAYED);
		CreateBitmap();
		//SetTimer(hWnd, 123, 100, NULL);
		SetTimer(hWnd, 123, 100, AniProc);
		SetTimer(hWnd, 111, 100, KeyStateProc);

		GetClientRect(hWnd, &rectView);
		}
		break;
	//case WM_TIMER:
	//	{
	//	updateFrame(hWnd);
	//	InvalidateRgn(hWnd, NULL, false); // false�� �κ������� �����ϴµ� true�� ��ü������ �����Ѵ�.
	//	}
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
			case ID_DRAW_CIRCLE:
				{
					MessageBox(NULL, L"CIRCLE", L"Draw", MB_OK);
					shape[0] = true;
					shape[1] = false;
					shape[2] = false;
				}
				break;
			case ID_DRAW_STAR:
				{
					MessageBox(NULL, L"STAR", L"Draw", MB_OK);
					shape[1] = true;
					shape[0] = false;
					shape[2] = false;
				}
				break;
			case ID_DRAW_RECT:
				{
					MessageBox(NULL, L"Rect", L"Draw", MB_OK);
					shape[2] = true;
					shape[1] = false;
					shape[0] = false;
				}
				break;
			case ID_FILEOPEN:				
				{
					memset(&OFN, 0, sizeof(OPENFILENAME));
					OFN.lStructSize = sizeof(OPENFILENAME);
					OFN.hwndOwner = hWnd;
					OFN.lpstrFilter = filter;
					OFN.lpstrFile = lpstrFile;
					OFN.nMaxFile = 100; //��� ������ �Ѳ����� ó���Ұ����� .
					OFN.lpstrInitialDir = _T(".");
					//if (GetOpenFileName(&OFN) != 0)
					//{
					//	_stprintf_s(str, _T("%s ������ ���ڽ��ϱ�?"), OFN.lpstrFile);
					//	MessageBox(hWnd,str,_T("���� ����"),MB_OK);
					//}
					if (GetOpenFileName(&OFN) != 0)
						OutFromFile(OFN.lpstrFile, hWnd);
					break;
				}
				break;
			case ID_COLORDLG:
				{
					for (i = 0; i < 16; i++)
						tmp[i] = RGB(rand() % 256, rand() % 256, rand() % 256);
					memset(&COLOR, 0, sizeof(CHOOSECOLOR));
					COLOR.lStructSize = sizeof(CHOOSECOLOR);
					COLOR.hwndOwner = hWnd;
					COLOR.lpCustColors = tmp;
					COLOR.Flags = CC_FULLOPEN;
					if (ChooseColor(&COLOR) != 0)
					{
						color = COLOR.rgbResult;
						InvalidateRgn(hWnd, NULL, TRUE);
					}
					break;
				}				
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
			/*hBrush = CreateSolidBrush(color);
			OldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			if (Selection)
			{
				if (shape[0])
				{
					Ellipse(hdc, mx - 50, my - 50, mx + 50, my + 50);
				}
				else if (shape[1])
				{
					DrawStar(hdc, mx, my, 50);
				}
				else if (shape[2])
				{
					Rectangle(hdc, mx - 50, my - 50, mx + 50, my + 50);
				}
			}
		
	
			SelectObject(hdc, OldBrush);
			DeleteObject(hBrush);*/
		//	DrawBitmap(hWnd, hdc);
			DrawBitMapDoubleBuffering(hWnd, hdc);
			DrawRectText(hdc);

            EndPaint(hWnd, &ps);
        }
        break;
	case WM_LBUTTONDOWN:
		{
		mx = LOWORD(lParam);
		my = HIWORD(lParam);
		Selection = true;
		InvalidateRgn(hWnd, NULL, TRUE);
		}
		break;
	case WM_LBUTTONUP:
		{
		Selection = false;
		InvalidateRgn(hWnd, NULL, TRUE);

		}
		break;

    case WM_DESTROY:
		DeleteBitmap();
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



//�̹����� �����´� . ../kungfu.bmp ..�� ����������(������) 
void CreateBitmap()
{
	//1 �̹�������
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/����.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}
	//2 ��ũ�� �������¹�
	{
		hTransParentImage = (HBITMAP)LoadImage(NULL, TEXT("images/sigong.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hTransParentImage, sizeof(BITMAP), &bitTransparent);
	}
	//�̹��� �����̱�
	{
		hAniImage = (HBITMAP)LoadImage(NULL, TEXT("images/character.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hAniImage, sizeof(BITMAP), &bitAni);
		//�ϴܿ������θ��޸��Ŵϱ�
		Run_Frame_max = bitAni.bmWidth / Sprite_size_x - 1;
		Run_Frame_min = 0;
		cur_Frame = Run_Frame_min;

	}

}

//������  hMemDC = CreateCompatibleDC(hdc); �Ȱ��̸����

void DrawBitmap(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP h01Bitmap;
	int bx, by;
	//1���� �׸��ֱ�
	{
		hMemDC = CreateCompatibleDC(hdc); //�Ȱ��̸����
		h01Bitmap = (HBITMAP)SelectObject(hMemDC, hBackImage); //�׷��ִ°ž�
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hdc, 0, 0, bx, by, hMemDC, 0, 0, SRCCOPY); //���ڸ��� �ٷα׷���
		SelectObject(hMemDC, h01Bitmap);
		DeleteDC(hMemDC);
	}
	//2��°�� �������
	{
		hMemDC = CreateCompatibleDC(hdc); //�Ȱ��̸����
		h01Bitmap = (HBITMAP)SelectObject(hMemDC, hTransParentImage); //�׷��ִ°ž�
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		BitBlt(hdc, 100, 100, bx, by, hMemDC, 0, 0, SRCCOPY); // �̰��Ϲݱ׸���
		TransparentBlt(hdc, 200, 100, bx, by, hMemDC, 0, 0, bx, by, RGB(255, 0, 255));//��ȫ���� �����ϰ� ������Ѵ�.
		SelectObject(hMemDC, h01Bitmap);
		DeleteDC(hMemDC);
	}
	//3��° �ִϸ��̼�
	{
		hMemDC = CreateCompatibleDC(hdc); //�Ȱ��̸����
		h01Bitmap = (HBITMAP)SelectObject(hMemDC, hAniImage); //�׷��ִ°ž�
		bx = bitAni.bmWidth / 16; //�̹��� ������ ���η� 16��
		by = bitAni.bmHeight / 2; //���η� 2��
		
		int xStart = cur_Frame * bx;
		int yStart = 0;
		TransparentBlt(hdc, 100, 100, bx, by, hMemDC, xStart, yStart, bx, by, RGB(255, 0, 255));//
		SelectObject(hMemDC, h01Bitmap);
		DeleteDC(hMemDC);
	}
	

}


void DrawBitMapDoubleBuffering(HWND hWnd, HDC hdc)
{
	HDC hMemDC;
	HBITMAP h01Bitmap;
	int bx, by;



	HDC hMemDC2;
	HBITMAP h01Bitmap2;

	hMemDC = CreateCompatibleDC(hdc);

	if (HDoubleBufferImage == NULL)
	{
		HDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //ȭ�鿵����ŭ �������
		
	}
	h01Bitmap = (HBITMAP)SelectObject(hMemDC, HDoubleBufferImage); //ȭ�鿵��ũ�⸸ŭ �׷���.
	//1���� �׸��ֱ�
	{
		hMemDC2 = CreateCompatibleDC(hMemDC); //�Ȱ��̸����
		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage); //�׷��ִ°ž�
		bx = bitBack.bmWidth;
		by = bitBack.bmHeight;

		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY); //��濡 �̸��׷���.

		SelectObject(hMemDC2, h01Bitmap2);
		DeleteDC(hMemDC2);
	}
	//2��°�� �������
	{
		hMemDC2 = CreateCompatibleDC(hMemDC); //�Ȱ��̸����
		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransParentImage); //�׷��ִ°ž�
		bx = bitTransparent.bmWidth;
		by = bitTransparent.bmHeight;

		BitBlt(hMemDC, 100, 100, bx, by, hMemDC2, 0, 0, SRCCOPY); // �̰��Ϲݱ׸���
		TransparentBlt(hMemDC, 200, 100, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));//��ȫ���� �����ϰ� ������Ѵ�.
		SelectObject(hMemDC2, h01Bitmap2);
		DeleteDC(hMemDC2);
	}
	//3��° �ִϸ��̼�
	{
		hMemDC2 = CreateCompatibleDC(hMemDC); //�Ȱ��̸����
		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage); //�׷��ִ°ž�
		

		bx = bitAni.bmWidth / 6; //�̹��� ������ ���η� 6��
		by = bitAni.bmHeight / 8; //���η� 2��

		int xStart = cur_Frame * bx;
		int yStart = Position *by;

		TransparentBlt(hMemDC, moveX, moveY, bx*4, by*4, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 �� 4���Ѱ�.
		SelectObject(hMemDC2, h01Bitmap2);
		DeleteDC(hMemDC2);
	}
	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, h01Bitmap);



}


void DeleteBitmap()
{
	DeleteObject(hBackImage);
	DeleteObject(hTransParentImage);
}

void DrawRectText(HDC hdc)
{
	static int xPos = 0;
	TCHAR strTest[] = _T("�ؽ�Ʈ ���");
	TextOut(hdc, xPos, 10, strTest, _tcslen(strTest));
	
	TextOut(hdc, 100, 10, sKeyState, _tcslen(sKeyState));


	xPos += 5;
	if (xPos > rectView.right) xPos = 0;
}

VOID CALLBACK AniProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	updateFrame(hWnd);
	InvalidateRgn(hWnd, NULL, false);
	return;
}

VOID CALLBACK KeyStateProc(HWND hWnd, UINT uMsg, UINT idEvent, DWORD dwTime)
{
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		moveX += 10;
		Position = 2;
		if (GetKeyState(VK_UP) & 0x8000)
		{
			moveY -= 10;
			Position = 7;
		}

		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			moveY += 10;
			Position = 5;
		}

	
	}
	else if (GetKeyState(VK_LEFT) & 0x8000)
	{
		moveX -= 10;
		Position = 1;
		if (GetKeyState(VK_UP) & 0x8000)
		{
			moveY -= 10;
			Position = 6;
		}

		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			moveY += 10;
			Position = 4;
		}

	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		moveY -= 10;
		Position = 3;
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		moveY += 10;
		Position = 0;
	}

}



void updateFrame(HWND hwnd)
{
	cur_Frame++;
	cur_Frame %= (Run_Frame_max - Run_Frame_min);
	cur_Frame += Run_Frame_min;

	
}