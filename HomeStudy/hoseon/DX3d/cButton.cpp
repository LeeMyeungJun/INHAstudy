#include "stdafx.h"
#include "cButton.h"


cButton::cButton()
	:m_pRoot(NULL)
	, m_ptMouseClick({ 0,0 })
	, m_ptMouseMove({ 0,0 })
	, m_vPosition({ 0,0 })
	, m_vSize({0,0})
	, m_isMouseDown(false)
	, m_isMouseBtnDown(false)
	, m_isOnOff(true)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cButton::~cButton()
{
}

void cButton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}

void cButton::Move(D3DXVECTOR2 vMove)
{
	m_vPosition += vMove;
	D3DXMatrixTranslation(&m_matWorld, (FLOAT)m_vPosition.x, (FLOAT)m_vPosition.y, 0);
}

bool cButton::InCheck(POINT MousePt)
{
	if (m_vPosition.x <= MousePt.x && m_vPosition.x + m_vSize.x >= MousePt.x
		&& m_vPosition.y <= MousePt.y && m_vPosition.y + m_vSize.y >= MousePt.y)
		return true;

	
	return false;
}

void cButton::BtnOnOff()
{
	m_isOnOff = !m_isOnOff;
}


