#include "stdafx.h"
#include "cMap.h"
#include "cObjLoader.h"
#include "cGroup.h"

cMap::cMap()
{
}

cMap::~cMap()
{
	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}
	m_vecGroup.clear();
	g_pObjectManager->Destroy();
	g_pTextureManager->Destroy();
}

void cMap::Setup_Obj()
{
	cObjLoader l;
	//l.Load(m_vecGroup, "obj", "box.obj");
	l.Load(m_vecGroup, "obj", "Map.obj");
	l.Load(m_vecMapSurface, "obj", "map_surface.obj");
	vector<ST_PNT_VERTEX> v;
	v = m_vecMapSurface[0]->GetVertex();
	v[0].p[0];
}

void cMap::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
}

vector<cGroup*> cMap::GetVecMapSurface()
{
	return m_vecMapSurface;
}
