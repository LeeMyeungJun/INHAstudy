#include "stdafx.h"


MenuScene::MenuScene()
{
	m_rc_Title = { 200,50,700,200 };
	m_rc_Start = { 350,300,550,370 };
	m_rc_Exit = { 350,400,550,470 };

	TitleFont = CreateFont(80, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "1훈새마을운동 R");
	CommonFont = CreateFont(30, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "빙그레체");

}


MenuScene::~MenuScene()
{
}

void MenuScene::Init(void)
{
}

void MenuScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	if (message == WM_LBUTTONDOWN)
	{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);

		if (Clickx >= m_rc_Start.left &&Clickx <= m_rc_Start.right
			&& Clicky >= m_rc_Start.top && Clicky <= m_rc_Start.bottom)
		{
			GameCenter::GetInstance()->SceneChange(Scene_enum::GAME_ENUM);
		}
		else if (Clickx >= m_rc_Exit.left &&Clickx <= m_rc_Exit.right
			&& Clicky >= m_rc_Exit.top && Clicky <= m_rc_Exit.bottom)
		{
			PostQuitMessage(0);
		}
	}
}

void MenuScene::Render(HWND hWnd, HDC hdc)
{
	UI(hdc);
}

void MenuScene::Free(void)
{
}

void MenuScene::UI(HDC hdc)
{
	Rectangle(hdc, m_rc_Title.left, m_rc_Title.top - 10, m_rc_Title.right, m_rc_Title.bottom - 50);
	HFONT oldFont = (HFONT)SelectObject(hdc, TitleFont);
	DrawTextW(hdc,m_Title.c_str(),m_Title.size(), &m_rc_Title, DT_TOP | DT_CENTER | DT_SINGLELINE);



	/*START BUTTON*/
	Rectangle(hdc, m_rc_Start.left, m_rc_Start.top - 10, m_rc_Start.right, m_rc_Start.bottom - 10);
	(HFONT)SelectObject(hdc, CommonFont);
	DrawTextW(hdc, m_StartButton.c_str(), m_StartButton.size(), &m_rc_Start, DT_TOP | DT_CENTER | DT_SINGLELINE);


	/*EXIT BUTTON*/
	Rectangle(hdc, m_rc_Exit.left, m_rc_Exit.top - 10, m_rc_Exit.right, m_rc_Exit.bottom - 10);
	//폰트 start와 동일.
	DrawTextW(hdc, m_ExitButton.c_str(), m_ExitButton.size(), &m_rc_Exit, DT_TOP | DT_CENTER | DT_SINGLELINE);



	SelectObject(hdc, oldFont);
}
