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

	Setup_Mesh();
	
	m_vecVertex.resize(8); //8개의 정점
	//
	//버텍스에대한 정보
	m_vecVertex[0].x = -1.0f;   m_vecVertex[0].y =  -1.0f;   m_vecVertex[0].z =  -1.0f;
	m_vecVertex[1].x = -1.0f;   m_vecVertex[1].y =   1.0f;    m_vecVertex[1].z = -1.0f;
	m_vecVertex[2].x =  1.0f;    m_vecVertex[2].y =  1.0f;    m_vecVertex[2].z = -1.0f;
	m_vecVertex[3].x =  1.0f;    m_vecVertex[3].y = -1.0f;   m_vecVertex[3].z =  -1.0f;

	m_vecVertex[4].x = -1.0f;   m_vecVertex[4].y = -1.0f;   m_vecVertex[4].z =  1.0f;
	m_vecVertex[5].x = -1.0f;   m_vecVertex[5].y =  1.0f;    m_vecVertex[5].z = 1.0f;
	m_vecVertex[6].x =  1.0f;    m_vecVertex[6].y = 1.0f;    m_vecVertex[6].z = 1.0f;
	m_vecVertex[7].x =  1.0f;    m_vecVertex[7].y =-1.0f;   m_vecVertex[7].z =  1.0f;


	//모니터 크기로하는사람들은 - > 뷰포트를 역행렬을 곱해졌어  ,,  X Y값은 알겠어 Z값은 어떻게구해여 Near Far 이방 법 >


	//이렇게하면되는데 2.0하면 90도로보여서 우리눈에는안보임  1.0 1.0 이 45도임
	//m_vecVertex[0].x = -2.0f;    m_vecVertex[0].y = -2.0f;   m_vecVertex[0].z = - 1.0f;
	//m_vecVertex[1].x = -2.0f;    m_vecVertex[1].y =  2.0f;    m_vecVertex[1].z = -1.0f;
	//m_vecVertex[2].x =  2.0f;    m_vecVertex[2].y =  2.0f;    m_vecVertex[2].z = -1.0f;
	//m_vecVertex[3].x =  2.0f;    m_vecVertex[3].y = -2.0f;   m_vecVertex[3].z = - 1.0f;

	//m_vecVertex[4].x = -2.0f;    m_vecVertex[4].y = -2.0f;   m_vecVertex[4].z =  1.0f;
	//m_vecVertex[5].x = -2.0f;    m_vecVertex[5].y =  2.0f;    m_vecVertex[5].z = 1.0f;
	//m_vecVertex[6].x =  2.0f;    m_vecVertex[6].y = 2.0f;    m_vecVertex[6].z =  1.0f;
	//m_vecVertex[7].x =  2.0f;    m_vecVertex[7].y = -2.0f;   m_vecVertex[7].z =  1.0f;


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

	m_vecFrustum.resize(m_vecVertex.size());
	

	//우리는 1 -1 이게 곱하게되면은 로컬좌표에있는 버텍스잖아 근데우리가 로컬좌표에있는값은 뷰포트에 넘어가게되면은 월드 다음에 처리된거라서 
	//뷰포트를 다시넣게되면은 그값이 로컬로 왔을때 역행렬로 곱해줬을떄 

	//버텍스에 뷰포트 1000 막 해서 하는거지  니어는 0이고 파는 1이잖아 버텍스 8개로 정육면체 그릴수있으니까 
	for (int i = 0; i < m_vecVertex.size(); i++)
	{
		D3DXVec3Unproject(&m_vecFrustum[i], &m_vecVertex[i], NULL, &proj, &view, NULL);
	}
	// 64  /1 


	D3DXPlaneFromPoints(&m_plnae[0], &m_vecFrustum[0], &m_vecFrustum[1], &m_vecFrustum[2]); //앞면
	D3DXPlaneFromPoints(&m_plnae[1], &m_vecFrustum[3], &m_vecFrustum[2], &m_vecFrustum[6]); //우
	D3DXPlaneFromPoints(&m_plnae[2], &m_vecFrustum[7], &m_vecFrustum[6], &m_vecFrustum[5]); // 뒷면
	D3DXPlaneFromPoints(&m_plnae[3], &m_vecFrustum[4], &m_vecFrustum[5], &m_vecFrustum[1]); //왼
	D3DXPlaneFromPoints(&m_plnae[4], &m_vecFrustum[1], &m_vecFrustum[5], &m_vecFrustum[6]); //윗면
	D3DXPlaneFromPoints(&m_plnae[5], &m_vecFrustum[4], &m_vecFrustum[0], &m_vecFrustum[3]); //아랫면



}

bool cFrustum::InternalCheck(D3DXVECTOR3 vecPoint)
{
	//vecPoint 
	for(int i = 0 ; i < 6 ; i++)
	{
		FLOAT D = D3DXPlaneDotCoord(&m_plnae[i], &vecPoint);
		//뒷면에서 판별식이 양수가된다
		if (D > 0)
			return false;
	}

	return true;
}

void cFrustum::Setup_Mesh()
{
	D3DXCreateSphere(g_pD3DDvice, 0.5f, 10, 10, &m_meshSpear, NULL);
	
	int size = 5;
	for (int z = -size; z < size; ++z)
	{
		for (int y = size; y > -size; --y)
		{
			for (int x = size; x > -size; --x)
			{
			ST_SPHERE s;
			s.fRadius = 0.5f;
			s.vCenter = D3DXVECTOR3(z, y, x);

			m_vecSphere.push_back(s);
			}
		}
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

}

void cFrustum::Render()
{
	D3DXMATRIXA16 matWorld;
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);


	D3DXMatrixIdentity(&matWorld);
	g_pD3DDvice->SetTexture(0, 0);

	for (int i = 0; i < m_vecSphere.size(); i++)
	{
		if(InternalCheck(m_vecSphere[i].vCenter))
		{
			D3DXMatrixIdentity(&matWorld);
			matWorld._41 = m_vecSphere[i].vCenter.x;
			matWorld._42 = m_vecSphere[i].vCenter.y;
			matWorld._43 = m_vecSphere[i].vCenter.z;
			g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
			g_pD3DDvice->SetMaterial(&m_stMtlNone);
			m_meshSpear->DrawSubset(0);
		}

	}

}
