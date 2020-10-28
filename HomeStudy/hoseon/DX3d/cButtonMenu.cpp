#include "stdafx.h"
#include "cButton.h"
#include "cButtonMenu.h"
#include "cBtnSprite.h"


cButtonMenu::cButtonMenu()
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


	vecTemp = D3DXVECTOR2(130, 330);
	cBtnSprite* m_cOk = new cBtnSprite("UI", "btn-med-down.png");
	m_cOk->Setup(vecTemp);
	m_pRoot->AddChild(m_cOk);

	
	vecTemp = D3DXVECTOR2(130, 400);
	cBtnSprite* m_cCancel = new cBtnSprite("UI", "btn-med-down.png");
	m_cCancel->Setup(vecTemp);
	m_pRoot->AddChild(m_cCancel);


	vecTemp = D3DXVECTOR2(400, 80);
	cBtnSprite* m_cExit = new cBtnSprite("UI", "btn-main-menu.png");
	m_cExit->Setup(vecTemp);
	m_pRoot->AddChild(m_cExit);

}

void cButtonMenu::Update()
{
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
	if(m_pRoot)
		m_pRoot->WndProc(hWnd, message, wParam, lParam);
		
}
