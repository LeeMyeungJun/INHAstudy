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


	//���õȼ��� �������� �̵��ҋ����� ����ŭ �̵������ֶ�

};

