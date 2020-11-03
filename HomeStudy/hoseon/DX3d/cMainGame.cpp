#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cHexagon.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"



#include "cAseLoader.h"
#include "cFrame.h"
#include "cRay.h"
#include "cRawLoader.h"
#include "cXLoader.h"
#include "cSkinnedMesh.h"
#include "cFrustumCulling.h"
#include "cFrustum.h"

#include "cOBB.h"
#include "cZealot.h"

#include "cButtonMenu.h"

DWORD	FtoDW(float f)
{
	return *((DWORD*)&f); //float를 DW로 바꿔주는 함수를 만든것뿐
}
cMainGame::cMainGame()
	: m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	, m_pTexture(NULL)
	, m_pLight(NULL)
	, m_pHexagon(NULL)
	, m_pMap(NULL)
	, m_pRootFrame(NULL)
	, m_pObjMesh(NULL)
	, m_pRawLoader(NULL)
	, m_pMtTexture(NULL)
	, m_pXLoader(NULL)
	, m_pSkinnedMesh(NULL)
	, m_pFrustumCulling(NULL)
	, m_pFrustum(NULL)
	, m_pHoldZealot(NULL)
	, m_pMoveZealot(NULL)
	, m_pFont(NULL)
	, m_p3DTEXT(NULL)
	, m_pSprite(NULL)
	, m_pTextureUI(NULL)
	, m_pMenuBtn(NULL)
	, m_pTex0(NULL)
	, m_pTex1(NULL)
	, m_pTex2(NULL)
	, m_pTex3(NULL)
	, m_nType(-1)
	, m_isMouseClick(true)
	, m_pShader(NULL)
	, m_pZealotTexture(NULL)
	, m_pDiffuse(NULL)
	, m_pSpecular(NULL)

{
	m_fCameraDist = 10;
	m_fBoxRotY = 0;
	m_isLButtonDown = false;

	m_ptPrevMouse.x = 0;
	m_ptPrevMouse.y = 0;
}

cMainGame::~cMainGame()
{
	SafeDelete(m_pMoveZealot);
	SafeDelete(m_pHoldZealot);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeDelete(m_pMap);
	SafeDelete(m_pXLoader);
	SafeDelete(m_pSkinnedMesh);
	SafeDelete(m_pFrustumCulling);
	SafeDelete(m_pFrustum);
	SafeDelete(m_pMenuBtn);

	SafeRelease(m_pZealotTexture);
	SafeRelease(m_pShader);
	SafeRelease(m_pSprite);
	SafeRelease(m_pTextureUI);
	//SafeRelease(m_pMeshSphere);
	//SafeRelease(m_pMeshTeapot);
	//SafeRelease(m_pObjMesh);
	SafeRelease(m_p3DTEXT);
	SafeRelease(m_pFont);
	SafeRelease(m_pTexture);
	SafeRelease(m_pMtTexture);



	for each(auto p in m_vecObjMtlTex)
		SafeRelease(p);

	//m_pRootFrame->Destroy(); //생성안하고 
	
	g_pFontManager->Destroy();
	g_pDeviceManager->Destroy(); //완전히꺼지낳아 

}

void cMainGame::Setup()
{
	m_pGrid = new cGrid;
	if (m_pGrid)
		m_pGrid->Setup();

	Create_Font();
	//Setup_UI();
	/*m_pCubeMan = new cCubeMan;
	if (m_pCubeMan)
		m_pCubeMan->Setup();*/

	m_pCamera = new cCamera;
	if (m_pCamera)
	{
		//m_pCamera->Setup(&(m_pCubeMan->GetPosition()));
		m_pCamera->Setup(NULL,&m_isMouseClick);
	}
	//Setup_Particle();
	Setup_MultiTexture();
	/*m_pHexagon = new cHexagon;
	if (m_pHexagon)
		m_pHexagon->Setup();*/

	//Setup_Obj();
	//Setup_MeshObejct();
	SetLight();

	/*{
		cAseLoader l;
		m_pRootFrame = l.Load("woman/woman_01_all.ASE");
	}*/

	//Setup_PickingObj();
	//Setup_Raw();

	//m_pXLoader = new cXLoader;
	//if(m_pXLoader)
	//	m_pXLoader->Setup();

	//D3DXCreateTextureFromFile(g_pD3DDevice, L"HeightMapData/terrain.jpg", &m_pMtTexture);

	m_pSkinnedMesh = new cSkinnedMesh;
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Setup("Zealot", "zealot.X");
	LoadAssets();
	
	/*m_pFrustumCulling = new cFrustumCulling;
	if (m_pFrustumCulling)
	{
		m_pFrustumCulling->Setup_Frustum();
		m_pFrustumCulling->Setup_Sphere();
	}*/

	//Setup_Frustum();

	Setup_OBB();

	m_pMenuBtn = new cButtonMenu;
	m_pMenuBtn->Setup(&m_isMouseClick);
}

void cMainGame::Update()
{
	/*if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);*/

	g_pTimeManager->Update();
	if (m_pSkinnedMesh)
		m_pSkinnedMesh->Update();
	
	if (m_pCamera)
		m_pCamera->Update();

	//m_pFrustumCulling->Update();

	/*if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(), NULL);*/

	/*if (m_pFrustum)
		m_pFrustum->Update();*/

	if (m_pHoldZealot)
		m_pHoldZealot->Update(m_pMap);
	if (m_pMoveZealot)
		m_pMoveZealot->Update(m_pMap);

	//Update_MultiTexture();
	//Update_Particle();
	
	/*if (m_pMenuBtn)
		m_pMenuBtn->Update();*/
}

void cMainGame::Render()
{
	if(g_pD3DDevice)
		g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 45, 48), 1.0f, 0);
	
	g_pD3DDevice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();
	
	//MultiTexture_Render();
	
	//Render_Particle();

	//Text_Render();
	//if (m_pCubeMan)
	//	m_pCubeMan->Render();

	/*if (m_pHexagon)
		m_pHexagon->Render();*/

	//Obj_Render();
	//Mesh_Render();
	
	/*//캐릭터
	{
		if (m_pRootFrame)
			m_pRootFrame->Render();
	}*/

	//PickingObj_Render();
	//Render_Raw();
	//m_pXLoader->Display(0.025f);

	SkinnedMesh_Render();
	//m_pFrustumCulling->Render_sphere();
	//Frustum_Render();

	OBB_Render();
	//m_pRootFrame->CountFPS();
	//UI_Render(); //제일위에잇으라고 마지막에 그려줌

	//if (m_pMenuBtn)
	//	m_pMenuBtn->Render();
	g_pD3DDevice->EndScene();
	g_pD3DDevice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	if (m_pMenuBtn)
		m_pMenuBtn->WndProc(hWnd, message, wParam, lParam);

	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
		m_pSkinnedMesh->animState = ATTACK;
		m_pSkinnedMesh->SetAnimationIndexBlend(1);
		}
		break;
	case WM_KEYDOWN:
		{
		m_pMenuBtn->BtnOnOff();
		}
		break;
	}
}

void cMainGame::Setup_Obj()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "Map.obj");
	Load_Surface();
}

void cMainGame::Obj_Render()
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

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

	matWorld = matS * matR;
	//m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}


void cMainGame::SetLight()
{
	D3DLIGHT9	stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, m_pTexture);
	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], 
		sizeof(ST_PT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);	//텍스쳐 입히고 빼겠다
}


void cMainGame::Setup_Line()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(100, 240, 100);
	v.p = D3DXVECTOR3(0, 50, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, -50, 0);
	m_vecLineVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(240, 100, 100);
	v.p = D3DXVECTOR3(50, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(-50, 0, 0);
	m_vecLineVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(100, 100, 240);
	v.p = D3DXVECTOR3(0, 0, 50);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, -50);
	m_vecLineVertex.push_back(v);
}

void cMainGame::Draw_Line()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecLineVertex.size() / 2, &m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));
}

void cMainGame::Setup_Triangle()
{
	srand((unsigned int)time(0));
	ST_PC_VERTEX	v;
	v.c = D3DCOLOR_XRGB(rand() % 256, rand() % 256, rand() % 256);
	
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0);
	m_vecTriangleVertex.push_back(v);
	
	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0);
	m_vecTriangleVertex.push_back(v);
	
	v.p = D3DXVECTOR3(1.0f, 1.0f, 0);
	m_vecTriangleVertex.push_back(v);
}

void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	D3DXVECTOR3 vPosition = D3DXVECTOR3(0, 0, 5);
	D3DXMatrixTranslation(&matWorld, vPosition.x, vPosition.y, vPosition.z);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecTriangleVertex.size() / 3, &m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));
}

void cMainGame::Setup_Box()
{
	ST_PC_VERTEX	v;

	m_vecBoxVertex.push_back(D3DXVECTOR3(-0.8f, -0.8f, -0.8f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(-0.8f, 0.8f, -0.8f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(0.8f, 0.8f, -0.8f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(0.8f, -0.8f, -0.8f));

	m_vecBoxVertex.push_back(D3DXVECTOR3(-0.8f, -0.8f, 0.8f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(-0.8f, 0.8f, 0.8f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(0.8f, 0.8f, 0.8f));
	m_vecBoxVertex.push_back(D3DXVECTOR3(0.8f, -0.8f, 0.8f));

	
	//front
	v.c = D3DCOLOR_XRGB(0, 254, 155);
	
	v.p = m_vecBoxVertex[0];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecBoxTrisVertex.push_back(v);

	v.p = m_vecBoxVertex[0];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecBoxTrisVertex.push_back(v);

	//back
	v.c = D3DCOLOR_XRGB(255, 80, 97);
	
	v.p = m_vecBoxVertex[4];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[5];
	m_vecBoxTrisVertex.push_back(v);

	v.p = m_vecBoxVertex[4];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[7];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecBoxTrisVertex.push_back(v);

	//left
	v.c = D3DCOLOR_XRGB(2, 196, 53);

	v.p = m_vecBoxVertex[4];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[5];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecBoxTrisVertex.push_back(v);

	v.p = m_vecBoxVertex[4];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[1];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[0];
	m_vecBoxTrisVertex.push_back(v);

	//right
	v.c = D3DCOLOR_XRGB(148, 97, 253);
	
	v.p = m_vecBoxVertex[3];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecBoxTrisVertex.push_back(v);

	v.p = m_vecBoxVertex[3];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[7];
	m_vecBoxTrisVertex.push_back(v);

	//top
	v.c = D3DCOLOR_XRGB(255, 219, 78);
	
	v.p = m_vecBoxVertex[1];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[5];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecBoxTrisVertex.push_back(v);

	v.p = m_vecBoxVertex[1];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[6];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[2];
	m_vecBoxTrisVertex.push_back(v);

	//buttom
	v.c = D3DCOLOR_XRGB(45, 217, 254);
	
	v.p = m_vecBoxVertex[4];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[0];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecBoxTrisVertex.push_back(v);

	v.p = m_vecBoxVertex[4];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[3];
	m_vecBoxTrisVertex.push_back(v);
	v.p = m_vecBoxVertex[7];
	m_vecBoxTrisVertex.push_back(v);
}

void cMainGame::Draw_Box()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_fBoxRotY));

	D3DXVECTOR3 vPosition = m_vPosition;
	D3DXMatrixTranslation(&matWorld, vPosition.x, vPosition.y, vPosition.z);
	matWorld = matRot * matWorld;
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecBoxTrisVertex.size() / 3, &m_vecBoxTrisVertex[0],
		sizeof(ST_PC_VERTEX));

	/*for (int i = 0; i < m_vecIndex.size(); i += 3)
	{
		cVector3 v1 = m_vecVertex[m_vecIndex[i + 0]];
		cVector3 v2 = m_vecVertex[m_vecIndex[i + 1]];
		cVector3 v3 = m_vecVertex[m_vecIndex[i + 2]];

		v1 = cVector3::TransformCoord(v1, matWVP);
		v2 = cVector3::TransformCoord(v2, matWVP);
		v3 = cVector3::TransformCoord(v3, matWVP);

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		cVector3 l1 = v2 - v1;
		cVector3 l2 = v1 - v3;

		if (cVector3::Cross(l2, l1).z > 0)
		{
			MoveToEx(m_MemDc, v1.x, v1.y, NULL);
			LineTo(m_MemDc, v2.x, v2.y);
			LineTo(m_MemDc, v3.x, v3.y);
			LineTo(m_MemDc, v1.x, v1.y);
		}
	}*/
}

void cMainGame::Setup_Grid()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(100, 100, 100);
	int nNumHalfTile = 20;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile * fInterval;
	float fMin = -nNumHalfTile * fInterval;

	for (int i = 1; i <= nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecGridVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecGridVertex.push_back(v);

		v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		m_vecGridVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		m_vecGridVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		m_vecGridVertex.push_back(v);
	}
	//가운데 선
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecGridVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecGridVertex.push_back(v);

	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecGridVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecGridVertex.push_back(v);
}

void cMainGame::Draw_Grid()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);
	
	for(int i = 0; i < m_vecGridVertex.size() / 2; i += 2)
	{
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_LINELIST, m_vecGridVertex.size() / 2, &m_vecGridVertex[0],
			sizeof(ST_PC_VERTEX));
	}
}

void cMainGame::Setup_Pyramid()
{
	ST_PC_VERTEX	v;
	v.c = D3DCOLOR_XRGB(100, 240, 100);
	
	m_vecPyramidVertex.push_back(D3DXVECTOR3(-0.2f, 2.0f, -0.2f));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(-0.2f, 2.0f, 0.2f));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(0.2f, 2.0f, 0.2f));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(0.2f, 2.0f, -0.2f));
	
	m_vecPyramidVertex.push_back(D3DXVECTOR3(0, 0, 0));

	//top
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);

	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	
	//right
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);
	
	//left
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);
	
	//forward
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);
	
	//back
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(240, 100, 100);

	m_vecPyramidVertex.clear();
	m_vecPyramidVertex.push_back(D3DXVECTOR3(2, -0.2f, -0.2f));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(2, -0.2f, 0.2f));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(2, 0.2f, 0.2f));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(2, 0.2f, -0.2f));

	m_vecPyramidVertex.push_back(D3DXVECTOR3(0, 0, 0));

	//top
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);

	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);

	//right
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	//left
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	//forward
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	//back
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(100, 100, 240);

	m_vecPyramidVertex.clear();
	m_vecPyramidVertex.push_back(D3DXVECTOR3(-0.2f, -0.2f, 2));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(0.2f, -0.2f, 2));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(0.2f, 0.2f, 2));
	m_vecPyramidVertex.push_back(D3DXVECTOR3(-0.2f, 0.2f, 2));

	m_vecPyramidVertex.push_back(D3DXVECTOR3(0, 0, 0));

	//top
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);

	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);

	//right
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	//left
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	//forward
	v.p = m_vecPyramidVertex[2];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[1];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);

	//back
	v.p = m_vecPyramidVertex[0];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[3];
	m_vecPyramidTrisVertex.push_back(v);
	v.p = m_vecPyramidVertex[4];
	m_vecPyramidTrisVertex.push_back(v);
}

void cMainGame::Draw_Pyramid()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF);

	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecPyramidTrisVertex.size() / 3, &m_vecPyramidTrisVertex[0],
		sizeof(ST_PC_VERTEX));
}


void cMainGame::Update_Move()
{
	D3DXMATRIXA16 matRot;
	D3DXMatrixRotationY(&matRot, D3DXToRadian(m_fBoxRotY));
	D3DXVECTOR3 vecRot;
	D3DXVec3TransformNormal(&vecRot, &m_vBoxDirection, &matRot);
	
	if (GetKeyState('W') & 0x8000)
		m_vPosition = m_vPosition + (vecRot * 0.1f);
	else if (GetKeyState('S') & 0x8000)
		m_vPosition = m_vPosition - (vecRot * 0.1f);
}

void cMainGame::Update_Rotation()
{
	if (GetKeyState('A') & 0x8000)
		m_fBoxRotY -= 1;
	else if (GetKeyState('D') & 0x8000)
		m_fBoxRotY += 1;
}

bool cMainGame::LoadAssets()
{
	// 텍스처 로딩
	m_pZealotTexture = LoadTexture("Shader/Zealot_Diffuse.bmp");
	if (!m_pZealotTexture) return false;

	m_pDiffuse = LoadTexture("Shader/Fieldstone.tga");
	if (!m_pDiffuse) return false;

	m_pSpecular = LoadTexture("Shader/Earth.jpg");
	if (!m_pSpecular) return false;

	
	// 쉐이더 로딩
	//m_pShader = LoadShader("Shader/Shader.fx");
	m_pShader = LoadShader("Shader/SpecularMapping.fx");

	if (!m_pShader) return false;

	// 모델 로딩

	return true;
}

LPD3DXEFFECT cMainGame::LoadShader(const char* filename)
{
	LPD3DXEFFECT ret = NULL;

	LPD3DXBUFFER pError = NULL;
	DWORD dwShaderFlags = 0;

#if _DEBUG
	dwShaderFlags |= D3DXSHADER_DEBUG;
#endif

	D3DXCreateEffectFromFileA(g_pD3DDevice, filename,
		NULL, NULL, dwShaderFlags, NULL, &ret, &pError); //애가 주야

														 // 쉐이더 로딩에 실패한 경우 output창에 쉐이더
														 // 컴파일 에러를 출력한다.
	if (!ret && pError)
	{
		int size = pError->GetBufferSize();
		void *ack = pError->GetBufferPointer();

		//에러발생시 나오는코드니까
	/*	if (ack)
		{
			char* str = new char[size];
			sprintf(str, (const char*)ack, size);
			OutputDebugString(str);
			delete[] str;
		}*/
	}

	return ret;
}

LPDIRECT3DTEXTURE9 cMainGame::LoadTexture(const char* filename)
{
	LPDIRECT3DTEXTURE9 ret = NULL;
	if (FAILED(D3DXCreateTextureFromFileA(g_pD3DDevice, filename, &ret)))
	{
		//OutputDebugString("텍스처 로딩 실패: ");
		//OutputDebugString(filename);
		//OutputDebugString("\n");
		cout << "텍스처 로딩 실패" << endl;
	}

	return ret;
}

void cMainGame::Setup_MultiTexture()
{
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/stones.png",&m_pTex0);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/env0.png", &m_pTex1);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/env1.png", &m_pTex2);
	D3DXCreateTextureFromFile(g_pD3DDevice, L"Texture/Albedo00.jpg", &m_pTex3);

	ST_PT_VERTEX v;
	v.p = D3DXVECTOR3(0, 0, 0); v.t = D3DXVECTOR2(0, 1); m_vecVertex_Multil.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multil.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(1, 1); m_vecVertex_Multil.push_back(v);
	
	v.p = D3DXVECTOR3(2, 2, 0); v.t = D3DXVECTOR2(1, 0); m_vecVertex_Multil.push_back(v);
	v.p = D3DXVECTOR3(2, 0, 0); v.t = D3DXVECTOR2(1, 1); m_vecVertex_Multil.push_back(v);
	v.p = D3DXVECTOR3(0, 2, 0); v.t = D3DXVECTOR2(0, 0); m_vecVertex_Multil.push_back(v);


}

void cMainGame::Update_MultiTexture()
{
	if (::GetAsyncKeyState('1') & 0x8000) m_nType = 1;
	if (::GetAsyncKeyState('2') & 0x8000) m_nType = 2;
	if (::GetAsyncKeyState('3') & 0x8000) m_nType = 3;
	if (::GetAsyncKeyState('4') & 0x8000) m_nType = 4;
	if (::GetAsyncKeyState('5') & 0x8000) m_nType = 5;
	if (::GetAsyncKeyState('6') & 0x8000) m_nType = 6;
	if (::GetAsyncKeyState('7') & 0x8000) m_nType = 7;
	if (::GetAsyncKeyState('8') & 0x8000) m_nType = 8;
	if (::GetAsyncKeyState('9') & 0x8000) m_nType = 9;
	if (::GetAsyncKeyState('0') & 0x8000) m_nType = 0;
	if (::GetAsyncKeyState('R') & 0x8000) m_nType = -1;


}

void cMainGame::MultiTexture_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	for(int i = 0 ; i < 4 ; i++) //안넣어두되는데 셋팅에 의미로 그냥하는거뿐이야
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_ADDRESSW, D3DTADDRESS_WRAP);

		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);
		//위세줄은 선형보간하겠다는뜻인데 지금은 딱히뜻이없어서 애들은 삭제해도 상간업다
	}

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_TEXCOORDINDEX, 0); //1번인덱스가 0번텍스쳐의 좌표사용
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_TEXCOORDINDEX, 0);
	g_pD3DDevice->SetTextureStageState(3, D3DTSS_TEXCOORDINDEX, 0);

	switch (m_nType)
	{
	case 1: MultiTexture_Render1(); break;
	case 2: MultiTexture_Render2(); break;
	case 3: MultiTexture_Render3(); break;
	case 4: MultiTexture_Render4(); break;
	case 5: MultiTexture_Render5(); break;
	case 6: MultiTexture_Render6(); break;
	case 7: MultiTexture_Render7(); break;
	case 8: MultiTexture_Render8(); break;
	case 9: MultiTexture_Render9(); break;
	case 0: MultiTexture_Render0(); break;
	default: MultiTexture_Render_default(); break;
	
		
	}

	SetBillboard();
	

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecVertex_Multil.size() / 3,
		&m_vecVertex_Multil[0],
		sizeof(ST_PT_VERTEX));

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTexture(1, NULL);
	g_pD3DDevice->SetTexture(2, NULL);

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE); //D3DTSS_COLOROP 텍스쳐 혼합처리 안하겠다D3DTOP_DISABLE
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_RESULTARG, D3DTA_CURRENT);


	for (int i = 0; i < 4; ++i)
	{
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MAGFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MINFILTER, D3DTEXF_NONE);
		g_pD3DDevice->SetSamplerState(i, D3DSAMP_MIPFILTER, D3DTEXF_NONE);
	}



}

void cMainGame::MultiTexture_Render1()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex1); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);//곱하기를 한거야
	
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 

	


}

void cMainGame::MultiTexture_Render2()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex1); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE2X);//곱하기를 한거야

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render3()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex1); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE4X);//곱하기를 한거야

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render4()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex1); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADD);//더해주자

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render5()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex1); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SUBTRACT);//더해주자

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render6()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex3); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED);//더해주자

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render7()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex3); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSIGNED2X);//더해주자

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render8()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex3); //1번에다가 1번꺼를

	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_ADDSMOOTH);//더해주자

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render9()//애는 이미지 3개로해보자
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex2); //1번에다가 1번꺼를
	g_pD3DDevice->SetTexture(2, m_pTex3); //1번에다가 1번꺼를


	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEMP);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_MULTIPLYADD);



	g_pD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

void cMainGame::MultiTexture_Render0()
{
	g_pD3DDevice->SetTexture(0, m_pTex0); //0번에다가 0번꺼를
	g_pD3DDevice->SetTexture(1, m_pTex2); //1번에다가 1번꺼를
	g_pD3DDevice->SetTexture(2, m_pTex3); //1번에다가 1번꺼를


	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLORARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_RESULTARG, D3DTA_TEMP);

	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG0, D3DTA_CURRENT);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG1, D3DTA_TEMP);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLORARG2, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_LERP);



	g_pD3DDevice->SetTextureStageState(3, D3DTSS_COLOROP, D3DTOP_DISABLE);//구지 명시를 하지안항도되는데 
}

//이미지 하나만출력하는 디폴트용
void cMainGame::MultiTexture_Render_default()
{
	g_pD3DDevice->SetTexture(0, m_pTex0);
	g_pD3DDevice->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_DISABLE);//1번친구안쓸거임
	g_pD3DDevice->SetTextureStageState(2, D3DTSS_COLOROP, D3DTOP_DISABLE);//2번친구안쓸거임
}

void cMainGame::Setup_MeshObejct()
{
	D3DXCreateTeapot(g_pD3DDevice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	cObjLoader l;
	//m_pObjMesh = l.LoadMesh(m_vecObjMtlTex, "obj", "map.obj");
}

void cMainGame::Mesh_Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);

	D3DXMATRIXA16 matWorld, matS, matR;
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS* matR;
		D3DXMatrixTranslation(&matWorld, 0, 0, 10);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlTeapot);
		m_pMeshTeapot->DrawSubset(0); //지금은 속성이 하나뿐이니까 0해주면대 여러개면 값을 넣어주면되고
	}

	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS* matR;
		//D3DXMatrixTranslation(&matWorld, 0, 0, 10);

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0);
	}

	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0f);

		matWorld = matS * matR;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		for(size_t i = 0; i < m_vecObjMtlTex.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&m_vecObjMtlTex[i]->GetMaterial());
			g_pD3DDevice->SetTexture(0, m_vecObjMtlTex[i]->GetTexture());
			m_pObjMesh->DrawSubset(i);
		}
	}
}

void cMainGame::Setup_PickingObj()
{
	for(int i = 0; i <= 10; i++)
	{
		ST_SPHERE s;
		s.fRadius = 0.5f;
		s.vCenter = D3DXVECTOR3(0, 0, -10 + 2 * i);
		m_vecSphere.push_back(s);
	}

	ZeroMemory(&m_stMtlNone, sizeof(D3DMATERIAL9));
	m_stMtlNone.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlNone.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPicked, sizeof(D3DMATERIAL9));
	m_stMtlPicked.Ambient = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Diffuse = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);
	m_stMtlPicked.Specular = D3DXCOLOR(0.7f, 0.0f, 0.0f, 1.0f);

	ZeroMemory(&m_stMtlPlane, sizeof(D3DMATERIAL9));
	m_stMtlPlane.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stMtlPlane.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	ST_PN_VERTEX v;
	v.n = D3DXVECTOR3(0, 1, 0);
	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(-10, 0, 10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(10, 0, 10); m_vecPlaneVertex.push_back(v);

	v.p = D3DXVECTOR3(-10, 0, -10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(10, 0, 10); m_vecPlaneVertex.push_back(v);
	v.p = D3DXVECTOR3(10, 0, -10); m_vecPlaneVertex.push_back(v);
}

void cMainGame::PickingObj_Render()
{
	D3DXMATRIXA16 matWorld;

	g_pD3DDevice->SetFVF(ST_PN_VERTEX::FVF);
	g_pD3DDevice->SetMaterial(&m_stMtlPlane);
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecPlaneVertex[0], sizeof(ST_PN_VERTEX));

	for(int i = 0; i < m_vecSphere.size(); i++)
	{
		D3DXMatrixIdentity(&matWorld);
		matWorld._41 = m_vecSphere[i].vCenter.x;
		matWorld._42 = m_vecSphere[i].vCenter.y;
		matWorld._43 = m_vecSphere[i].vCenter.z;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->SetMaterial(m_vecSphere[i].isPicked ? &m_stMtlPicked : &m_stMtlNone);
		m_pMeshSphere->DrawSubset(0);
	}
	g_pD3DDevice->SetMaterial(&m_stMtlNone);
	D3DXMatrixTranslation(&matWorld, m_vPickedPosition.x, m_vPickedPosition.y, m_vPickedPosition.z);

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_pMeshSphere->DrawSubset(0);
}

void cMainGame::Setup_Raw()
{
	int tmp = 0;
	ST_PNT_VERTEX v[6];
	m_pRawLoader->LoadRaw(m_meshPlaneVertex, "HeightMapData", "HeightMap.raw");
	int a[6];
	for(int i = 1; i <= CELL; i++)
	{
		for(int j = 0; j < CELL; j++)
		{
			v[0] = m_meshPlaneVertex[i * (CELL + 1) + j];
			tmp = i * (CELL + 1) + j;
			v[1] = m_meshPlaneVertex[tmp - (CELL + 1)];
			tmp = tmp - (CELL + 1);
			v[2] = m_meshPlaneVertex[tmp + 1];
			tmp = i * (CELL + 1) + j;
			v[3] = m_meshPlaneVertex[tmp];
			tmp = tmp + 1;
			v[4] = m_meshPlaneVertex[tmp];
			tmp = i * (CELL + 1) + j;
			v[5] = m_meshPlaneVertex[tmp + 1];

			/*a[0] = i * (CELL + 1) + j;
			a[1] = a[0] - (CELL + 1);
			a[2] = a[1] + 1;
			a[3] = a[0];
			a[4] = a[2];
			a[5] = a[0] + 1;
			continue;*/

			for(int k = 0; k < 6; k++)
				m_vecMtVertex.push_back(v[k]);
		}
	}

	for (int i = 0; i < CELL; i++)
	{
		for (int j = 0; j < CELL; j++)
		{
			m_vecMtVertex[i * (CELL + 1) + j].t = D3DXVECTOR2((float)j/CELL, (float)i/CELL);
		}
	}
}

void cMainGame::Render_Raw()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetTexture(0, m_pMtTexture);
	D3DXMATRIXA16 matI;
	D3DXMatrixIdentity(&matI);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matI);
	g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecMtVertex.size() / 3, &m_vecMtVertex[0],
		sizeof(ST_PNT_VERTEX));
	g_pD3DDevice->SetTexture(0, NULL);
}

void cMainGame::SkinnedMesh_Render()
{
	D3DXMATRIXA16 matWorld,matView,matProjection;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	if(m_pShader)
	{
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProjection);
		m_pShader->SetMatrix("gWorldMatrix", &matWorld);
		m_pShader->SetMatrix("gViewMatrix", &matView);
		m_pShader->SetMatrix("gProjectionMatrix", &matProjection);
		D3DXCOLOR color(1, 0, 1, 1);
		D3DXVECTOR4 light(1.0f, 0.7f, 0.7f, 1.0f);
		//m_pShader->SetValue("gColor", &color, sizeof(D3DXVECTOR4));
		m_pShader->SetVector("gLightColor",&light);
		m_pShader->SetTexture("DiffuseMap_Tex", m_pDiffuse);
		m_pShader->SetTexture("SpecularMap_Tex", m_pSpecular);

		
		//Texture
	//	m_pShader->SetTexture("DiffuseMap_Tex", m_pZealotTexture);

		
		UINT numpasses = 0; //우리는 0번밖에없어서 이리함
		m_pShader->Begin(&numpasses, NULL);
		{

			for (UINT i = 0; i < numpasses; i++)
			{
				m_pShader->BeginPass(i);
				if (m_pSkinnedMesh)
					m_pSkinnedMesh->Render(NULL);
				m_pShader->EndPass();
			}
		}

		m_pShader->End();//그리기작업은 여기까지
	}
	else
	{
		if (m_pSkinnedMesh)
			m_pSkinnedMesh->Render(NULL);
	}
	
	
}


void cMainGame::Setup_Frustum()
{
	D3DXCreateSphere(g_pD3DDevice, 0.5f, 10, 10, &m_pSphere, NULL);

	for(int i = -20; i <= 20; i++)
	{
		for(int j = -20; j <= 20; j++)
		{
			for (int k = -20; k <= 20; k++)
			{
				ST_SPHERE* s = new ST_SPHERE;
				s->fRadius = 0.5f;
				s->vCenter = D3DXVECTOR3((float)i, (float)j, (float)k);
				s->isPicked = true;
				m_vecCullingSphere.push_back(s);
			}
		}
	}

	ZeroMemory(&m_stCullingMtl, sizeof(D3DMATERIAL9));
	m_stCullingMtl.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stCullingMtl.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);
	m_stCullingMtl.Specular = D3DXCOLOR(0.7f, 0.7f, 0.7f, 1.0f);

	m_pFrustum = new cFrustum;
	m_pFrustum->Setup();
}

void cMainGame::Frustum_Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->SetTexture(0, 0);

	for each(ST_SPHERE* sphere in m_vecCullingSphere)
	{
		if(sphere->isPicked)
		{
			D3DXMatrixIdentity(&matWorld);
			matWorld._41 = sphere->vCenter.x;
			matWorld._42 = sphere->vCenter.y;
			matWorld._43 = sphere->vCenter.z;
			g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
			g_pD3DDevice->SetMaterial(&m_stCullingMtl);
			m_pSphere->DrawSubset(0);
		}
	}
}


void cMainGame::Setup_OBB()
{
	m_pHoldZealot = new cZealot;
	m_pHoldZealot->Setup();

	m_pMoveZealot = new cZealot;
	m_pMoveZealot->Setup();

	cCharacter* pCharacter = new cCharacter;
	m_pMoveZealot->SetCharacterController(pCharacter);
	SafeRelease(pCharacter);
}

void cMainGame::OBB_Render()
{
	D3DCOLOR c = cOBB::IsCollision(m_pHoldZealot->GetOBB(), m_pMoveZealot->GetOBB()) ?
		D3DCOLOR_XRGB(255, 0, 0) : D3DCOLOR_XRGB(255, 255, 255);

	if (m_pHoldZealot)
		m_pHoldZealot->Render(c);
	if (m_pMoveZealot)
		m_pMoveZealot->Render(c);
}

void cMainGame::Create_Font()
{
	D3DXFONT_DESC fd;
	ZeroMemory(&fd, sizeof(D3DXFONT_DESC));
	fd.Height = 50;
	fd.Width = 25;
	fd.Weight = FW_MEDIUM; //이거는 F12눌르고 타입좀 확인해봐
	fd.Italic = false;
	fd.CharSet = DEFAULT_CHARSET;
	fd.OutputPrecision = OUT_DEFAULT_PRECIS;
	fd.PitchAndFamily = FF_DONTCARE;
	//일단은 시스템에있는 폰트가지고 사용해볼게
	//wcscpy_s(fd.FaceName, L"굴림체");
	//이제 우리폰트로 해보자구
	AddFontResourceA("font/umberto.ttf");
	wcscpy_s(fd.FaceName, L"umberto");

	D3DXCreateFontIndirect(g_pD3DDevice,&fd, &m_pFont);



	//>>:3D
	HDC hdc = CreateCompatibleDC(0);
	LOGFONT lf;
	ZeroMemory(&lf, sizeof(LOGFONT));
	lf.lfHeight = 25;
	lf.lfWidth = 12;
	lf.lfWeight = 500;
	lf.lfItalic = false;
	lf.lfUnderline = false;
	lf.lfStrikeOut = false;
	lf.lfCharSet = DEFAULT_CHARSET;
	wcscpy_s(lf.lfFaceName, L"umberto");

	HFONT hFont;
	HFONT hFontOld;
	hFont = CreateFontIndirect(&lf);
	hFontOld = (HFONT)SelectObject(hdc, hFont);
	D3DXCreateText(g_pD3DDevice, hdc,
		L"Direct3D",
		0.001f,
		0.01f,
		&m_p3DTEXT,
		0, 0);

	SelectObject(hdc, hFontOld);
	DeleteObject(hFont);
	DeleteDC(hdc);

	
}

void cMainGame::Text_Render()
{
	string sText("ABC 123 !@#$ 가나다라");
	RECT rc;
	SetRect(&rc, 100, 100, 301, 200);

	// >> :font manager 추가후
	LPD3DXFONT pFont = g_pFontManager->GetFont(cFontManager::E_DEFALUT);
	//<<:

	//> fontmanager 사용안할떄는 setup에서 해주고 여기서 이리씀
	/*m_pFont->DrawTextA(NULL,
		sText.c_str(),
		sText.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));*/


	pFont->DrawTextA(NULL,
		sText.c_str(),
		sText.length(),
		&rc,
		DT_LEFT | DT_TOP | DT_NOCLIP,
		D3DCOLOR_XRGB(255, 255, 0));


	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	//>3d 캐릭터위에 잇게하고 따라다니게하는거 
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixScaling(&matS, 1.0f, 1.0f, 10.0f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 4.0f);//45도지?
	D3DXMatrixTranslation(&matT, -2.0f, 1.0f, 0.0f);
	matWorld = matS * matR * matT;
	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	m_p3DTEXT->DrawSubset(0);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

}

void cMainGame::Setup_UI()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);

	//m_pTextureUI = g_pTextureManager->GetTexture("UI/수지.png"); //UI는 이런식으로하면 안된다고 보여줄려고한거야 이거로하면 짤림 이상하게나옴

	D3DXCreateTextureFromFileExA(
		g_pD3DDevice,
		"UI/수지.png",
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN, //난모르니 너가알아서
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTextureUI
	);
}

void cMainGame::UI_Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	//이미지 출력
	RECT rc;
	SetRect(&rc, 0, 0, m_stImageInfo.Width, m_stImageInfo.Height);
	

	//>>: UI도 회전같은걸 시킬수있어
	D3DXMATRIXA16 matS, matR, matT, mat;
	//사진 위치
	D3DXMatrixTranslation(&matT, 100, 100, 0);

	////회전
	//static float fAngle = 0.0f;
	////fAngle += 0.1f;
	//D3DXMatrixRotationZ(&matR, fAngle);

	mat = matR *matT;


	m_pSprite->SetTransform(&mat);
	
		m_pSprite->Draw(m_pTextureUI,
			&rc,
			&D3DXVECTOR3(0, 0, 0),
			&D3DXVECTOR3(50, 0, 0),
			D3DCOLOR_ARGB(255, 255, 255, 255)); // A가 알파블랜딩값

	
	m_pSprite->End();
}

void cMainGame::Setup_Particle()
{
	m_vecVertexParticle.resize(1000);//1000개쯤으로 잡아놀게
	for(int i = 0 ; i < m_vecVertexParticle.size();i++)
	{
		float fRadius = rand() % 100 / 10.0f; //무슨의미지 
		//간격을 고정시켜볼게
		fRadius = 50.0f; //별자리모양처럼됨
		m_vecVertexParticle[i].p = D3DXVECTOR3(0, 0, fRadius);
		D3DXVECTOR3 vAngle = D3DXVECTOR3(
			D3DXToRadian(rand() % 3600 / 10.0f)
			, D3DXToRadian(rand() % 3600 / 10.0f)
			, D3DXToRadian(rand() % 3600 / 10.0f));
		//Angle값을 어떻게 바꾸냐에따라 일자로나가거나 

		D3DXMATRIX matRx, matRy ,matRz, matWorld;
		D3DXMatrixRotationX(&matRx, vAngle.x);
		D3DXMatrixRotationY(&matRy, vAngle.y);
		D3DXMatrixRotationZ(&matRz, vAngle.z);

		matWorld = matRx * matRy * matRz;

		D3DXVec3TransformCoord(
			&m_vecVertexParticle[i].p,
			&m_vecVertexParticle[i].p,
			&matWorld);

		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(255, 180, 70, 20);

	}
}

void cMainGame::Update_Particle()
{
	//일정시간에 사라지게만들거야 우리가 라이프타임을 만들든지해 이친구는 그냥 사라지지말고 반짝이는 친구로
	static int nAlpha = 0;
	static int nDelta = 4;
	nAlpha += nDelta;
	
	if(nAlpha >255)
	{
		nAlpha = 255;
		nDelta *= -1;
	}

	if (nAlpha <0)
	{
		nAlpha = 0;
		nDelta *= -1;
	}

	for(int i = 0 ; i < m_vecVertexParticle.size(); i++)
	{
		if (i % 2)continue;
		m_vecVertexParticle[i].c = D3DCOLOR_ARGB(nAlpha, 180, 70, 20);
	}

	
}

void cMainGame::Render_Particle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE, FtoDW(5.0f));//점으로할껀데 확대할건지말건지에대해

	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_A, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_B, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSCALE_C, FtoDW(10.0f)); //나중에 1.0에서 10정도로 바꿔봐

	g_pD3DDevice->SetRenderState(D3DRS_POINTSPRITEENABLE, true);//포인트도 텍스쳐입힐수있게끔 해주는친구

	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MIN, FtoDW(0.0f));
	g_pD3DDevice->SetRenderState(D3DRS_POINTSIZE_MAX, FtoDW(100.0f));

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE); //MODULATE 조절하다
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_DIFFUSE);

	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	//여기까지만확인하고 따른걸 적용하든지말든지하자
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD); //일단 색깔값을 더할거야
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	//여기까지가 셋팅이야

	g_pD3DDevice->SetFVF(ST_PC_VERTEX::FVF); //fvf가멀까
	g_pD3DDevice->SetTexture(0, g_pTextureManager->GetTexture("images/alpha_tex.tga"));
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_POINTLIST,
		m_vecVertexParticle.size(),//점마다찍을거니까 안나눠 
		&m_vecVertexParticle[0],
		sizeof(ST_PC_VERTEX));

	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);

	g_pD3DDevice->SetTexture(0, NULL);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	g_pD3DDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_TEXTURE);

}

void cMainGame::SetBillboard()
{
	D3DXMATRIXA16 matBillboard, matView;
	D3DXMatrixIdentity(&matBillboard);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView); //나만바라보게 첫번쨰 뷰메트릭스를 구하고
	//나만본다는 이야기는모야 x축 y축 z축 다돌아갈거아냐 게임상에서 나만보게하면 우리는 y축에서만 바라봐도 충분해

	//그y축에대한 성분을 뽑아내면
	matBillboard._11 = matView._11;
	matBillboard._13 = matView._13;
	matBillboard._31 = matView._31;
	matBillboard._33 = matView._33;

	D3DXMATRIXA16 matT;
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, 1, 0, 0);
	matBillboard *= matT;
	//역행렬을 가져다가 곱해주면되겟지?
	D3DXMatrixInverse(&matBillboard, NULL, &matBillboard);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matBillboard);

	
}
