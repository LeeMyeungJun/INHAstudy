#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "cCubeMan.h"
#include "cLight.h"
#include "cObjLoader.h"
#include "cGroup.h"
#include "cObjMap.h"
#include "cAseLoader.h"
#include "cFrame.h"
#include "cRawLoader.h"


//D3DXMatrixRotationX()
//D3Dxvec3TransformNormal 사용  등등 이름비슷하니까 찾아쓰도록

cMainGame::cMainGame()
	:m_pCubePC(NULL)
	, m_pCamera(NULL)
	, m_pGrid(NULL)
	, m_pCubeMan(NULL)
	, m_pTexture(NULL)
	, m_pLight(NULL)
	, m_pMap(NULL)
	, m_pRootFrame(NULL)
	, m_pMeshTeapot(NULL)
	, m_pMeshSphere(NULL)
	, m_pObjMesh(NULL)
{
	
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pCubePC);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pCubeMan);
	SafeDelete(m_pMap);
	SafeRelease(m_pTexture);
	SafeRelease(m_pMeshTeapot);
	SafeRelease(m_pMeshSphere);
	SafeRelease(m_pObjMesh);
	SafeRelease(m_pRawTexture);

	for each(auto p in m_vecObjMtltex)
		SafeRelease(p);


	for each(auto p in m_vecGroup)
	{
		SafeRelease(p);
	}
	m_vecGroup.clear();

	//>>AseLoader:
	m_pRootFrame->Destroy();
	//<<:
	g_pObjectManager->Destroy();

	g_pDeveceManager->Destroy();
}

void cMainGame::Setup()
{
	//Setup_Line();
	//Setup_Triangle();

	//m_pLight = new cLight;
	//m_pLight->Setup();
	
	//m_pCubePC = new cCubePC;
	//m_pCubePC->Setup();

	m_pCubeMan = new cCubeMan;
	m_pCubeMan->Setup();
	


	m_pCamera = new cCamera;
	m_pCamera->Setup(&m_pCubeMan->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	//>>:AseLoader
	cAseLoader l;
	m_pRootFrame = l.Load("woman/woman_01_all.ASE");
	
	//<<:
	
	Setup_Obj();
	

	
	
	// >> : for texture
	D3DXCreateTextureFromFile(g_pD3DDvice, L"raw/terrain.jpg", &m_pRawTexture);
	D3DXCreateTextureFromFile(g_pD3DDvice, L"수지.png",&m_pTexture);
	{
		//좌하단먼저 그릴거야 
		ST_PT_VERTEX v;
		v.p = D3DXVECTOR3(0, 0, 0);
		v.t = D3DXVECTOR2(0, 1);
		m_vecVertex.push_back(v);

		//상단으로가면
		v.p = D3DXVECTOR3(0, 2, 0);
		v.t = D3DXVECTOR2(0, 0);
		m_vecVertex.push_back(v);

		
		v.p = D3DXVECTOR3(2, 2, 0);
		v.t = D3DXVECTOR2(1, 0);
		m_vecVertex.push_back(v);

		v.p = D3DXVECTOR3(0, 0, 0);
		v.t = D3DXVECTOR2(0, 1);
		m_vecVertex.push_back(v);

		//상단으로가면
		v.p = D3DXVECTOR3(2, 2, 0);
		v.t = D3DXVECTOR2(1, 0);
		m_vecVertex.push_back(v);


		v.p = D3DXVECTOR3(2, 0, 0);
		v.t = D3DXVECTOR2(1, 1);
		m_vecVertex.push_back(v);

	}
	
	Set_Light();

	Setup_MeshObejct();
	Load_Raw();
	m_vPosition = m_pCubeMan->GetPosition();


}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update();

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);
	
	if (m_pCamera)
		m_pCamera->Update();

	//if (m_pRootFrame)
	//	m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(),NULL);//처음엔 널을 넣어주면 되겠지?
	
	//if (m_pLight)
	//	m_pLight->Update();

	
	
}

void cMainGame::Render()
{
	if (g_pD3DDvice)
		g_pD3DDvice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 45, 48), 1.0f, 0);

	g_pD3DDvice->BeginScene();

	//Draw_Texture();

	if (m_pGrid)
		m_pGrid->Render();

	//if (m_pCubePC)
	//	m_pCubePC->Render();
	//Obj_Render();
	
	//if (m_pLight)
	//	m_pLight->Render();

	//일단 지우고 테스트합시다 .
	if (m_pCubeMan)
		m_pCubeMan->Render();

	//AseLoader
	//{
	//	if (m_pRootFrame)
	//		m_pRootFrame->Render();
	//}

	//MeshRender
	//Mesh_Render();
	Render_Raw();
	

	g_pD3DDvice->EndScene();
	g_pD3DDvice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	//if (m_pLight)
	//	m_pLight->WndProc(hWnd, message, wParam, lParam);
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
	//g_pD3DDvice->DrawPrimitive()//지금안쓸거야 정희한 포멧을 쓸거니까.
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
	//g_pD3DDvice->DrawPrimitive()//지금안쓸거야 정희한 포멧을 쓸거니까.
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size() / 3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부
}

void cMainGame::Set_Light()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	D3DXVECTOR3 vDir(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	g_pD3DDvice->SetLight(0, &stLight);
	g_pD3DDvice->LightEnable(0, true);
	//g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);
}

void cMainGame::Draw_Texture()
{
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld); //월드에 텍스쳐를 적용
	g_pD3DDvice->SetTexture(0, m_pTexture);
	g_pD3DDvice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PT_VERTEX));
	g_pD3DDvice->SetTexture(0, NULL); //월드에 텍스쳐빼기
}

void cMainGame::Setup_Obj()
{
	cObjLoader l;
	l.Load(m_vecGroup, "obj", "map.obj");

	Load_Surface();
	
}

void cMainGame::Obj_Render()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
	
	matWorld = matS* matR;
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);

	for each(auto p in m_vecGroup)
	{
		p->Render();
	}
	//D3DXIntersectTri(v1, v2, v3, rayPos, rayDir, u, v, f);
}

void cMainGame::Load_Surface()
{
	D3DXMATRIXA16 matWorld, matS, matR;
	D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
	D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);

	matWorld = matS* matR;
	m_pMap = new cObjMap("obj", "map_surface.obj", &matWorld);
}

void cMainGame::Setup_MeshObejct()
{
	D3DXCreateTeapot(g_pD3DDvice, &m_pMeshTeapot, NULL);
	D3DXCreateSphere(g_pD3DDvice, 0.5f, 10, 10, &m_pMeshSphere, NULL);

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);

	ZeroMemory(&m_stMtlSphere, sizeof(D3DMATERIAL9));
	m_stMtlSphere.Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
	m_stMtlSphere.Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);


	//Mesh Loader사용
	cObjLoader l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtltex, "obj", "map.obj");

	
}

void cMainGame::Mesh_Render()
{
	g_pD3DDvice->SetTexture(0, NULL);
	
	D3DXMATRIXA16 matWorld, matS, matR;

	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS* matR;
		D3DXMatrixTranslation(&matWorld, 0, 0, 10);

		g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDvice->SetMaterial(&m_stMtlTeapot);
		m_pMeshTeapot->DrawSubset(0); //지금은 속성이 하나뿐이니까 0해주면대 여러개면 값을 넣어주면되고
		
	}

	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS* matR;
//		D3DXMatrixTranslation(&matWorld, 0, 0, 10);

		g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDvice->SetMaterial(&m_stMtlSphere);
		m_pMeshSphere->DrawSubset(0); //지금은 속성이 하나뿐이니까 0해주면대 여러개면 값을 넣어주면되고

	}

	{
		D3DXMatrixIdentity(&matWorld);

		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		matWorld = matS* matR;
		D3DXMatrixScaling(&matS, 0.01f, 0.01f, 0.01f);
		D3DXMatrixRotationX(&matR, -D3DX_PI / 2.0F);
		matWorld = matS * matR;

		g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);

		for(size_t i = 0; i < m_vecObjMtltex.size();i++)
		{
			g_pD3DDvice->SetMaterial(&m_vecObjMtltex[i]->GetMaterial());
			g_pD3DDvice->SetTexture(0,m_vecObjMtltex[i]->GetTexture());
			m_pObjMesh->DrawSubset(i);

		}

	}
}

void cMainGame::Load_Raw()
{
	cRawLoader r;
	r.RawLoader("raw/HeightMap.raw","raw/terrain.jpg" , m_vecRawVertex);
}

void cMainGame::Render_Raw()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);
	//g_pD3DDvice->SetRenderState(D3DRS_CULLMODE, false);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PNT_VERTEX::FVF);
	g_pD3DDvice->SetTexture(0, m_pRawTexture);
	
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecRawVertex.size() / 3,
		&m_vecRawVertex[0],
		sizeof(ST_PNT_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부

	g_pD3DDvice->SetTexture(0, NULL);
}

void cMainGame::Height_Raw_Position()
{
	D3DXVECTOR3 Position = m_vPosition;

	m_vPosition = m_vecRawVertex[0].p;

}
