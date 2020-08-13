#include "stdafx.h"



//FontSetting

MenuUI::MenuUI()
{
	m_rc_Title = { 200,50,700,200 };
	m_rc_Start = { 350,300,550,370 };
	m_rc_Exit  = { 350,400,550,470 };
	m_rc_Manual = { 200,500,700,570 };
}


MenuUI::~MenuUI()
{
}

void MenuUI::Init(void)
{
	
}

void MenuUI::draw(HDC hdc)
{
	/*TITLE*/
	Rectangle(hdc, m_rc_Title.left, m_rc_Title.top-10, m_rc_Title.right, m_rc_Title.bottom-50);
	HFONT oldFont = (HFONT)SelectObject(hdc, FontSetting.TitleFont);
	DrawText(hdc, FontSetting.m_Title.c_str(), FontSetting.m_Title.size(), &m_rc_Title, DT_TOP | DT_CENTER | DT_SINGLELINE);



	/*START BUTTON*/
	Rectangle(hdc, m_rc_Start.left, m_rc_Start.top-10, m_rc_Start.right, m_rc_Start.bottom-10);
	(HFONT)SelectObject(hdc, FontSetting.CommonFont);
	DrawText(hdc, FontSetting.m_StartButton.c_str(), FontSetting.m_StartButton.size(), &m_rc_Start, DT_TOP | DT_CENTER | DT_SINGLELINE);


	/*EXIT BUTTON*/
	Rectangle(hdc, m_rc_Exit.left, m_rc_Exit.top-10, m_rc_Exit.right, m_rc_Exit.bottom-10);
	//폰트 start와 동일.
	DrawText(hdc, FontSetting.m_ExitButton.c_str(), FontSetting.m_ExitButton.size(), &m_rc_Exit, DT_TOP | DT_CENTER | DT_SINGLELINE);

	/*Manual */
	Rectangle(hdc, m_rc_Manual.left, m_rc_Manual.top - 10, m_rc_Manual.right, m_rc_Manual.bottom - 10);
	(HFONT)SelectObject(hdc, FontSetting.ManualFont);
	DrawText(hdc, FontSetting.m_Manual.c_str(), FontSetting.m_Manual.size(), &m_rc_Manual, DT_TOP | DT_CENTER | DT_SINGLELINE);


	SelectObject(hdc, oldFont);
}

