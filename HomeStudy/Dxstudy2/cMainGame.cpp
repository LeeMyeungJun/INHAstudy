#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "Player.h"
#include "xFileLoader.h"
#include "cSkinnedMesh.h"

#include "cZeloat.h"
#include "cOBB.h"


//D3DXMatrixRotationX()
//D3Dxvec3TransformNormal 사용  등등 이름비슷하니까 찾아쓰도록

cMainGame::cMainGame()
	:m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pPlayer(NULL)
	, m_pXFile(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pHoldZealot(NULL)
	, m_pMoveZealot(NULL)
	, m_pMap(NULL)
{
	
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pPlayer);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pXFile);
	SafeDelete(m_pSkinnedMesh);

	SafeDelete(m_pHoldZealot);
	SafeDelete(m_pMoveZealot);
	SafeDelete(m_pMap);
	g_pDeveceManager->Destroy();
}

void cMainGame::Setup()
{
	//Setup_Line();
	//Setup_Triangle();

	//m_pCubePC = new cCubePC;
	//m_pCubePC->Setup();

	setLight();
	
	//m_pPlayer = new Player;
	//m_pPlayer->Setup();

	m_pCamera = new cCamera; //0,0,0
	m_pCamera->Setup(NULL);

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	Setup_OBB();

	/*Setup_Frustum();*/
	
	/*m_pXFile = new xFileLoader;
	m_pXFile->Setup_Xfile("xFile/zealot.x");*/

	//m_pSkinnedMesh = new cSkinnedMesh;
	//m_pSkinnedMesh->Setup("xFile","zealot.x");
	//


}

void cMainGame::Update()
{
	//if (m_pPlayer)
	//{
	//	m_pPlayer->Update();
	//}

	g_pTimeManager->Update();
	//if (m_pSkinnedMesh)
	//	m_pSkinnedMesh->Update();


	//if (m_pFrustum)
	//	m_pFrustum->Update();
	//
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pHoldZealot)
		m_pHoldZealot->Update(m_pMap);

	if (m_pMoveZealot)
		m_pMoveZealot->Update(m_pMap);
	
}

void cMainGame::Render()
{
	if (g_pD3DDvice)
		g_pD3DDvice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(30, 75, 48), 1.0f, 0);

	g_pD3DDvice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	OBB_Render();

	//Frustum_Render();

	/*if (m_pPlayer)
		m_pPlayer->Render();*/

	//SkinnedMesh_Render();
	//m_pXFile->Render_Xfile();
	
	g_pD3DDvice->EndScene();
	g_pD3DDvice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	//if (m_pSkinnedMesh)
	//	m_pSkinnedMesh->WndProc(hWnd, message, wParam, lParam);
	//
	//switch (message)
	//{
	//case WM_RBUTTONDOWN:
	//	{
	//		for each(ST_SPHERE* sphere in m_vecCullingSphere)
	//		{
	//			if(m_pFrustum->IsIn(sphere))
	//			{
	//				sphere->isPicked = true;
	//			}
	//			else
	//			{
	//				sphere->isPicked = false;
	//			}
	//		}
	//	}
	//	
	//}
}

void cMainGame::Setup_Line()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 0, 0); //빨간줄 . 하지만 기본 조명값이 있어서 그냥보내면 검정색임 
	v.p = D3DXVECTOR3(0, 2, 0);
	m_vecLineVertex.push_back(v);

	v.p = D3DXVECTOR3(0, -2, 0);
	m_vecLineVertex.push_back(v);

	
}

void cMainGame::Setup_Triangle()
{
	ST_PC_VERTEX	v;
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

	v.p = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

}

void cMainGame::Draw_Line()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld); //항등행렬로 초기화
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecLineVertex.size() / 2,
		&m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부
}



void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld); //항등행렬로 초기화


	D3DXVECTOR3 vPosition = D3DXVECTOR3(5, 0, 5);
	D3DXMatrixTranslation(&matWorld, vPosition.x, vPosition.y, vPosition.z);
	
	
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size() / 3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부
}

void cMainGame::setLight()
{
	D3DLIGHT9   stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir = D3DXVECTOR3(0.0f, -1.0f, 0.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDvice->SetLight(0, &stLight);
	g_pD3DDvice->LightEnable(0, true);

}

void cMainGame::SkinnedMesh_Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Render(NULL);
	
}

void cMainGame::Setup_Frustum()
{
	D3DXCreateSphere(g_pD3DDvice, 0.5f, 10, 10, &m_pSphere, NULL);

	for(int i = -20 ; i <= 20 ; i ++)
	{
		for(int j = -20 ; j <= 20 ; j++)
		{
			for (int k = -20; k <= 20; k++)
			{
				ST_SPHERE* s = new ST_SPHERE;
				s->fRadius = 0.5f;
				s->vCenter = D3DXVECTOR3((float)i, (float)j, (float)k);
				s->isPicked = true; //컬링할건지 안할건지 판단하는데 쓸거야 true로 일단 다그리는걸로 해놓자 .
				m_vecCullingSphere.push_back(s);
			}
		}
	}// <<:for last

	ZeroMemory(&m_stCullingMtl, sizeof(D3DMATERIAL9));
	m_stCullingMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stCullingMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stCullingMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	m_pFrustum = new Frustum;
	m_pFrustum->Setup();
	
}

void cMainGame::Frustum_Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetMaterial(&m_stCullingMtl);

	
	for each(ST_SPHERE* sphere in m_vecCullingSphere)
	{
		if(sphere->isPicked)
		{
			matWorld._41 = sphere->vCenter.x;
			matWorld._42 = sphere->vCenter.y;
			matWorld._43 = sphere->vCenter.z;
			g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
			m_pSphere->DrawSubset(0);
		}
	}
}

void cMainGame::Setup_OBB()
{
	m_pHoldZealot = new cZeloat;
	m_pHoldZealot->Setup();

	m_pMoveZealot = new cZeloat;
	m_pMoveZealot->Setup();

	cCharacter* pCharacter = new cCharacter;
	m_pMoveZealot->SetCharacterController(pCharacter);
	SafeRelease(pCharacter); //? 
}

void cMainGame::OBB_Render()
{
	D3DCOLOR c = cOBB::IsCollision(m_pHoldZealot->GetOBB(), m_pMoveZealot->GetOBB()) ? D3DCOLOR_XRGB(255, 0, 0) : D3DCOLOR_XRGB(255, 255, 255);//충돌하면 빨강

	if (m_pHoldZealot)
		m_pHoldZealot->Render(c);
	
	if (m_pMoveZealot)
		m_pMoveZealot->Render(c);
}



