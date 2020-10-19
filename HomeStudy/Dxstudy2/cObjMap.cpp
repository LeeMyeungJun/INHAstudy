#include "stdafx.h"
#include "cObjMap.h"
#include "cObjLoader.h"

cObjMap::cObjMap(char* szFolder, char* szFile, D3DXMATRIXA16* pmat)
{
	Load(szFolder, szFile, pmat);
}

void cObjMap::Load(char* szFolder, char* szFile, D3DXMATRIXA16* pmat)
{
	cObjLoader l;
	l.LoadSurface(m_vecSurface, szFolder, szFile, pmat);
}

bool cObjMap::GetHeight(float x, float& y, float z)
{
	int rayPosition = 1000;
	D3DXVECTOR3 vRayPos(x, rayPosition, z);
	D3DXVECTOR3 vRayDir(0, -1, 0);

	for(size_t i= 0; i < m_vecSurface.size(); i+= 3)
	{
		float u, v, f;
		if(D3DXIntersectTri(	&m_vecSurface[i+0],
							&m_vecSurface[i + 1] ,
							&m_vecSurface[i + 2] ,
							&vRayPos,
							&vRayDir,
							&u, &v ,&f))
		{
			


			if (rayPosition - f > 2.0f + y || rayPosition - f < y - 2.0f)
				return false;
			else
			{
				y = rayPosition - f;
				return true;
			}

			
			//if(1000 - f - y < 2) //2는 범위값 
			//{
			//	y = 1000 - f;
			//	return true;
			//}
			//if (y  <  1000 - f + 2) //2는 범위값 
			//{
			//	return false;
			//}
			
		}
	}
	return false;
}

cObjMap::~cObjMap()
{
}
