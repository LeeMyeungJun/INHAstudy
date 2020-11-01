#include "stdafx.h"
#include "cButton.h"
#include "cButtonMenu.h"
#include "cBtnSprite.h"


cButtonMenu::cButtonMenu()
	:m_isClick(NULL)
{

}


cButtonMenu::~cButtonMenu()
{
	if(m_pRoot)
		m_pRoot->Destroy();

}

void cButtonMenu::Setup(bool* bCheck)
{
	m_isClick = bCheck;

	
	Sprite sp;
	
	D3DXVECTOR2 vecTemp(0,0);
	cBtnSprite* m_cBody = new cBtnSprite("UI","panel-info.png",NULL,NULL);
	m_cBody->Setup(vecTemp);
	
	m_cBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = m_cBody;
	sp.st_Position = D3DXVECTOR2(0, 0); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/panel-info.png");
	m_vecSprite.push_back(sp);
	m_vSize = g_pUITextureManager->GetTextureSize("UI/panel-info.png");
	m_vecBtn.push_back(m_cBody);

	
	vecTemp = D3DXVECTOR2(130, 330);
	cBtnSprite* m_cOk = new cBtnSprite("UI", "btn-med-over.png", "UI", "btn-med-down.png");
	m_cOk->Setup(vecTemp);
	m_pRoot->AddChild(m_cOk);
	sp.st_Position = D3DXVECTOR2(130, 330); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/btn-med-over.png");
	m_vecSprite.push_back(sp);
	m_vecBtn.push_back(m_cOk);

	
	vecTemp = D3DXVECTOR2(130, 400);
	cBtnSprite* m_cCancel = new cBtnSprite("UI", "btn-med-over.png", "UI", "btn-med-down.png");
	m_cCancel->Setup(vecTemp);
	m_pRoot->AddChild(m_cCancel);
	sp.st_Position = D3DXVECTOR2(130, 400); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/btn-med-over.png");
	m_vecSprite.push_back(sp);
	m_vecBtn.push_back(m_cCancel);


	vecTemp = D3DXVECTOR2(400, 80);
	cBtnSprite* m_cExit = new cBtnSprite("UI", "btn-main-menu.png",NULL,NULL);
	m_cExit->Setup(vecTemp);
	m_pRoot->AddChild(m_cExit);
	sp.st_Position = D3DXVECTOR2(400, 80); sp.st_SpriteSize = g_pUITextureManager->GetTextureSize("UI/btn-main-menu.png");
	m_vecSprite.push_back(sp);
	m_vecBtn.push_back(m_cExit);


}

void cButtonMenu::Update()
{
	if (!m_isOnOff)
		return;
	if (m_pRoot)
		m_pRoot->Update();
}

void cButtonMenu::Render()
{
	if (!m_isOnOff)
		return;
	if (m_pRoot)
		m_pRoot->Render();
}

void cButtonMenu::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (!m_isOnOff)
		return;
	
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptMouseClick.x = LOWORD(lParam);
		m_ptMouseClick.y = HIWORD(lParam);
		if(InCheck(m_ptMouseClick))
		{
			*m_isClick = false;
			m_isMouseDown = true;
			if(ChildBtnInCheck(m_ptMouseClick))
			{
				m_isMouseBtnDown = true;
			}
		}
		break;
	case WM_LBUTTONUP:
		{
		m_isMouseDown = false;
		*m_isClick = true;
		if (m_isMouseBtnDown)
		{
			m_ptMouseMove.x = LOWORD(lParam);
			m_ptMouseMove.y = HIWORD(lParam);

			int iEventCheck = ChildBtnInCheck(m_ptMouseMove);

			if (iEventCheck == 0)
				break;

			ClickEvent((EVENT)iEventCheck);


		}
		}
		
		break;
	case WM_MOUSEMOVE:
		if (m_isMouseDown)
		{
			m_ptMouseMove.x = LOWORD(lParam);
			m_ptMouseMove.y = HIWORD(lParam);

			D3DXVECTOR2 vTemp(0, 0);
			vTemp.x = m_ptMouseMove.x - m_ptMouseClick.x;
			vTemp.y = m_ptMouseMove.y - m_ptMouseClick.y;
			
			Move(vTemp);
			
			m_ptMouseClick = m_ptMouseMove;
		}
		break;
	}
		
}

void cButtonMenu::ClickEvent(EVENT ev)
{
	switch (ev)
	{
	case EN_OK:
		m_vecBtn[ev]->BtnOnOff();
		break;
	case EN_CANCEL:
		m_vecBtn[ev]->BtnOnOff();
		break;
	case EN_EXIT:
		BtnOnOff();
		break;

	}
}

int cButtonMenu::ChildBtnInCheck(POINT pt)
{
	for (int i = 0; i < m_vecSprite.size(); i++)
	{
		if(EN_BODY == i)continue;

		if (m_vPosition.x+ m_vecSprite[i].st_Position.x <= pt.x &&m_vPosition.x + m_vecSprite[i].st_Position.x + m_vecSprite[i].st_SpriteSize.x >= pt.x
			&& m_vPosition.y + m_vecSprite[i].st_Position.y <= pt.y &&m_vPosition.y + m_vecSprite[i].st_Position.y + m_vecSprite[i].st_SpriteSize.y >= pt.y)
			return i;
	}
	return 0;
}

