#include "stdafx.h"
#include "cPath.h"


void cPath::Update(D3DXMATRIXA16* matR)
{
	D3DXMATRIXA16 temp;
	D3DXMatrixIdentity(&temp);
	
	D3DXVECTOR3 vUp(0,1,0);
	m_vNode.y = 0.9f; //

	
	D3DXMatrixLookAtLH(matR, &D3DXVECTOR3(0,0,0), &(m_vNode - *m_vPosition), &vUp);
	D3DXMatrixTranspose(matR, matR);//전치행렬을 시켜준다 . 행과열을 바꿔줌
	*m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(m_vDirection, m_vDirection, matR);

	*m_vPosition += (*m_vDirection * 0.1f);


	//매트릭스 R을 원점에있는걸로 생각하고서 두번쟤인자를 원점에있는걸로 생각하고 디렉션 계싼해논거를 
}

cPath::cPath()
	:m_vPosition(NULL)
	,m_vNode(0,0,0)
{
	
}


cPath::~cPath()
{

}
