#include "stdafx.h"

extern GameManager * g_GameManager;

MenuScene::MenuScene()
{
	m_SceneUI = m_MenuUI;
	Init();
}


MenuScene::~MenuScene()
{
}

void MenuScene::Init(void)
{
	m_rc_Title_Btn = { 200,50,700,200 };
	m_rc_Start_Btn = { 350,300-10,550,370-10 };
	m_rc_Exit_Btn = { 350,400-10,550,470-10 };
}

void MenuScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	

	if (message == WM_LBUTTONDOWN )
	{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);

		if (Clickx >= m_rc_Start_Btn.left &&Clickx <= m_rc_Start_Btn.right 
			&& Clicky>=m_rc_Start_Btn.top && Clicky <= m_rc_Start_Btn.bottom)
		{
			g_GameManager->SceneChange(Scene_enum::SCENE_GAME);
		}
		else if (Clickx >= m_rc_Exit_Btn.left &&Clickx <= m_rc_Exit_Btn.right
			&& Clicky >= m_rc_Exit_Btn.top && Clicky <= m_rc_Exit_Btn.bottom)
		{
			PostQuitMessage(0);
		}

		
	}

}

void MenuScene::Render(HWND hWnd, HDC hdc)
{
	m_SceneUI->draw(hdc);
}

void MenuScene::Free(void)
{
}
