#include "stdafx.h"
#include "cRay.h"


cRay::cRay()
	: m_vOrg(0,0,0)
	, m_vDir(0,0,0)
	, m_eRaySpace(E_NONE)
{
}


cRay::~cRay()
{
}

cRay cRay::RayAtViewSpace(int nScreenX, int nScreenY)
{
	D3DVIEWPORT9	vp;
	g_pD3DDvice->GetViewport(&vp);
	D3DXMATRIXA16 matProj;
	g_pD3DDvice->GetTransform(D3DTS_PROJECTION, &matProj);

	cRay r;
	r.m_vDir.x = ((2.0*nScreenX) / vp.Width - 1.0f) / matProj._11;
	r.m_vDir.y = ((-2.0*nScreenY) / vp.Height + 1.0f) / matProj._22;
	r.m_vDir.z = 1.0f;

	r.m_eRaySpace = E_VIEW;

	return r;
}

cRay cRay::RayAtWorldSpace(int nScreenX, int nScreenY)
{
	cRay r = cRay::RayAtViewSpace(nScreenX, nScreenY);
	D3DXMATRIXA16 matView, matInvVIew;
	g_pD3DDvice->GetTransform(D3DTS_VIEW, &matView);

	D3DXMatrixInverse(&matInvVIew, 0, &matView);

	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvVIew); //포지션이고
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvVIew); // 벡터야
	//방향베겉는 노말라이즈 시켜주고
	D3DXVec3Normalize(&r.m_vDir, &r.m_vDir);
	r.m_eRaySpace = E_WORLD;
	return r;
}

bool cRay::IntersectTri(D3DXVECTOR3& v0, D3DXVECTOR3& v1, D3DXVECTOR3& v2, D3DXVECTOR3& vPickedPosition)
{
	float u, v, f;
	bool b = D3DXIntersectTri(&v0, &v1, &v2, &m_vOrg, &m_vDir, &u, &v, &f);//바닥하고 충돌 체크용인거야
	vPickedPosition = m_vOrg + f*m_vDir;
	return b;

}

bool cRay::IsPicked(ST_SPHERE* pSphere)
{
	//방법 1"(원일경우에만 됨)
	return D3DXSphereBoundProbe(&pSphere->vCenter, pSphere->fRadius, &m_vOrg, &m_vDir);
	//방법 2
	cRay r = (*this);
	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixIdentity(&matInvWorld);
	matInvWorld._41 = -pSphere->vCenter.x;
	matInvWorld._42 = -pSphere->vCenter.y;
	matInvWorld._43 = -pSphere->vCenter.z;

	D3DXVec3TransformCoord(&r.m_vOrg, &r.m_vOrg, &matInvWorld); //포지션이고
	D3DXVec3TransformNormal(&r.m_vDir, &r.m_vDir, &matInvWorld); // 벡터야

	//(Q.V)^2 - V.V*(Q.Q - r*r) > 0 머다하고 공식이 책에있어
	float vv = D3DXVec3Dot(&r.m_vDir, &r.m_vDir);
	float qv = D3DXVec3Dot(&r.m_vOrg, &r.m_vDir);
	float qq = D3DXVec3Dot(&r.m_vOrg, &r.m_vOrg);
	float rr = pSphere->fRadius * pSphere->fRadius;
	return qv*qv - vv* (qq - rr) >= 0; //충돌이냐 아니냐로 이걸로 판단

}
