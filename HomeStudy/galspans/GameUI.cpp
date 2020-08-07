#include "stdafx.h"


GameUI::GameUI()
{
	n_rc_reStart = { 200,300,400,370 };
	m_rc_menu = { 500,300,700,370 };
}


GameUI::~GameUI()
{
}

void GameUI::Init(void)
{
}

void GameUI::draw(HDC hdc)
{
	Rectangle(hdc, n_rc_reStart.left, n_rc_reStart.top - 10, n_rc_reStart.right, n_rc_reStart.bottom - 10);
	(HFONT)SelectObject(hdc, FontSetting.EndFont);
	DrawText(hdc, FontSetting.m_reStart.c_str(), FontSetting.m_reStart.size(), &n_rc_reStart, DT_TOP | DT_CENTER | DT_SINGLELINE);

	/*EXIT BUTTON*/
	Rectangle(hdc, m_rc_menu.left, m_rc_menu.top - 10, m_rc_menu.right, m_rc_menu.bottom - 10);
	//폰트 start와 동일.
	DrawText(hdc, FontSetting.m_reMenu.c_str(), FontSetting.m_reMenu.size(), &m_rc_menu, DT_TOP | DT_CENTER | DT_SINGLELINE);
}
