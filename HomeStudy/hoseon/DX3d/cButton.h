#pragma once
class cSpriteNode;

class cButton
{
public:
	cButton();
	virtual ~cButton();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	
public:
	cSpriteNode*		m_pRoot;
	D3DXMATRIXA16		m_matWorld;


	//선택된순간 잡은순간 이동할떄마다 차만큼 이동시켜주라구

};

