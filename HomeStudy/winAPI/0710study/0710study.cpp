// 0710study.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "0710study.h"
#include <tchar.h>
#include <math.h>
#include <stdlib.h>


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

double getRadian(int num)
{
	return num*(3.1415926535897 / 180);
}

double CrossX(double x1,double y1,double x2,double y2 ,double x3 ,double y3,double x4, double y4)
{

	double a, b, c, d, e, f;
	double x, y;

	a = y1 - y2;
	b = -(x1 - x2);
	c = y3 - y4;
	d = -(x3 - x4);
	e = a*x1 + b*y1;
	f = c*x3 + d*y3;

	x = ((e*d - b*f)) / ((a*d - b*c));
	y = ((a*f - e*c)) / ((a	*d - b*c));

	if (fabs(x) != INFINITY && fabs(y) != INFINITY)
		return x;
	else
		return -1;

	return -1;
}

double CrossY(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{

	double a, b, c, d, e, f;
	double x, y;

	a = y1 - y2;
	b = -(x1 - x2);
	c = y3 - y4;
	d = -(x3 - x4);
	e = a*x1 + b*y1;
	f = c*x3 + d*y3;

	x = ((e*d - b*f)) / ((a*d - b*c));
	y = ((a*f - e*c)) / ((a	*d - b*c));

	if (fabs(x) != INFINITY && fabs(y) != INFINITY)
		return y;
	else
		return -1;

	return -1;
}

void DrawGrid(HDC hdc, int xStart, int yStart, int xEnd, int yEnd, int lineThickness)
{
	//hdc 100 100 500 500 50
	int iCount = xEnd - xStart;

	//가운데 세로줄
	for (int i = 0; i <=iCount/lineThickness;i++ )
	{
		MoveToEx(hdc, xStart +lineThickness*i, yStart, NULL);
		LineTo(hdc, xStart + lineThickness*i, yEnd);
	}

	//가운데 가로줄
	for (int i = 0; i <= iCount / lineThickness; i++)
	{
		MoveToEx(hdc, xStart, yStart + lineThickness*i, NULL);
		LineTo(hdc, xEnd, yStart + lineThickness*i);
	}

}

void DrawCircle(HDC hdc, int centerX, int centerY, int r)
{
	//int smallr = (tan(15)*r) / (1 - tan(15));
	////rx ry는 반지름 
	Ellipse(hdc, centerX-r, centerY-r, centerX+r, centerY+r);

	//int smallCenter = centerX + r + smallr;
	//Ellipse(hdc, smallCenter - smallr, smallCenter - smallr, smallCenter + smallr, smallCenter + smallr);
}

void DrawStar(HDC hdc, double x, double y, double r)
{
	double PointX[10] = {x,0,x+(r*cos(getRadian(18))),0,x+(r * sin(getRadian(36))),0,x-(r*sin(getRadian(36))),0,x-(r*cos(getRadian(18))),0 };
	double PointY[10] = {y-r,0,y-(r*sin(getRadian(18))),0,y+(r*cos(getRadian(36))),0,y + (r*cos(getRadian(36))) ,0,y - (r*sin(getRadian(18))),0};

	PointX[1] = CrossX(PointX[0],PointY[0], PointX[4], PointY[4] , PointX[8], PointY[8] , PointX[2], PointY[2]);
	PointX[3] = CrossX(PointX[0], PointY[0], PointX[4], PointY[4], PointX[6], PointY[6], PointX[2], PointY[2]);
	PointX[5] = CrossX(PointX[6], PointY[6], PointX[2], PointY[2], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointX[7] = CrossX(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointX[9] = CrossX(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[2], PointY[2]);


	PointY[1] = CrossY(PointX[0], PointY[0], PointX[4], PointY[4], PointX[8], PointY[8], PointX[2], PointY[2]);
	PointY[3] = CrossY(PointX[0], PointY[0], PointX[4], PointY[4], PointX[6], PointY[6], PointX[2], PointY[2]);
	PointY[5] = CrossY(PointX[6], PointY[6], PointX[2], PointY[2], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointY[7] = CrossY(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[4], PointY[4]);
	PointY[9] = CrossY(PointX[0], PointY[0], PointX[6], PointY[6], PointX[8], PointY[8], PointX[2], PointY[2]);

	POINT point[10] = { };

	for (int i = 0; i < 10; i++)
	{
		point[i] = {(int) PointX[i],(int)PointY[i] };
	}

	Polygon(hdc, point, 10);
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
    LoadStringW(hInstance, IDC_MY0710STUDY, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MY0710STUDY));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MY0710STUDY));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_MY0710STUDY);
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

const int speed = 20;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static TCHAR str[100];
	static int count,yPos;
	static SIZE size;
	static int Check;
	static bool bFlag;

	static int x1, y1;
	static int mouseX, mouseY;
	static RECT rectView;

    switch (message)
    {
	case WM_CREATE:
		count = 0;
		yPos = 0;

		mouseX = 0; 
		mouseY = 0;
		SetTimer(hWnd, 1, 70, NULL);
		//SetTimer(hWnd, 2, 170, NULL);

		GetClientRect(hWnd, &rectView);
		x1 = 100;
		y1 = 100;


		
		CreateCaret(hWnd,NULL,5,30);//캐럿생성
		ShowCaret(hWnd);

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
	case WM_CHAR:
	{
		
		//키를 누를떄 글씨가나옴
		//HDC hdc = GetDC(hWnd);
		if (wParam == VK_BACK && count > 0)
			count--;
		else if (wParam == VK_RETURN)
		{
			count = 0;
			yPos = yPos + 20;
		}
		else 
			str[count++] = wParam;


		
		
		str[count] = NULL;
		InvalidateRgn(hWnd, NULL, TRUE); //WM_PAINT 호출 
	
		
		//TextOut(hdc, 300, 300,_T("어떤 키를 누를 때 이 문장이 보이나요"), 22); //뒤에껀길이 앞에게 문자
		//ReleaseDC(hWnd, hdc);
		break;
	}

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
			/*//TextOut(hdc, 0, yPos, str, _tcslen(str));
			
			//WCHAR test1[15] = L"테스트1asd";
			//TCHAR test2[15] = _T("테스트2asdcc");
			//TextOut(hdc, 300, 300, test2, _tcslen(test2)); //뒤에껀길이 앞에게 문자
			//TCHAR left[10] = L"왼쪽";
			//TCHAR right[10] = L"오른쪽";
			//TCHAR up[10] = L"위쪽";
			//TCHAR down[10] = L"아래쪽";


			//RECT rc;
			//rc.left = 10;
			//rc.top = 10+yPos;
			//rc.right = 400;
			//rc.bottom = 100+yPos;
	
			//DrawText(hdc, str, _tcslen(str), &rc,DT_SINGLELINE| DT_LEFT  );

			//GetTextExtentPoint(hdc, str, _tcslen(str),&size);
			//SetCaretPos(size.cx+10, 10+yPos);
			////DrawGrid(hdc, 100, 100, 500, 500, 50);//100,100에서 500에 500까지 50간격으로 
			////DrawCircle(hdc, 200, 200,50);
			//RECT test;
			//test.left = 100;
			//test.top = 100;
			//test.right = 400;
			//test.bottom = 400;
			//Rectangle(hdc, test.left - 5, test.top - 5, test.right+ 5, test.bottom + 5);
			////test = { 100,100,400,400 };
			//DrawText(hdc, left, _tcslen(left), &test, DT_SINGLELINE | DT_LEFT |DT_TOP);
			//DrawText(hdc, right, _tcslen(right), &test, DT_SINGLELINE | DT_RIGHT | DT_BOTTOM);
		
			//HPEN hPen,hPen2, oldPen;
			//hPen = CreatePen(PS_DOT, 4, RGB(255, 0, 0));
			//hPen2 = CreatePen(PS_DASH, 4, RGB(0, 0, 255));
			//oldPen = (HPEN)SelectObject(hdc, hPen);

			//HBRUSH hBrush, oldBrush;

			//hBrush = CreateSolidBrush(RGB(255, 255, 0));
			////oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			//oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));
			///*
			//old Pen = PS_SOLID, 1, RGB(0,0,0)
			//*/
			/*//SelectObject(hdc, hPen);

			//DrawStar(hdc, 300, 300, 50);
			//DrawStar(hdc, 300, 300, 80);
			//DrawStar(hdc, 100, 300, 200);

			//SelectObject(hdc, oldBrush);
			//DeleteObject(hBrush);
			//SelectObject(hdc, oldPen);

			DeleteObject(hPen);
			DeleteObject(hPen2);*/


			/*
			RECT ru,rd,rl,rr;


			int RectangleCenterX1 = 200, RectangleCenterY1 = 200;
			int RectangleCenterX2 = 300, RectangleCenterY2 = 300;
			HBRUSH hBrush, oldBrush;
	

			
	
			Rectangle(hdc, RectangleCenterX1, RectangleCenterY1, RectangleCenterX2, RectangleCenterY2); //가운데거 

			Rectangle(hdc, RectangleCenterX1, RectangleCenterY1 - 100, RectangleCenterX2, RectangleCenterY1); //위에거

			ru = { RectangleCenterX1, RectangleCenterY1 - 100 , RectangleCenterX2, RectangleCenterY1 };

			DrawText(hdc, up, _tcslen(up), &ru, DT_SINGLELINE | DT_CENTER);



			Rectangle(hdc, RectangleCenterX1, RectangleCenterY2, RectangleCenterX2, RectangleCenterY2 + 100); //아래거
			rd = { RectangleCenterX1, RectangleCenterY2, RectangleCenterX2, RectangleCenterY2 + 100 };

			DrawText(hdc, down, _tcslen(down), &rd, DT_SINGLELINE | DT_CENTER);

			Rectangle(hdc, RectangleCenterX2, RectangleCenterY1, RectangleCenterX2 + 100, RectangleCenterY2); //오른쪽

			rr = { RectangleCenterX2, RectangleCenterY1, RectangleCenterX2 + 100, RectangleCenterY2 };

			DrawText(hdc, right, _tcslen(right), &rr, DT_SINGLELINE | DT_CENTER);


			Rectangle(hdc, RectangleCenterX1 - 100, RectangleCenterY1, RectangleCenterX1, RectangleCenterY2); //왼쪽거 
			rl = { RectangleCenterX1 - 100, RectangleCenterY1, RectangleCenterX1, RectangleCenterY2 };

			DrawText(hdc, left, _tcslen(left), &rl, DT_SINGLELINE | DT_CENTER);

			hBrush = CreateSolidBrush(RGB(255, 0, 0));
			oldBrush = (HBRUSH)SelectObject(hdc, hBrush);
			if (bFlag)
			{
				switch (Check)
				{
				case 1:
					Rectangle(hdc, RectangleCenterX1, RectangleCenterY1 - 100, RectangleCenterX2, RectangleCenterY1);
					break;
				case 2:
					Rectangle(hdc, RectangleCenterX1, RectangleCenterY2, RectangleCenterX2, RectangleCenterY2 + 100);
					break;
				case 3:
					Rectangle(hdc, RectangleCenterX2, RectangleCenterY1, RectangleCenterX2 + 100, RectangleCenterY2);
					break;
				case 4:
					Rectangle(hdc, RectangleCenterX1 - 100, RectangleCenterY1, RectangleCenterX1, RectangleCenterY2);
					break;
				}
			}
			else
			{
				Rectangle(hdc, RectangleCenterX1, RectangleCenterY1, RectangleCenterX2, RectangleCenterY2);
			}



	
			SelectObject(hdc, oldBrush);
			DeleteObject(hBrush);
			*/
			//키다운과 키업



		//Rectangle(hdc, x1, y1, x2, y2);
		//Ellipse(hdc, x1, y1,x2,y2);
		DrawCircle(hdc, mouseX, mouseY,50);
		//Rectangle(hdc, x1+100, y1, x2+100, y2);
		//Ellipse(hdc, x1+100, y1, x2+100, y2);

           EndPaint(hWnd, &ps);
        }
        break;
	case WM_KEYDOWN:
	{
		/*bFlag = true;
		Check = 0;
		switch (wParam)
		{
		case VK_UP:
			Check = 1;
			break;
		case VK_DOWN:
			Check = 2;
			break;
		case VK_RIGHT:
			Check = 3;
			break;
		case VK_LEFT:
			Check = 4;
			break;
		default:
			Check = 0;
			break;*/

/*
		//if(wParam ==VK_RIGHT)
		//{
		//	

		//	x1 += speed;
		//

		//	if (rectView.right < x1)
		//	{
		//		x1 -= speed;
		//		
		//	}
		//	
		//}
		//else if (wParam == VK_LEFT)
		//{
		//	x1 -= speed;
		//	
		//	if (rectView.left > x1)
		//	{
		//		x1 += speed;
		//		
		//	}
		//	
		//}
		//else if (wParam == VK_UP)
		//{
		//	y1 -= speed;
		//
		//	if (rectView.top > y1)
		//	{
		//		y1 +=speed;
		//		
		//	}
		//	
		//}
		//else if (wParam == VK_DOWN)
		//{
		//	y1 += speed;
		//	
		//	if (rectView.bottom < y1)
		//	{
		//		y1 -= speed;
		//		
		//	}
		//	
		//}
		*/
		InvalidateRgn(hWnd, NULL, TRUE);
	}	
		break;
	case WM_KEYUP:
		//bFlag = false;
		InvalidateRgn(hWnd, NULL, TRUE);
		break;
	case WM_TIMER:
		/*switch (wParam)
		{
		case 1:
			if (x1 == mouseX)
			{
				x1 += speed;

				if (rectView.right < x1)
				{
					x1 -= speed;
				}
			}


			
			InvalidateRgn(hWnd, NULL, TRUE);
			
			break;
		case 2:
			y1 += speed;
			y2 += speed;
			if (rectView.bottom < y2)
			{
				y1 -= speed;
				y2 -= speed;
			}

			InvalidateRgn(hWnd, NULL, TRUE);
			break;
		}*/
		/*
		if (x1 > mouseX && x1-mouseX >= 10)
		{
			x1 -= speed;
		}
		else if (x1 < mouseX && mouseX - x1 >= 10 )
		{
			x1 += speed;
		}

		if (y1 > mouseY &&  y1 - mouseY  >= 10)
		{
			y1 -= speed;
		}
		else if (y1 < mouseY && mouseY - y1 >= 10 )
		{
			y1 += speed;
		}
		*/

		InvalidateRgn(hWnd, NULL, TRUE);
		break;
    case WM_DESTROY:
		HideCaret(hWnd);
		DestroyCaret();
		//캐럿만들엇으니까 지우기 위에 


        PostQuitMessage(0);
        break;

	case WM_LBUTTONDOWN://왼쪽클릭햇을경우
		{
			mouseX = LOWORD(lParam);
			mouseY = HIWORD(lParam);
		}
		break;
	case WM_LBUTTONUP://클릭하고 띄는순간   너희들 메뉴가있잖아 이게버튼이야 . 이걸탁눌렀어 . 아 생각해보니까 누를친구가아니야 
		break;
	case WM_RBUTTONDOWN:
		break;
	case WM_NCRBUTTONUP:
		break;
	case WM_MOUSEMOVE:
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

