#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"
#include "cCubePC.h"
#include "cCamera.h"
#include "cGrid.h"
#include "Player.h"
#include "xFileLoader.h"


//D3DXMatrixRotationX()
//D3Dxvec3TransformNormal ���  ��� �̸�����ϴϱ� ã�ƾ�����

cMainGame::cMainGame()
	:m_pCamera(NULL)
	,m_pGrid(NULL)
	,m_pPlayer(NULL)
	, m_pXFile(NULL)
{
	
}


cMainGame::~cMainGame()
{
	SafeDelete(m_pPlayer);
	SafeDelete(m_pCamera);
	SafeDelete(m_pGrid);
	SafeDelete(m_pXFile);
	g_pDeveceManager->Destroy();
}

void cMainGame::Setup()
{
	//Setup_Line();
	//Setup_Triangle();

	//m_pCubePC = new cCubePC;
	//m_pCubePC->Setup();

	setLight();
	
	m_pPlayer = new Player;
	m_pPlayer->Setup();

	m_pCamera = new cCamera; //0,0,0
	m_pCamera->Setup(&m_pPlayer->GetPosition());

	m_pGrid = new cGrid;
	m_pGrid->Setup();

	m_pXFile = new xFileLoader;
	m_pXFile->Setup_Xfile("xFile/bigship1.x");
	//Setup_Xfile();
	
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);//����Ʈ ����

	

}

void cMainGame::Update()
{
	if (m_pPlayer)
	{
		m_pPlayer->Update();
	}

	if (m_pCamera)
		m_pCamera->Update();
	
}

void cMainGame::Render()
{
	if (g_pD3DDvice)
		g_pD3DDvice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(45, 45, 48), 1.0f, 0);

	g_pD3DDvice->BeginScene();

	if (m_pGrid)
		m_pGrid->Render();

	if (m_pPlayer)
		m_pPlayer->Render();


	m_pXFile->Render_Xfile();
	
	g_pD3DDvice->EndScene();
	g_pD3DDvice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);
}

void cMainGame::Setup_Line()
{
	ST_PC_VERTEX v;
	v.c = D3DCOLOR_XRGB(255, 0, 0); //������ . ������ �⺻ ������ �־ �׳ɺ����� �������� 
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
	D3DXMatrixIdentity(&matWorld); //�׵���ķ� �ʱ�ȭ
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDvice->DrawPrimitive()//���ݾȾ��ž� ������ ������ ���Ŵϱ�.
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_LINELIST,
		m_vecLineVertex.size() / 2,
		&m_vecLineVertex[0],
		sizeof(ST_PC_VERTEX));//1���� �� Ÿ�� ������ , ������  1��°Ÿ�� ������ ���ΰ���
}



void cMainGame::Draw_Triangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld); //�׵���ķ� �ʱ�ȭ


	D3DXVECTOR3 vPosition = D3DXVECTOR3(5, 0, 5);
	D3DXMatrixTranslation(&matWorld, vPosition.x, vPosition.y, vPosition.z);
	
	
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDvice->DrawPrimitive()//���ݾȾ��ž� ������ ������ ���Ŵϱ�.
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size() / 3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));//1���� �� Ÿ�� ������ , ������  1��°Ÿ�� ������ ���ΰ���
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



