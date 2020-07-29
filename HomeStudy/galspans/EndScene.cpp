#include "stdafx.h"


extern GameManager * g_GameManager;
EndScene::EndScene()
{
	m_EndUI = new EndUI;

	m_SceneUI = m_EndUI;

	n_rc_reStart_btn = { 200,300-10,400,370-10 };
	m_rc_menu_btn = { 500,300-10,700,370-10 };
	
}


EndScene::~EndScene()
{
}

void EndScene::Init(void)
{
}

void EndScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{

	if (message == WM_LBUTTONDOWN)
	{
		int Clickx = LOWORD(lParam);
		int Clicky = HIWORD(lParam);

		if (Clickx >= n_rc_reStart_btn.left &&Clickx <= n_rc_reStart_btn.right
			&& Clicky >= n_rc_reStart_btn.top && Clicky <= n_rc_reStart_btn.bottom)
		{
			g_GameManager->SceneChange(Scene_enum::SCENE_GAME);
		}
		else if (Clickx >= m_rc_menu_btn.left &&Clickx <= m_rc_menu_btn.right
			&& Clicky >= m_rc_menu_btn.top && Clicky <= m_rc_menu_btn.bottom)
		{
			g_GameManager->SceneChange(Scene_enum::SCENE_MENU);
			
		}


	}

}

void EndScene::Render(HWND hWnd, HDC hdc)
{
	m_SceneUI->draw(hdc);
}

void EndScene::Free(void)
{
}
