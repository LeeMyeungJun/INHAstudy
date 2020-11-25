#include "stdafx.h"
#include "cObjMap.h"
#include "cObjLoader.h"

cObjMap::cObjMap(char* szFolder, char* szFile, D3DXMATRIXA16* pmat)
{
	Load(szFolder, szFile, pmat);
}

cObjMap::~cObjMap()
{
}

void cObjMap::Load(char* szFolder, char* szFile, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	l.LoadSurface(m_vecSurface, szFolder, szFile, pmat);
}

bool cObjMap::GetHeight(float x, float& y, float z)
{
	D3DXVECTOR3 vRayPos(x, 100, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for(size_t i = 0; i < m_vecSurface.size(); i += 3)
	{
		float u, v, f;
		if(D3DXIntersectTri(&m_vecSurface[i + 0], &m_vecSurface[i + 1], &m_vecSurface[i + 2],
							&vRayPos, &vRayDir, &u, &v, &f))
		{
			if (100 - f > 2.0f + y || 100 - f < y -2.0f)
				return false;
			else
			{
				y = 100 - f;
				return true;
			}
		}
	}
	return false;
}