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


	vector<D3DXVECTOR2> m_SpriteSize;
	vector<D3DXVECTOR2> m_SpritePosition;
	POINT				m_ptMouseClick;
	POINT				m_ptMouseMove;
	POINT				m_ptPosition;
	bool				m_isMouseButtonDown;

};

