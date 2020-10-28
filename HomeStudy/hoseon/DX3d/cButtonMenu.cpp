#include "stdafx.h"
#include "cButton.h"
#include "cButtonMenu.h"
#include "cBtnSprite.h"


cButtonMenu::cButtonMenu()
	: m_ptMouseClick({0,0})
	, m_ptMouseMove({0,0})
	, m_ptPosition({0,0})
	, m_isMouseButtonDown(false)
{

}


cButtonMenu::~cButtonMenu()
{
	if(m_pRoot)
		m_pRoot->Destroy();

}

void cButtonMenu::Setup()
{
	
	D3DXVECTOR2 vecTemp(0,0);
	cBtnSprite* m_cBody = new cBtnSprite("UI","panel-info.png");
	m_cBody->Setup(vecTemp);
	m_cBody->SetParentWorldTM(&m_matWorld);
	m_pRoot = m_cBody;

	m_SpriteSize.push_back(m_cBody->m_veSize);
	m_SpritePosition.push_back(vecTemp);

	vecTemp = D3DXVECTOR2(130, 330);
	cBtnSprite* m_cOk = new cBtnSprite("UI", "btn-med-down.png");
	m_cOk->Setup(vecTemp);
	m_pRoot->AddChild(m_cOk);

	m_SpriteSize.push_back(m_cOk->m_veSize);
	m_SpritePosition.push_back(vecTemp);

	
	vecTemp = D3DXVECTOR2(130, 400);
	cBtnSprite* m_cCancel = new cBtnSprite("UI", "btn-med-down.png");
	m_cCancel->Setup(vecTemp);
	m_pRoot->AddChild(m_cCancel);

	m_SpriteSize.push_back(m_cCancel->m_veSize);
	m_SpritePosition.push_back(vecTemp);


	vecTemp = D3DXVECTOR2(400, 80);
	cBtnSprite* m_cExit = new cBtnSprite("UI", "btn-main-menu.png");
	m_cExit->Setup(vecTemp);
	m_pRoot->AddChild(m_cExit);

	m_SpriteSize.push_back(m_cExit->m_veSize);
	m_SpritePosition.push_back(vecTemp);


	
}

void cButtonMenu::Update()
{
	//D3DXMATRIXA16 matT;
	//D3DXMatrixTranslation(&m_matWorld, 100, 0, 0);

	if (m_pRoot)
		m_pRoot->Update();
}

void cButtonMenu::Render()
{
	if (m_pRoot)
		m_pRoot->Render();
}

void cButtonMenu::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_ptMouseClick.x = LOWORD(lParam);
		m_ptMouseClick.y = HIWORD(lParam);
		if()
		m_isMouseButtonDown = true;
		break;
	case WM_LBUTTONUP:
		m_isMouseButtonDown = false;
		break;
	case WM_MOUSEMOVE:
		if (m_isMouseButtonDown)
		{
			m_ptMouseMove.x = LOWORD(lParam);
			m_ptMouseMove.y = HIWORD(lParam);

			m_ptPosition.x += m_ptMouseMove.x - m_ptMouseClick.x;

			cout << m_ptPosition.x<<endl;
			D3DXMatrixTranslation(&m_matWorld, m_ptPosition.x, 0, 0);
		}
		break;
	}
		
}
