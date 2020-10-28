#include "stdafx.h"
#include "cButton.h"


cButton::cButton()
	:m_pRoot(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cButton::~cButton()
{
}

void cButton::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	
}
