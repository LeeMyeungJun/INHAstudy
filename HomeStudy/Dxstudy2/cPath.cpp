#include "stdafx.h"
#include "cPath.h"


void cPath::Update()
{
	D3DXMATRIXA16 temp;
	D3DXMatrixIdentity(&temp);
	
	D3DXVECTOR3 vUp(0,1,0);
	D3DXMatrixLookAtLH(&temp, m_vPosition, &m_vNode, &vUp);
	*m_vDirection = D3DXVECTOR3(0, 0, 1);

	D3DXVec3TransformNormal(m_vDirection, m_vDirection, &temp);
	
	*m_vPosition += (*m_vDirection * 0.1f);
}

cPath::cPath()
	:m_NextNode(NULL)
	,m_vPosition(NULL)
	,m_vNode(0,0,0)
{
}


cPath::~cPath()
{

}
