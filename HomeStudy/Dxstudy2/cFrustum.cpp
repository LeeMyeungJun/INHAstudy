#include "stdafx.h"
#include "cFrustum.h"


cFrustum::cFrustum()
	:m_Pos(0,0,0)
{


}


cFrustum::~cFrustum()
{

}

void cFrustum::Setup()
{
	m_vecVertex.resize(8); //8개의 정점
	//
	//버텍스에대한 정보
	m_vecVertex[0].x = -0.5f;   m_vecVertex[0].y = -0.5f;   m_vecVertex[0].z = -0.5f;
	m_vecVertex[1].x = -0.5f;   m_vecVertex[1].y = 0.5f;    m_vecVertex[1].z = -0.5f;
	m_vecVertex[2].x = 0.5f;    m_vecVertex[2].y = 0.5f;    m_vecVertex[2].z = -0.5f;
	m_vecVertex[3].x = 0.5f;    m_vecVertex[3].y = -0.5f;   m_vecVertex[3].z = -0.5f;

	m_vecVertex[4].x = -0.5f;   m_vecVertex[4].y = -0.5f;   m_vecVertex[4].z = 0.5f;
	m_vecVertex[5].x = -0.5f;   m_vecVertex[5].y = 0.5f;    m_vecVertex[5].z = 0.5f;
	m_vecVertex[6].x = 0.5f;    m_vecVertex[6].y = 0.5f;    m_vecVertex[6].z = 0.5f;
	m_vecVertex[7].x = 0.5f;    m_vecVertex[7].y = -0.5f;   m_vecVertex[7].z = 0.5f;


	D3DXMATRIXA16 view, proj;
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&proj);

	g_pD3DDvice->GetTransform(D3DTS_VIEW, &view);
	g_pD3DDvice->GetTransform(D3DTS_PROJECTION, &proj);

	m_vecFrustum.resize(m_vecVertex.size());
	for(int i = 0 ; i < m_vecVertex.size() ; i++)
	{
		D3DXVec3Unproject(&m_vecFrustum[i], &m_vecVertex[i], NULL, &proj, &view, NULL);
	}


	m_plnae.resize(6);
	
	D3DXPlaneFromPoints(&m_plnae[0], &m_vecFrustum[0], &m_vecFrustum[1], &m_vecFrustum[2]); //앞면
	D3DXPlaneFromPoints(&m_plnae[1], &m_vecFrustum[4], &m_vecFrustum[5], &m_vecFrustum[1]); // 왼쪽면
	D3DXPlaneFromPoints(&m_plnae[2], &m_vecFrustum[7], &m_vecFrustum[6], &m_vecFrustum[5]); // 뒷면
	D3DXPlaneFromPoints(&m_plnae[3], &m_vecFrustum[7], &m_vecFrustum[6], &m_vecFrustum[2]); //우
	D3DXPlaneFromPoints(&m_plnae[4], &m_vecFrustum[0], &m_vecFrustum[3], &m_vecFrustum[7]); //윗면
	D3DXPlaneFromPoints(&m_plnae[5], &m_vecFrustum[1], &m_vecFrustum[5], &m_vecFrustum[6]); //아랫면





}

void cFrustum::Update()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMATRIXA16 view, proj;
	D3DXMatrixIdentity(&view);
	D3DXMatrixIdentity(&proj);

	g_pD3DDvice->GetTransform(D3DTS_VIEW, &view);
	g_pD3DDvice->GetTransform(D3DTS_PROJECTION, &proj);

	//D3DXPlaneFromPoints()
	//D3DXPlaneDotCoord()

}

bool cFrustum::InternalCheck(D3DXVECTOR3* vecPoint)
{
	return false;
}

void cFrustum::Render()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, TRUE);
	g_pD3DDvice->SetTexture(0, NULL);
	D3DXMATRIXA16   matWorld, matT;
	{
		g_pD3DDvice->SetMaterial(&m_stMtlSphere);

		for (int z = -12; z < 12; ++z)
		{
			for (int y = 12; y > -12; --y)
			{
				for (int x = 12; x > -12; --x)
				{
					D3DXMatrixIdentity(&matWorld);
					D3DXMatrixTranslation(&matT, x, y, z);
					matWorld = matWorld * matT;
					g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
					m_vecMeshSphere[+x]_->DrawSubset(0);
					
				}
			}
		}
	}

}
