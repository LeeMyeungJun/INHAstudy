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
	//m_pPath = new cPath[6];
	

	m_pHex = new cHex;
	m_pHex->Setup();
	m_pPath = new cPath[m_pHex->m_iSize];
	
	m_iIndex = 0;
	m_iEndIndex = m_pHex->m_iSize;


	for (int i = 0; i < m_iEndIndex; i++)
	{
		m_pPath[i].set_m_v_direction(&m_vDirection);
		m_pPath[i].set_m_v_position(&m_vPosition);
		m_pPath[i].set_m_v_node(m_pHex->m_vecBezierVertex[i].p);
	}





	
}

void cCharacter::Update(iMap* pMap)
{
	/*if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.1f;
	}
	
	D3DXVECTOR3 vPosition = m_vPosition;
	
	if (GetKeyState('W') & 0X8000)
	{
		vPosition  = m_vPosition + (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0X8000)
	{
<<<<<<< HEAD
		m_vPosition -= (m_vDirection * 0.1f);
	}*/

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR,matT;
=======
		vPosition = m_vPosition -(m_vDirection * 0.1f);
	}

	D3DXMATRIXA16 matR, matT;
>>>>>>> 92581022d02896bb4e44749abd9a86cc27bc9803
	D3DXMatrixRotationY(&matR, m_fRotY);
	m_pPath[m_iIndex].Update(&matR);

<<<<<<< HEAD
	if (fabs(m_vPosition.x - m_pPath[m_iIndex].get_m_v_node().x) < 0.1f
		&& fabs(m_vPosition.z - m_pPath[m_iIndex].get_m_v_node().z) < 0.1f)
	{
		if (m_iIndex == m_iEndIndex-1)
		{
			m_iIndex = 0;
		}
		else
		{
			m_iIndex++;
		}
	}
	//m_vDirection = D3DXVECTOR3(0, 0, 1);
	//D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
=======

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);

	//>>:����
	if(pMap)
	{
		if(pMap->GetHeight(vPosition.x,vPosition.y,vPosition.z))
		{
			m_vPosition = vPosition;
		}
	}

	//<<:

	
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y+0.9f, m_vPosition.z);
>>>>>>> 92581022d02896bb4e44749abd9a86cc27bc9803
	m_matWorld = matR * matT;
}

void cCharacter::Render()
{
	m_pHex->Render();
}

D3DXVECTOR3& cCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXVECTOR3& cCharacter::GetDirection()
{
	return m_vDirection;
}
