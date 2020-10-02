#include "stdafx.h"
#include "cLeftArm.h"


cLeftArm::cLeftArm()
{
}


cLeftArm::~cLeftArm()
{
}

void cLeftArm::Setup()
{
	cCubeNode::Setup();
	D3DXMATRIXA16 matS, matT, mat;
	D3DXMatrixScaling(&matS, 0.2f, 0.6f, 0.2f);
	D3DXMatrixTranslation(&matT, -0.3f, -0.3f, 0.0f);
	mat = matS * matT;


	{

		//front
		m_vecVertex[0].t = D3DXVECTOR2(44.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[1].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[2].t = D3DXVECTOR2(48.0f / 64.0f, 20.0f / 32.0f);

		m_vecVertex[3].t = D3DXVECTOR2(44.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[4].t = D3DXVECTOR2(48.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[5].t = D3DXVECTOR2(48.0f / 64.0f, 32.0f / 32.0f);

		//back
		m_vecVertex[6].t = D3DXVECTOR2(52.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[7].t = D3DXVECTOR2(56.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[8].t = D3DXVECTOR2(52.0f / 64.0f, 20.0f / 32.0f);

		m_vecVertex[9].t = D3DXVECTOR2(52.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[10].t = D3DXVECTOR2(56.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[11].t = D3DXVECTOR2(56.0f / 64.0f, 20.0f / 32.0f);

		//left
		m_vecVertex[12].t = D3DXVECTOR2(40.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[13].t = D3DXVECTOR2(40.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[14].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);

		m_vecVertex[15].t = D3DXVECTOR2(40.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[16].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[17].t = D3DXVECTOR2(44.0f / 64.0f, 32.0f / 32.0f);

		//right
		m_vecVertex[18].t = D3DXVECTOR2(40.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[19].t = D3DXVECTOR2(40.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[20].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);

		m_vecVertex[21].t = D3DXVECTOR2(40.0f / 64.0f, 32.0f / 32.0f);
		m_vecVertex[22].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[23].t = D3DXVECTOR2(44.0f / 64.0f, 32.0f / 32.0f);

		//top
		m_vecVertex[24].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[25].t = D3DXVECTOR2(44.0f / 64.0f, 16.0f / 32.0f);
		m_vecVertex[26].t = D3DXVECTOR2(48.0f / 64.0f, 16.0f / 32.0f);

		m_vecVertex[27].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[28].t = D3DXVECTOR2(48.0f / 64.0f, 16.0f / 32.0f);
		m_vecVertex[29].t = D3DXVECTOR2(48.0f / 64.0f, 20.0f / 32.0f);

		//bottom
		m_vecVertex[30].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[31].t = D3DXVECTOR2(44.0f / 64.0f, 16.0f / 32.0f);
		m_vecVertex[32].t = D3DXVECTOR2(48.0f / 64.0f, 16.0f / 32.0f);

		m_vecVertex[33].t = D3DXVECTOR2(44.0f / 64.0f, 20.0f / 32.0f);
		m_vecVertex[34].t = D3DXVECTOR2(48.0f / 64.0f, 16.0f / 32.0f);
		m_vecVertex[35].t = D3DXVECTOR2(48.0f / 64.0f, 20.0f / 32.0f);

	}


	
	for (size_t i = 0; i<m_vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&m_vecVertex[i].p, &m_vecVertex[i].p, &mat);
	}
	//이게 기준점 
	m_vLocalPos.y = 0.3f;

}
