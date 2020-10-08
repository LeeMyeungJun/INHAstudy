#include "stdafx.h"
#include "cPath.h"


void cPath::Update(D3DXMATRIXA16* matR)
{
	D3DXMATRIXA16 temp;
	D3DXMatrixIdentity(&temp);
	
	D3DXVECTOR3 vUp(0,1,0);
	m_vNode.y = 0.9f; //

	
	D3DXMatrixLookAtLH(matR, &D3DXVECTOR3(0,0,0), &(m_vNode - *m_vPosition), &vUp);
	D3DXMatrixTranspose(matR, matR);//��ġ����� �����ش� . ������� �ٲ���
	*m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(m_vDirection, m_vDirection, matR);

	*m_vPosition += (*m_vDirection * 0.1f);


	//��Ʈ���� R�� �������ִ°ɷ� �����ϰ� �ι������ڸ� �������ִ°ɷ� �����ϰ� �𷺼� ����س�Ÿ� 
}

cPath::cPath()
	:m_vPosition(NULL)
	,m_vNode(0,0,0)
{
	
}


cPath::~cPath()
{

}
