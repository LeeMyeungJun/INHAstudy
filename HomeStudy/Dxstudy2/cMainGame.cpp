#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"


//D3DXMatrixRotationX()
//D3Dxvec3TransformNormal ���  ��� �̸�����ϴϱ� ã�ƾ�����

cMainGame::cMainGame()
{
	
}


cMainGame::~cMainGame()
{
	g_pDeveceManager->Destroy();
}

void cMainGame::Setup()
{
	Setup_Line();
	Setup_Triangle();
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);//����Ʈ ����
	

}

void cMainGame::Update()
{
	
}

void cMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXVECTOR3 vEye = D3DXVECTOR3(0, 0, -5.0f);
	D3DXVECTOR3 vLookAt = D3DXVECTOR3(0, 0, 0);
	D3DXVECTOR3 vUp = D3DXVECTOR3(0, 1, 0);

	D3DXMATRIXA16 matView;
	
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);

	g_pD3DDvice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDvice->SetTransform(D3DTS_PROJECTION, &matProj);
	
	
	g_pD3DDvice->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(0, 0,255), 1.0f, 0);

	g_pD3DDvice->BeginScene();

	Draw_Line();
	Draw_Triangle();
	
	g_pD3DDvice->EndScene();
	
	g_pD3DDvice->Present(NULL, NULL, NULL, NULL);
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
