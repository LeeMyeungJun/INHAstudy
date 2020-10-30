#pragma once
class cSpriteNode;
class cBtnSprite;

class cButton
{
public:
	struct Sprite
	{
		D3DXVECTOR2 st_SpriteSize;
		D3DXVECTOR2 st_Position;
	};
	
public:
	cButton();
	virtual ~cButton();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	virtual void Move(D3DXVECTOR2 vMove);
	virtual bool InCheck(POINT pt);
	virtual void BtnOnOff();

	
public:
	cSpriteNode*		m_pRoot;
	D3DXMATRIXA16		m_matWorld;

	vector<Sprite>		m_vecSprite;
	vector<cBtnSprite*> m_vecBtn;

	
	D3DXVECTOR2			m_vPosition;
	D3DXVECTOR2			m_vSize;
	POINT				m_ptMouseClick;
	POINT				m_ptMouseMove;
	bool				m_isMouseDown; //보드판 다운
	bool				m_isMouseBtnDown; //버튼 다운
	
	bool				m_isOnOff; //버튼의 기능 활성화

};

