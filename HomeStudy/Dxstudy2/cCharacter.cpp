#include "stdafx.h"
#include "cCharacter.h"
#include "cObjLoader.h"


cCharacter::cCharacter()
	:m_fRotY(0.0f)
	,m_vDirection(0,0,1)
	,m_vPosition(0,0.9f,0)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cCharacter::~cCharacter()
{
}

void cCharacter::Setup()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "map_surface.obj");

}

void cCharacter::Update()
{
	PlayerMove();

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 matR, matT;
	D3DXMatrixRotationY(&matR, m_fRotY);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);
	m_matWorld = matR * matT;
}

void cCharacter::Render()
{
}

bool cCharacter::CollisionCheck(D3DXVECTOR3 temp)
{
	
	vector<ST_PNT_VERTEX> vecTemp = m_vecGroup[0]->GetVertex();
	D3DXVECTOR3 vecRayPos = m_vPosition;
	vecRayPos.y = 100;
	for (int i = 0; i < vecTemp.size(); i += 3)
	{
		float pDist;
		if(D3DXIntersectTri(&vecTemp[i].p, &vecTemp[i + 1].p, &vecTemp[i + 2].p, &vecRayPos, &D3DXVECTOR3(0, -1, 0), 0, 0, &pDist))
		{
			m_vPosition.y = (100.9f - pDist);
			return false;
		}
		else
		{
			m_vPosition.y = 0.9f;
		}
			
		
	}
	return false;
}

void cCharacter::PlayerMove()
{
	//RotY Set
	{
		if (GetKeyState('A') & 0X8000)
		{
			m_fRotY -= 0.1f;
		}

		if (GetKeyState('D') & 0X8000)
		{
			m_fRotY += 0.1f;
		}
	}

	D3DXVECTOR3 temp = m_vPosition;


	if (GetKeyState('W') & 0X8000)
	{
		temp += (m_vDirection * 0.1f);
	}
	if (GetKeyState('S') & 0X8000)
	{
		temp -= (m_vDirection * 0.1f);
	}

	if (!CollisionCheck(temp))
	{
		m_vPosition = temp;
	}


}

D3DXVECTOR3& cCharacter::GetPosition()
{
	return m_vPosition;
}

D3DXVECTOR3& cCharacter::GetDirection()
{
	return m_vDirection;
}
