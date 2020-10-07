#include "stdafx.h"
#include "cCharacter.h"
#include "cPath.h"


cCharacter::cCharacter()
	:m_fRotY(0.0f)
	,m_vDirection(0,0,1)
	,m_vPosition(0,0.9f,0)
	, m_pPath(NULL)
	, m_iIndex(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
	delete[] m_pPath;
}

void cCharacter::Setup()
{
	D3DXVECTOR3 temp;
	
	m_pPath = new cPath[6];
	
	m_pPath[0].set_m_next_node(&m_pPath[1]);
	m_pPath[0].set_m_v_direction(&m_vDirection);
	temp = D3DXVECTOR3(-10, m_vPosition.y, -10);
	m_pPath[0].set_m_v_node(temp);
	m_pPath[0].set_m_v_position(&m_vPosition);

	m_pPath[1].set_m_next_node(&m_pPath[0]);
	m_pPath[1].set_m_v_direction(&m_vDirection);
	temp = D3DXVECTOR3(10, m_vPosition.y, 10);
	m_pPath[1].set_m_v_node(temp);
	m_pPath[1].set_m_v_position(&m_vPosition);

}

void cCharacter::Update()
{

	/*if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.1f;
	}

	if (GetKeyState('W') & 0X8000)
	{
		m_vPosition += (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0X8000)
	{
		m_vPosition -= (m_vDirection * 0.1f);
	}
	*/
	//RECT rc;
	//GetClientRect(g_hWnd, &rc);
	if (m_vPosition == m_pPath[m_iIndex].get_m_v_node())
	{
		m_iIndex++;
	}

	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_pPath[m_iIndex].Update();
	m_vDirection = D3DXVECTOR3(0, 0, 1);
	
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR *matT;
}

void cCharacter::Render()
{
}

D3DXVECTOR3& cCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXVECTOR3& cCharacter::GetDirection()
{
	return m_vDirection;
}