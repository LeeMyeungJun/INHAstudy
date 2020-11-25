#include "stdafx.h"
#include "cHead.h"


cHead::cHead()
{
}


cHead::~cHead()
{
}

void cHead::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16	matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.4f, 0.4f, 0.4f);
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	mat = matS * matT;

	for (size_t i = 0; i < m_vecVertex.size(); ++i)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}

	m_vLocalPos.y = 0.5f;

	//left
	m_vecVertex[0].t = D3DXVECTOR2(0, 4.0f / 8.0f);
	m_vecVertex[1].t = D3DXVECTOR2(0, 2.0f / 8.0f);
	m_vecVertex[2].t = D3DXVECTOR2(1.0f / 8.0f, 2.0f / 8.0f);

	m_vecVertex[3].t = D3DXVECTOR2(0, 4.0f / 8.0f);
	m_vecVertex[4].t = D3DXVECTOR2(1.0f / 8.0f, 1.0f / 4.0f);
	m_vecVertex[5].t = D3DXVECTOR2(1.0f / 8.0f, 1.0f / 2.0f);
	//front
	m_vecVertex[6].t = D3DXVECTOR2(3.0f / 8.0f, 4.0f / 8.0f);
	m_vecVertex[7].t = D3DXVECTOR2(3.0f / 8.0f, 2.0f / 8.0f);
	m_vecVertex[8].t = D3DXVECTOR2(4.0f / 8.0f, 2.0f / 8.0f);

	m_vecVertex[9].t = D3DXVECTOR2(3.0f / 8.0f, 4.0f / 8.0f);
	m_vecVertex[10].t = D3DXVECTOR2(4.0f / 8.0f, 2.0f / 8.0f);
	m_vecVertex[11].t = D3DXVECTOR2(4.0f / 8.0f, 4.0f / 8.0f);
	//right
	m_vecVertex[12].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 2.0f);
	m_vecVertex[13].t = D3DXVECTOR2(3.0f / 8.0f, 1.0f / 4.0f);
	m_vecVertex[14].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 4.0f);

	m_vecVertex[15].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 2.0f);
	m_vecVertex[16].t = D3DXVECTOR2(3.0f / 8.0f, 1.0f / 4.0f);
	m_vecVertex[17].t = D3DXVECTOR2(3.0f / 8.0f, 1.0f / 2.0f);
	//back
	m_vecVertex[18].t = D3DXVECTOR2(1.0f / 8.0f, 1.0f / 2.0f);
	m_vecVertex[20].t = D3DXVECTOR2(1.0f / 8.0f, 1.0f / 4.0f);
	m_vecVertex[19].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 4.0f);

	m_vecVertex[21].t = D3DXVECTOR2(1.0f / 8.0f, 1.0f / 2.0f);
	m_vecVertex[23].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 4.0f);
	m_vecVertex[22].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 2.0f);
	//top
	m_vecVertex[24].t = D3DXVECTOR2(1.0f / 8.0f, 2.0f / 8.0f);
	m_vecVertex[25].t = D3DXVECTOR2(1.0f / 8.0f, 0);
	m_vecVertex[26].t = D3DXVECTOR2(2.0f / 8.0f, 0);

	m_vecVertex[27].t = D3DXVECTOR2(1.0f / 8.0f, 2.0f / 8.0f);
	m_vecVertex[28].t = D3DXVECTOR2(1.0f / 4.0f, 0);
	m_vecVertex[29].t = D3DXVECTOR2(2.0f / 8.0f, 2.0f / 8.0f);
	//bottom
	m_vecVertex[30].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 4.0f);
	m_vecVertex[31].t = D3DXVECTOR2(1.0f / 4.0f, 0);
	m_vecVertex[32].t = D3DXVECTOR2(3.0f / 8.0f, 0);

	m_vecVertex[33].t = D3DXVECTOR2(1.0f / 4.0f, 1.0f / 4.0f);
	m_vecVertex[34].t = D3DXVECTOR2(3.0f / 8.0f, 0);
	m_vecVertex[35].t = D3DXVECTOR2(3.0f / 8.0f, 1.0f / 4.0f);
}