#include "stdafx.h"
#include "cCharacter.h"
#include "cMap.h"
#include "cGroup.h"

cCharacter::cCharacter():m_fRotY(0.0f), m_vDirection(0, 0, 1), m_vPosition(0, 0, 0), m_vPostPos(5, 1, 0), 
						m_vRayPos(0, 0, 0), m_vRayDir(0, -1, 0), m_vPrevPos(0, 0, 0)
{
	D3DXMatrixIdentity(&m_matWorld);
}

cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
}

void cCharacter::Update(iMap* pMap)
{
	if (GetKeyState('A') & 0X8000)
	{
		m_fRotY -= 0.1f;
	}
	if (GetKeyState('D') & 0X8000)
	{
		m_fRotY += 0.1f;
	}
	
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, -1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	
	D3DXVECTOR3 vPosition = m_vPosition;

	if (GetKeyState('W') & 0X8000)
	{
		vPosition = m_vPosition + (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0X8000)
	{
		vPosition = m_vPosition - (m_vDirection * 0.1f);
	}

	/*if (pMap)
	{
		if (pMap->GetHeight(vPosition.x, vPosition.y, vPosition.z))
		{
			m_vPosition = vPosition;
		}
	}*/
	m_vPosition = vPosition;

	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y /*+ 1.0f*/, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCharacter::Render()
{
}

void cCharacter::KeyInput()
{
	/*if (GetKeyState('A') & 0x8000)
		m_fRotY -= 0.1f;
	else if (GetKeyState('D') & 0x8000)
		m_fRotY += 0.1f;

	D3DXVECTOR3 vPosition = m_vPosition;

	if (GetKeyState('W') & 0x8000)
	{
		vPosition += m_vPosition + (m_vDirection * 0.1f);
	}
	else if (GetKeyState('S') & 0x8000)
	{
		vPosition -= m_vPosition + (m_vDirection * 0.1f);
	}*/
}

D3DXVECTOR3& cCharacter::GetPosition()
{
	return m_vPosition;
}
