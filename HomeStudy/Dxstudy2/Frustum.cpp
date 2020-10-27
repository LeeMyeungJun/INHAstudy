#include "stdafx.h"
#include "Frustum.h"


Frustum::Frustum()
{
}


Frustum::~Frustum()
{
}

void Frustum::Setup()
{
	//버텍스 8개설정하고 면을만들거야
	// : near
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1,  1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1,  1, 0));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1, -1, 0));

	// : far
	m_vecProjVertex.push_back(D3DXVECTOR3(-1, -1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3(-1,  1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1,  1, 1));
	m_vecProjVertex.push_back(D3DXVECTOR3( 1, -1, 1));

	m_vecPlane.resize(6); //6면체니까 6개가나올거고
	m_vecWorldVertex.resize(8); 
	

}

void Frustum::Update()
{
	D3DXMATRIXA16 matView, matProj;
	g_pD3DDvice->GetTransform(D3DTS_PROJECTION, &matProj);
	g_pD3DDvice->GetTransform(D3DTS_VIEW, &matView);

	for(size_t i = 0 ; i < m_vecProjVertex.size() ; i++)
	{
		D3DXVec3Unproject(&m_vecWorldVertex[i], &m_vecProjVertex[i], NULL, &matProj, &matView, NULL);
	}
	/*
	 *			5------------6
	 *		   /|			/|
	 *		 1 ------------2 |
	 *		 |  |		   | |
	 *		 |  |          | |
	 *		 |  4----------|-7
	 *		 |/			   |/
	 *		 0-------------3
	 */

	//면생성 부분
	//:near 
	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecWorldVertex[0], &m_vecWorldVertex[1], &m_vecWorldVertex[2]);
	//:far
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecWorldVertex[6], &m_vecWorldVertex[5], &m_vecWorldVertex[4]);
	//:top
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecWorldVertex[1], &m_vecWorldVertex[5], &m_vecWorldVertex[6]);
	//:bottom
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecWorldVertex[0], &m_vecWorldVertex[3], &m_vecWorldVertex[7]);
	//:left
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecWorldVertex[1], &m_vecWorldVertex[0], &m_vecWorldVertex[4]);
	//:right
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecWorldVertex[2], &m_vecWorldVertex[6], &m_vecWorldVertex[7]);
	
}

bool Frustum::IsIn(ST_SPHERE* pSphere)
{
	for each(D3DXPLANE p in m_vecPlane)
	{
		//반지름보다 크면 밖에쪽에있는것 
		if (D3DXPlaneDotCoord(&p, &pSphere->vCenter) > pSphere->fRadius) return false;
	}
	return true;
}
