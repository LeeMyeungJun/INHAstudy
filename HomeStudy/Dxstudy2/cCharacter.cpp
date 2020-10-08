#include "stdafx.h"
#include "cCharacter.h"
#include "cPath.h"
#include "cHex.h"


cCharacter::cCharacter()
	:m_fRotY(0.0f)
	,m_vDirection(0,0,1)
	,m_vOldDirection(0,0,1)
	,m_vPosition(0,0.9f,0)
	,m_pPath(NULL)
	,m_pHex(NULL)
	,m_iIndex(0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
	delete[] m_pPath;
	SafeDelete(m_pHex);
}

void cCharacter::Setup()
{
	m_pPath = new cPath[6];
	m_pHex = new cHex;
	m_pHex->Setup();
	
	
	m_iIndex = 0;

	m_pPath[0].set_m_v_direction(&m_vDirection);
	m_pPath[0].set_m_v_position(&m_vPosition);
	m_pPath[0].set_m_v_node(m_pHex->m_vHexagon[0]);


	m_pPath[1].set_m_v_direction(&m_vDirection);
	m_pPath[1].set_m_v_position(&m_vPosition);
	m_pPath[1].set_m_v_node(m_pHex->m_vHexagon[1]);

	m_pPath[2].set_m_v_direction(&m_vDirection);
	m_pPath[2].set_m_v_position(&m_vPosition);
	m_pPath[2].set_m_v_node(m_pHex->m_vHexagon[2]);

	m_pPath[3].set_m_v_direction(&m_vDirection);
	m_pPath[3].set_m_v_position(&m_vPosition);
	m_pPath[3].set_m_v_node(m_pHex->m_vHexagon[3]);

	m_pPath[4].set_m_v_direction(&m_vDirection);
	m_pPath[4].set_m_v_position(&m_vPosition);
	m_pPath[4].set_m_v_node(m_pHex->m_vHexagon[4]);

	m_pPath[5].set_m_v_direction(&m_vDirection);
	m_pPath[5].set_m_v_position(&m_vPosition);
	m_pPath[5].set_m_v_node(m_pHex->m_vHexagon[5]);




	
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
	}*/

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR,matT;
	D3DXMatrixRotationY(&matR, m_fRotY);
	//D3DXVECTOR3 temp(0.1f, 0.1f, 0.1f);

	
	m_pPath[m_iIndex].Update(&matR);

	if (fabs(m_vPosition.x - m_pPath[m_iIndex].get_m_v_node().x) < 0.1f
		&& fabs(m_vPosition.z - m_pPath[m_iIndex].get_m_v_node().z) < 0.1f)
	{
		if (m_iIndex == 5)
		{
			m_iIndex = 0;
		}
		else
		{
			m_iIndex++;
		}

		//D3DXMatrixRotationY(&matR, D3DXToRadian(60));
		
		//D3DXMatrixRotationY(&matR, m_fRotY);
		//m_fRotY += acosf(D3DXVec3Dot(&m_vOldDirection,&m_vDirection));
		//m_vOldDirection = m_vDirection;
		//m_fRotY += D3DX_PI/3;
		//D3DXMatrixRotationY(&matR, m_fRotY);
		
	}

	
	//m_vDirection = D3DXVECTOR3(0, 0, 1);
	//D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
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
