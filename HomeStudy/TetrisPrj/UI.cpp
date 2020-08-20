#include "stdafx.h"


UI::UI(GameCenter * wrapped):m_gameCenter(wrapped)
{
	
	TitleFont = CreateFont(FONT_TITLE_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1훈새마을운동 R");
	CommonFont = CreateFont(FONT_COMMON_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"빙그레체");
	EndFont = CreateFont(FONT_END_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"빙그레체");
	GameFont = CreateFont(FONT_GAME_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1훈새마을운동 R");
	ManualFont = CreateFont(FONT_MANUAL_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1훈새마을운동 R");

	LineBrush = CreateSolidBrush(RGB(255, 0, 0)); //빨간색
	BlockBrush = CreateSolidBrush(RGB(192, 192, 192)); //살잒회색
	BasicBrush = CreateSolidBrush(RGB(0, 0, 0)); //검정색


}


UI::~UI()
{
}

void UI::Init()
{
	GetClientRect(m_gameCenter->getHwnd(), &m_rcclient);

	m_rcLogin_Title = { m_rcclient.left + 300,m_rcclient.top + 50,m_rcclient.right - 300,m_rcclient.top + 250 };
	m_rcLogin_LocalBtn = { m_rcclient.left + 500,m_rcclient.bottom - 500,m_rcclient.left + 900,m_rcclient.bottom - 200 };
	m_rcLogin_OnlineBtn = { m_rcclient.right - 900,m_rcclient.bottom - 500,m_rcclient.right - 500,m_rcclient.bottom - 200 };
	m_rcLogin_ExitBtn = { m_rcclient.right - 150, m_rcclient.top + 30, m_rcclient.right - 50, m_rcclient.top + 100 };

}

void UI::UIRender(HDC hdc)
{
	Init();

	switch (m_gameCenter->getScene())
	{
	case GameCenter::Scene_enum::LOGIN_SCENE:
		LoginRender(hdc);
		break;
	case GameCenter::Scene_enum::LOBBY_SCENE:

		break;
	case GameCenter::Scene_enum::ROOM_SCENE:

		break;
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:

		break;
	}
}

void UI::LoginRender(HDC hdc)
{
	RECT rectTemp;
	/*TITLE*/
	Rectangle(hdc, m_rcLogin_Title.left, m_rcLogin_Title.top, m_rcLogin_Title.right, m_rcLogin_Title.bottom);
	HFONT oldFont = (HFONT)SelectObject(hdc, TitleFont);
	rectTemp = m_rcLogin_Title;
	rectTemp.top += 30;
	DrawText(hdc, m_Title.c_str(), m_Title.size(), &rectTemp, DT_TOP | DT_CENTER | DT_SINGLELINE);



	/*LOCAL BUTTON*/
	Rectangle(hdc, m_rcLogin_LocalBtn.left, m_rcLogin_LocalBtn.top, m_rcLogin_LocalBtn.right, m_rcLogin_LocalBtn.bottom);
	(HFONT)SelectObject(hdc, CommonFont);
	rectTemp = m_rcLogin_LocalBtn;
	rectTemp.top += 80;
	DrawText(hdc, m_LocalBtn.c_str(), m_LocalBtn.size(), &rectTemp, DT_TOP | DT_CENTER | DT_SINGLELINE);


	/*Online BUTTON*/
	Rectangle(hdc, m_rcLogin_OnlineBtn.left, m_rcLogin_OnlineBtn.top, m_rcLogin_OnlineBtn.right, m_rcLogin_OnlineBtn.bottom);
	//폰트 start와 동일.
	rectTemp = m_rcLogin_OnlineBtn;
	rectTemp.top += 80;
	DrawText(hdc, m_OnlineBtn.c_str(), m_OnlineBtn.size(), &rectTemp, DT_TOP | DT_CENTER | DT_SINGLELINE);

	/*EXIT */
	Rectangle(hdc, m_rcLogin_ExitBtn.left, m_rcLogin_ExitBtn.top, m_rcLogin_ExitBtn.right, m_rcLogin_ExitBtn.bottom);
	(HFONT)SelectObject(hdc, ManualFont);
	rectTemp = m_rcLogin_ExitBtn;
	rectTemp.top += 10;
	DrawText(hdc, m_Exit.c_str(), m_Exit.size(), &rectTemp, DT_TOP | DT_CENTER | DT_SINGLELINE);


	SelectObject(hdc, oldFont);


}
