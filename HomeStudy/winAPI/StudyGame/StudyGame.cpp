// StudyGame.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "StudyGame.h"
#include "FileInout.h"
#include "Rect.h"
#include "Monster.h"
#include "PlayerBullet.h"
#include "GameObject.h"
#include <tchar.h>
#include <math.h>
#include <stdlib.h>


#include <vector>
#include <fstream>
#include <iostream>
#include <string>

enum PLAYSCREEN
{
	PLAY_MENU,
	PLAY_GAME,
	PLAY_END
};

int SCREEN = PLAY_MENU;
const int namesize = 10;
const int BlockCount = 8;
const int BulletCount = 5;
const int MonsterCount = 30;

const int MonsterSpawnTime = 30;
static int TimeCheck = 0;

const int setDegree = 5;
static int degree;
static TCHAR tcScore[30];
static TCHAR input[namesize];
GameManager manger; 


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


TCHAR* RankIntOut();
const string TCHARToString(const TCHAR* ptsz);

void MakeCannon(HDC hdc)
{

	POINT point[3] = { { 380,700 },{ 420,700 },{ 400,840 } };
	double CenterX = 400;
	double CenterY = 850;

	for (int i = 0; i < 3; i++)
	{
		double xTmp = (point[i].x - CenterX);
		double yTmp = (point[i].y - CenterY);
		point[i].x = cos(degree * PI / 180) * xTmp - sin(degree * PI / 180) * yTmp + CenterX;
		point[i].y = sin(degree * PI / 180) *  xTmp + cos(degree * PI / 180) * yTmp + CenterY;
	}

	Polygon(hdc, point, 3);
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
    LoadStringW(hInstance, IDC_STUDYGAME, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_STUDYGAME));

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




//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_STUDYGAME));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = NULL;
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

   HWND hWnd = CreateWindowW(szWindowClass, szWindowClass, WS_OVERLAPPEDWINDOW,
      600,30, 800, 1000, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}


//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//  PURPOSE:  Processes messages for the main window.
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HFONT hFont, oldFont;
	HPEN hpen, oldpen;
	PAINTSTRUCT ps;
	HBRUSH hBrush, oldBrush;
	static int count , bullet;
	static vector<Rect*> vecRect;
	static vector<PlayerBullet*> vecBullet;
	static vector<Monster*> vecMonster;
	static int spawn;
	int temp = spawn % MonsterCount;
	static int iScore;
	static RECT RectView;

	



    switch (message)
    {
	case WM_CREATE:
		{
		GetClientRect(hWnd, &RectView);
		RectView.top += 50;
		iScore = 0;
		bullet = 0;
		degree = 0;
		SetTimer(hWnd, 1, 70, NULL);
		SetTimer(hWnd, 2, 100, NULL);

			for (int i = 0; i < BulletCount; i++)
			{
				PlayerBullet *bullet = new PlayerBullet(i);
				vecBullet.push_back(bullet);
			}

			for (int i = 0; i < MonsterCount; i++)
			{
				Monster *mons = new Monster(i, rand() % 8);
				vecMonster.push_back(mons);
			}
			for (int i = 0; i < BlockCount; i++)
			{
				Rect *obj = new Rect(i);
				vecRect.push_back(obj);
			}
		}
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
			switch (SCREEN)
			{
			case PLAY_MENU:
				{
				

				TCHAR *str = TEXT("벽을 지키기 1.0ver");

				//폰트스타일
				hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));

				oldFont = (HFONT)SelectObject(hdc, hFont);
				TextOut(hdc, 180, 100, str, lstrlen(str));
				SelectObject(hdc, oldFont);
				DeleteObject(hFont);

				//시작화면 상자 스타일
				hpen = CreatePen(PS_SOLID, 4, RGB(0, 0, 0));
				oldpen = (HPEN)SelectObject(hdc, hpen);

				RECT inform, inform2, idSetting;
				inform = { 150,640,600,700 };
				inform2 = { 150,740,300,800 };
				idSetting = { 300,740,600,800 };

				Rectangle(hdc, 150, 600, 650, 700);
				Rectangle(hdc, 150, 700, 300, 800);
				Rectangle(hdc, 300, 700, 650, 800);


				//폰트스타일
				hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("돋움"));

				oldFont = (HFONT)SelectObject(hdc, hFont);

				DrawText(hdc, _T("ID 입력창"), 6, &inform, DT_SINGLELINE || DT_CENTER || DT_VCENTER);
				DrawText(hdc, _T("ID"), 2, &inform2, DT_SINGLELINE || DT_CENTER || DT_VCENTER);
				DrawText(hdc, input, _tcslen(input), &idSetting, DT_SINGLELINE || DT_CENTER || DT_VCENTER);

				SelectObject(hdc, oldFont);
				DeleteObject(hFont);

				
			}
				break;
			case PLAY_GAME:
				{
			
					RECT ID;
					ID = { 0,30,150,100 };
				
					hpen = CreatePen(PS_SOLID, 2, RGB(0, 0, 0));
					oldpen = (HPEN)SelectObject(hdc, hpen);

					Rectangle(hdc, 0, 0, 150, 100);
					Rectangle(hdc, 150, 0, 800, 100);

					SelectObject(hdc, oldpen);
					DeleteObject(hpen);


					hFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
					oldFont = (HFONT)SelectObject(hdc, hFont);

		
					DrawText(hdc, input, _tcslen(input), &ID, DT_SINGLELINE || DT_CENTER || DT_VCENTER);

					SelectObject(hdc, oldFont);
					DeleteObject(hFont);

					
					hFont = CreateFont(50, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("궁서"));
					oldFont = (HFONT)SelectObject(hdc, hFont);
					TCHAR *str = TEXT("SCORE :");

					TextOut(hdc, 180, 30, str, lstrlen(str));
					TextOut(hdc, 400, 30, tcScore, _tcslen(tcScore));
					

					SelectObject(hdc, oldFont);
					DeleteObject(hFont);


					hBrush = CreateSolidBrush(RGB(255, 0, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

					MakeCannon(hdc);
			
					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);

					hBrush = CreateSolidBrush(RGB(0, 255, 0));
					oldBrush = (HBRUSH)SelectObject(hdc, hBrush);

					Pie(hdc, 300,800,500,900,500,850,300,850); //반원 

					SelectObject(hdc, oldBrush);
					DeleteObject(hBrush);
				
					for (Rect *i : vecRect)
					{
						i->Draw(hdc);
					}

					for (PlayerBullet *i : vecBullet)
					{
						i->Draw(hdc);
					}

				
					for (Monster *i : vecMonster)
					{
						if (i->monster_id <= temp)
						{
							i->Draw(hdc);
						
						}
					}

			
				}
				break;
			case PLAY_END:
				{
				TCHAR *gameEnd = TEXT("GAME OVER");
				TCHAR *Point;
				RECT rcRank;
				rcRank = { 80,150,700,900 };
				DrawText(hdc, gameEnd, _tcslen(gameEnd), &RectView, DT_SINGLELINE || DT_CENTER || DT_VCENTER);
				Point = RankIntOut();
				DrawText(hdc, Point, _tcslen(Point), &rcRank, DT_SINGLELINE || DT_CENTER || DT_VCENTER);
				
				}
				break;
			}
			EndPaint(hWnd, &ps);
        }
        break;
	case WM_CHAR:
		{
			switch (SCREEN)
			{
			case PLAY_MENU:
				{
					if (wParam == VK_BACK &&count > 0) count--;
					else if (wParam != VK_BACK  && count < namesize - 1)input[count++] = wParam;

					if (wParam == VK_RETURN)
					{
						SCREEN = PLAY_GAME;
					}
					input[count] = NULL;
				}
				InvalidateRgn(hWnd, NULL, TRUE);
				break;
			case PLAY_END:
				if (wParam == VK_RETURN)exit(0);
				break;
			}
			
			
		}
		
		break;
	case WM_KEYDOWN:
		{
			switch (SCREEN)
			{
			case PLAY_GAME:
				{
					if (wParam == VK_RIGHT)
					{
						if (degree < 60)
						{
							degree += setDegree;
						}
					}
					else if (wParam == VK_LEFT)
					{

						if (degree > -60)
						{
							degree -= setDegree;
						}
					}
					else if (wParam == VK_SPACE)
					{
						int temp = bullet % BulletCount;
						for (PlayerBullet *i : vecBullet)
						{
							if (i->iBullet_id == temp)
							{
								if (i->getFlag() != 1)
								{
									i->setDegree(degree);
									i->setBulletFlag();
									bullet++;
									break;
								}
							}
						}

					}
					InvalidateRgn(hWnd, NULL, TRUE);
				}
				break;
			}
			
			
		}
		break;
	case WM_TIMER:
		{
		switch (SCREEN)
		{
		case PLAY_GAME:
			{
			switch (wParam)
				{
					case 1:
					{
						for (PlayerBullet *i : vecBullet)
						{
							i->update(vecMonster);
						}

						for (Monster *i : vecMonster)
						{
							if (i->monster_id <= temp)
							{
								i->update(vecRect);
							}
						}

						int gameoverCheck = 0;
						for (Rect *i : vecRect)
						{
							i->update(vecMonster);
							if (i->FlagRect)
							{
								gameoverCheck++;
							}
						}
						if (gameoverCheck == 0) SCREEN = PLAY_END;
						InvalidateRgn(hWnd, NULL, TRUE);
					}
					break;
					case 2:
					{
						iScore++;
						_itow(iScore, tcScore, 10);
						TimeCheck++;
						if (TimeCheck >= MonsterSpawnTime)
						{
							TimeCheck = 0;
							spawn++;
						}
						InvalidateRgn(hWnd, NULL, TRUE);
					}
					break;
				}
			}
			break;
		}
			
		
			
		}
		break;
    case WM_DESTROY:
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			PostQuitMessage(0);
		}
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

TCHAR* RankIntOut()
{
	
	vector<PlayerRank*> vecRank;


	ofstream outFile;
	string Scoretemp = TCHARToString(tcScore); //string으로 변환
	string Idtemp = TCHARToString(input);
	string temp = Scoretemp+"="+Idtemp+"\n";
	outFile.open("Ranking.dat",ios::app); //ios::app이 이어쓰기모드
	if (outFile.is_open())
	{
		outFile  << temp;
	}
	else
	{
		cout << "실패";
	}

	outFile.close();

	temp = "";
	Scoretemp = "";
	Idtemp = "";

	string text;

	ifstream inFile;
	inFile.open("Ranking.dat");
	if (inFile.is_open())
	{
		/* 하나하나 읽어오기 */
		while (getline(inFile, text)) 
		{
			//temp += text;

			int fin,insert;
			fin = text.find("=");
			insert = text.find("\r");
			Scoretemp = "";
			Idtemp = "";

			for (int i = 0; i < fin; i++)
			{
				Scoretemp += text[i];
			}
			for (int i = fin+1; i <insert; i++)
			{
				Idtemp += text[i];
			}

			
			PlayerRank* player = new PlayerRank;
			player->name = Idtemp;
			player->Score = stoi(Scoretemp);

			vecRank.push_back(player);
		}
	}
	else
	{
		cout << "실패";
		return 0;
	}
	inFile.close();
	//vector<PlayerRank*>::iterator iter = vecRank.begin();


	/* 벡터를 버블로정렬
	for (int i = 1; i < vecRank.size()-1; i++)
	{
		for (int j = 1; j < vecRank.size(); j++)
		{
			if (vecRank[j - 1] > vecRank[j])
			{
				swap(vecRank[j - 1], vecRank[j]);
			}
		}
	}
	*/

	/*삽입정렬*/
	int itemp = 0;
	for (int i = 1; i < vecRank.size(); i++)
	{
		itemp = i;
		while (vecRank[itemp]->Score > vecRank[itemp - 1]->Score )
		{
			swap(vecRank[itemp], vecRank[itemp - 1]);
			itemp--;
			if (itemp == 0)break;
		}
	}

	int ranking =1;
	for (PlayerRank* i : vecRank)
	{
		temp += to_string(ranking)+"st :" + i->name +":" + to_string(i->Score) + "\n";
		ranking++;
	}



	/*string TCHAR 로 내보내는법 */
	const char* all = temp.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);

	return (TCHAR*)t;
}

TCHAR* StringToTCHAR(string& s)
{
	//tstring tstr;
	const char* all = s.c_str();
	int len = 1 + strlen(all);
	wchar_t* t = new wchar_t[len];
	if (NULL == t) throw std::bad_alloc();
	mbstowcs(t, all, len);
	return (TCHAR*)t;
}

const string TCHARToString(const TCHAR* ptsz)
{
	int len = wcslen((wchar_t*)ptsz);

	char* psz = new char[2 * len + 1];

	wcstombs(psz, (wchar_t*)ptsz, 2 * len + 1);
	std::string s = psz;

	delete[] psz;

	return s;
}
