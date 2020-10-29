#include "stdafx.h"
#include "cButton.h"


cButton::cButton()
	:m_pRoot(NULL)
	, m_ptMouseClick({ 0,0 })
	, m_ptMouseMove({ 0,0 })
	, m_ptPosition({ 0,0 })
	, m_isMouseButtonDown(false)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cButton::~cButton()
{
}

void cButton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}
