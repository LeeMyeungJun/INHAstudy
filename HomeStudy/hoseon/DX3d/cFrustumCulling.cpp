#include "stdafx.h"
#include "cFrustumCulling.h"

cFrustumCulling::cFrustumCulling()
{
}

cFrustumCulling::~cFrustumCulling()
{
}

void cFrustumCulling::Setup_Frustum()
{
	D3DXMATRIXA16 proj;
	D3DXMATRIXA16 view;

	D3DXMatrixIdentity(&proj);
	D3DXMatrixIdentity(&view);

	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);
	
	m_vecVertex.resize(8);
	m_vecVertex[0].p.x = -1.0f;	m_vecVertex[0].p.y = -1.0f;	m_vecVertex[0].p.z = -1.0f;
	m_vecVertex[1].p.x = -1.0f;	m_vecVertex[1].p.y = 1.0f;	m_vecVertex[1].p.z = -1.0f;
	m_vecVertex[2].p.x = 1.0f;	m_vecVertex[2].p.y = 1.0f;	m_vecVertex[2].p.z = -1.0f;
	m_vecVertex[3].p.x = 1.0f;	m_vecVertex[3].p.y = -1.0f;	m_vecVertex[3].p.z = -1.0f;

	m_vecVertex[4].p.x = -1.0f;	m_vecVertex[4].p.y = -1.0f;	m_vecVertex[4].p.z = 1.0f;
	m_vecVertex[5].p.x = -1.0f;	m_vecVertex[5].p.y = 1.0f;	m_vecVertex[5].p.z = 1.0f;
	m_vecVertex[6].p.x = 1.0f;	m_vecVertex[6].p.y = 1.0f;	m_vecVertex[6].p.z = 1.0f;
	m_vecVertex[7].p.x = 1.0f;	m_vecVertex[7].p.y = -1.0f;	m_vecVertex[7].p.z = 1.0f;
}

void cFrustumCulling::Setup_Sphere()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);
	
	for (int i = 0; i < 20; i++)
	{
		for(int j = 0; j < 20; j++)
		{
			for(int k = 0; k < 20; k++)
			{
				ST_SPHERE s;
				s.fRadius = 0.5f;
				s.vCenter = D3DXVECTOR3(i, j, k);
				m_vecSphere.push_back(s);
			}
		}
	}

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
}

void cFrustumCulling::Update()
{
	D3DXMATRIXA16 proj;
	D3DXMATRIXA16 view;

	D3DXMatrixIdentity(&proj);
	D3DXMatrixIdentity(&view);

	g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &proj);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &view);

	m_vecProjVertex.resize(m_vecVertex.size());
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecProjVertex[i].p, &m_vecVertex[i].p, NULL, &proj, &view, NULL);
	}

	m_vecPlane.resize(6);

	//front
	D3DXPlaneFromPoints(&m_vecPlane[0], &m_vecProjVertex[0].p, &m_vecProjVertex[1].p, &m_vecProjVertex[2].p);
	//right
	D3DXPlaneFromPoints(&m_vecPlane[1], &m_vecProjVertex[3].p, &m_vecProjVertex[2].p, &m_vecProjVertex[6].p);
	//top
	D3DXPlaneFromPoints(&m_vecPlane[2], &m_vecProjVertex[1].p, &m_vecProjVertex[5].p, &m_vecProjVertex[6].p);
	//left
	D3DXPlaneFromPoints(&m_vecPlane[3], &m_vecProjVertex[4].p, &m_vecProjVertex[5].p, &m_vecProjVertex[1].p);
	//bottom
	D3DXPlaneFromPoints(&m_vecPlane[4], &m_vecProjVertex[4].p, &m_vecProjVertex[0].p, &m_vecProjVertex[3].p);
	//back
	D3DXPlaneFromPoints(&m_vecPlane[5], &m_vecProjVertex[7].p, &m_vecProjVertex[6].p, &m_vecProjVertex[5].p);
}

void cFrustumCulling::Render_sphere()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	matWorld = matS * matR;

	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		if(m_vecSphere[i].isInFrustum == true)
		{
			D3DXMatrixIdentity(&matWorld);
			matWorld._41 = m_vecSphere[i].vCenter.x;
			matWorld._42 = m_vecSphere[i].vCenter.y;
			matWorld._43 = m_vecSphere[i].vCenter.z;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			g_pD3DDevice->SetTexture(0, NULL);
			g_pD3DDevice->SetMaterial(&m_stMtlSphere);
			m_pMeshSphere->DrawSubset(0);
		}
	}
}

void cFrustumCulling::FrustumCulling()
{
	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		for (int j = 0; j < m_vecPlane.size(); j++)
		{
			if (D3DXPlaneDotCoord(&m_vecPlane[j], &m_vecSphere[i].vCenter) < 0)		//절두체 안쪽
			{
				m_vecSphere[i].isInFrustum = true;
			}
			else
			{
				m_vecSphere[i].isInFrustum = false;
				break;
			}
		}
	}
}
