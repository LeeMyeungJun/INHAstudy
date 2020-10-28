#include "stdafx.h"
#include "cSprite.h"


cSprite::cSprite()
	: m_sizeX(0)
	, m_sizeY(0)
	, m_fX(0)
	, m_fY(0)
{
	D3DXMatrixIdentity(&matTranslation);
	Setup();
}


cSprite::~cSprite()
{
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
}

void cSprite::Setup()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}

void cSprite::Update()
{
}

void cSprite::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//�̹��� ���
	RECT rc;
	SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);


	//>>: UI�� ȸ�������� ��ų���־�
	D3DXMATRIXA16 matS, matR,mat;
	//���� ��ġ  matTranslation;

	mat = matTranslation;


	m_pSprite->SetTransform(&mat);

	m_pSprite->Draw(m_pTextureUI,
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_ARGB(150, 255, 255, 255)); // A�� ���ĺ�����


	m_pSprite->End();
}

void cSprite::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		break;
	}
}
