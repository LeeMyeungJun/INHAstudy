#include "stdafx.h"
#include "cOBB.h"
#include "cSkinnedMesh.h"

cOBB::cOBB()
{
}

cOBB::~cOBB()
{
}

void cOBB::Setup(cSkinnedMesh* pSkinnedMesh)
{
	D3DXVECTOR3 vMin = pSkinnedMesh->GetMin();
	D3DXVECTOR3 vMax = pSkinnedMesh->GetMax();

	m_vOrigCenterPos = (vMin + vMax) / 2.0f;
	m_vOrigAxidDir[0] = D3DXVECTOR3(1, 0, 0);
	m_vOrigAxidDir[1] = D3DXVECTOR3(0, 1, 0);
	m_vOrigAxidDir[2] = D3DXVECTOR3(0, 0, 1);

	m_fAxisLen[0] = fabs(vMax.x - vMin.x);
	m_fAxisLen[1] = fabs(vMax.y - vMin.y);
	m_fAxisLen[2] = fabs(vMax.z - vMin.z);

	m_fAxisHalfLen[0] = m_fAxisLen[0] / 2.0f;
	m_fAxisHalfLen[1] = m_fAxisLen[1] / 2.0f;
	m_fAxisHalfLen[2] = m_fAxisLen[2] / 2.0f;
	
	m_vecOBBBOXVertex.resize(8);
	//0���� 
	m_vecOBBBOXVertex[0] = D3DXVECTOR3()

	
	D3DXMatrixIdentity(&m_matWorldTM);
}

void cOBB::Update(D3DXMATRIXA16* pmatWorld)
{
	if (pmatWorld)
		m_matWorldTM = *pmatWorld;

	for(int i = 0; i < 3; i++)
	{
		D3DXVec3TransformNormal(&m_vAxisDir[i], &m_vOrigAxidDir[i], &m_matWorldTM);
	}

	D3DXVec3TransformCoord(&m_vCenterPos, &m_vOrigCenterPos, &m_matWorldTM);

	
}

bool cOBB::IsCollision(cOBB* pOBB1, cOBB* pOBB2)
{
	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;
	const float cutoff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = pOBB2->m_vCenterPos - pOBB1->m_vCenterPos;

	for(int a = 0; a < 3; a++)
	{
		for(int b = 0; b < 3; b++)
		{
			cos[a][b] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &pOBB2->m_vAxisDir[b]);
			absCos[a][b] = abs(cos[a][b]);

			if (absCos[a][b] > cutoff)	//���� ���� �̻�
				existsParallelPair = true;
		}
		dist[a] = D3DXVec3Dot(&pOBB1->m_vAxisDir[a], &D);
		
		r = abs(dist[a]);
		r0 = pOBB1->m_fAxisHalfLen[a];
		r1 = pOBB2->m_fAxisHalfLen[0] * absCos[a][0] + pOBB2->m_fAxisHalfLen[1] * absCos[a][1] + pOBB2->m_fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)	//�浹x
			return false;
	}

	for(int b = 0; b < 3; b++)
	{
		r = abs(D3DXVec3Dot(&pOBB2->m_vAxisDir[b], &D));
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[0][b] + pOBB1->m_fAxisHalfLen[1] * absCos[1][b] + pOBB1->m_fAxisHalfLen[2] * absCos[2][b];
		r1 = pOBB2->m_fAxisHalfLen[b];

		if (r > r0 + r1)
			return false;
	}

	if (existsParallelPair)
	{
		return true;
	}
	
	{
		//0
		r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][0] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[1][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
		if (r > r0 + r1) return false;

		r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
		if (r > r0 + r1) return false;

		r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][2];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] + pOBB1->m_fAxisHalfLen[1] * absCos[1][0];
		if (r > r0 + r1) return false;

		//1=====================================================================================
		r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][0] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[2][1];
		if (r > r0 + r1) return false;

		r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][1];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[2][0];
		if (r > r0 + r1) return false;

		r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
		r0 = pOBB1->m_fAxisHalfLen[0] * absCos[1][2] + pOBB1->m_fAxisHalfLen[1] * absCos[0][2];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[2][1] + pOBB1->m_fAxisHalfLen[1] * absCos[2][0];
		if (r > r0 + r1) return false;

		//2====================================================================================
		r = abs(dist[2] * cos[1][0] - dist[2] * cos[1][1]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][0];
		r1 = pOBB1->m_fAxisHalfLen[1] * absCos[0][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][1];
		if (r > r0 + r1) return false;

		r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][1] + pOBB1->m_fAxisHalfLen[2] * absCos[1][1];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][2] + pOBB1->m_fAxisHalfLen[2] * absCos[0][0];
		if (r > r0 + r1) return false;

		r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
		r0 = pOBB1->m_fAxisHalfLen[1] * absCos[2][2] + pOBB1->m_fAxisHalfLen[2] * absCos[1][2];
		r1 = pOBB1->m_fAxisHalfLen[0] * absCos[0][1] + pOBB1->m_fAxisHalfLen[1] * absCos[0][0];
		if (r > r0 + r1) return false;
	}

	return true;
}

void cOBB::OBBBOX_Render(D3DCOLOR c)
{
	
}
