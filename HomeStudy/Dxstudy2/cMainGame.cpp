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
	//, m_pMeshSphere(NULL)
	, m_pObjMesh(NULL)
	, m_ptMousepick({0,0})
	, test(true)
{
	for(int i = 0 ; i < 10 ; i++)
	{
		m_stBoundShpere[i].center = D3DXVECTOR3(0, 0, 0);
		m_stBoundShpere[i].radius = 0;
	}
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
	//SafeRelease(m_pMeshSphere);
	SafeRelease(m_pObjMesh);

	for(int i = 0 ; i < 10 ; i++)
		SafeRelease(m_pMeshSphere[i]);
	
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

	m_gridVertex = m_pGrid->getGridVertex();

	
	//>>:AseLoader
	cAseLoader l;
	m_pRootFrame = l.Load("woman/woman_01_all.ASE");
	
	//<<:
	
	Setup_Obj();
	

	
	
	// >> : for texture
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
	

}

void cMainGame::Update()
{
	//if (m_pCubePC)
	//	m_pCubePC->Update();

	if (m_pCubeMan)
		m_pCubeMan->Update(m_pMap);
	
	if (m_pCamera)
		m_pCamera->Update();

	if (m_pRootFrame)
		m_pRootFrame->Update(m_pRootFrame->GetKeyFrame(),NULL);//처음엔 널을 넣어주면 되겠지?
	
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

	/*if (m_pCubePC)
		m_pCubePC->Render();*/
	//Obj_Render();
	
	//if (m_pLight)
	//	m_pLight->Render();

	//일단 지우고 테스트합시다 .
	if (m_pCubeMan)
		m_pCubeMan->Render();

	//AseLoader
	{
		if (m_pRootFrame)
			m_pRootFrame->Render();
	}

	//MeshRender
	Mesh_Render();
	
	

	g_pD3DDvice->EndScene();
	g_pD3DDvice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	if (m_pCamera)
		m_pCamera->WndProc(hWnd, message, wParam, lParam);

	//if (m_pLight)
	//	m_pLight->WndProc(hWnd, message, wParam, lParam);


	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_ptMousepick.x = LOWORD(lParam);
		m_ptMousepick.y = HIWORD(lParam);

		MousePicking(m_ptMousepick,message);
			
			
	}
	break;
	case WM_RBUTTONDOWN:
	{
		m_ptMousepick.x = LOWORD(lParam);
		m_ptMousepick.y = HIWORD(lParam);

		MousePicking(m_ptMousepick,message);
	}
	break;
	case WM_KEYDOWN:
	{
		switch (wParam)
		{
		case VK_SPACE:
		{
			if(test)
				BezierSetup();
			test = false;
		}
			break;
		}
	}
		break;
	}
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

void cMainGame::MousePicking(POINT ptCursor, UINT message)
{
	float fx, fy;
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	

	D3DVIEWPORT9 vp;
	g_pD3DDvice->GetViewport(&vp);

	D3DXMATRIXA16 proj;
	g_pD3DDvice->GetTransform(D3DTS_PROJECTION, &proj);

	D3DXMATRIXA16 view;
	g_pD3DDvice->GetTransform(D3DTS_VIEW, &view);
	
	
	//뷰포트 - > 투영
	D3DXVECTOR3 v;
	v.x = (((2.0f * ptCursor.x) / vp.Width) - 1) ;
	v.y = -(((2.0f * ptCursor.y) / vp.Height) - 1) ;
	v.z = 1.0f;

	//투영 - >카메라 
	v.x /= proj._11;
	v.y /= proj._22;


	//광선 좌표대입
	Ray ray;
	ray._origin = D3DXVECTOR3(0.0f, 0.0f, 0.0f); //광선의 원점
	ray._direction = D3DXVECTOR3(v.x, v.y, 1.0f); //광선의 방향

	//카메라 - > 월드
	D3DXMATRIXA16 matViewInverse;
	D3DXMatrixInverse(&matViewInverse, 0, &view);
	
	D3DXVec3TransformCoord(&ray._origin, &ray._origin, &matViewInverse);
	D3DXVec3TransformNormal(&ray._direction, &ray._direction, &matViewInverse);
	D3DXVec3Normalize(&ray._direction, &ray._direction);


	if(message == WM_LBUTTONDOWN)
	{
		for (int i = 0; i < 10; i++)
			if (raySpherelntersectionTest(&ray, m_stBoundShpere[i]))
			{
				if (!m_stBoundShpere[i].bLight)
				{
					m_stMtlSphere[i].Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
					m_stMtlSphere[i].Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
					m_stMtlSphere[i].Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
					m_stBoundShpere[i].bLight = true;
				}
				else
				{
					m_stMtlSphere[i].Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
					m_stMtlSphere[i].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
					m_stMtlSphere[i].Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
					m_stBoundShpere[i].bLight = false;
				}
				return;
			}

	}
	else if(message ==WM_RBUTTONDOWN)
	{
		for (size_t i = 0; i < m_gridVertex.size(); i += 3)
		{
			float u, v, f;
			ST_PN_VERTEX pt;
			if (D3DXIntersectTri(&m_gridVertex[i + 0].p,
				&m_gridVertex[i + 1].p,
				&m_gridVertex[i + 2].p,
				&ray._origin,
				&ray._direction,
				&u, &v, &f))
			{

				if (i % 2 == 0)
				{
					for (int j = 0; j < 6; j++)
					{
						m_gridVertex[i + j].c = D3DCOLOR_XRGB(100, 0, 0);
					}
					pt.p.x = (m_gridVertex[i + 1].p.x + m_gridVertex[i + 2].p.x) / 2;
					pt.p.z = (m_gridVertex[i + 0].p.z + m_gridVertex[i + 1].p.z) / 2;
				}
				else
				{
					for (int j = 0; j < 6; j++)
					{
						m_gridVertex[i - 3 + j].c = D3DCOLOR_XRGB(100, 0, 0);
					}
					pt.p.x = (m_gridVertex[i - 3  + 1].p.x + m_gridVertex[i - 3 + 2].p.x) / 2;
					pt.p.z = (m_gridVertex[i - 3  + 0].p.z + m_gridVertex[i - 3 + 1].p.z) / 2;

				}

				m_vecMoveVertex.push_back(pt);
				m_pGrid->setGridVertex(m_gridVertex);
				return;

			}
		}
	}


	

	
	return ;
}

bool cMainGame::raySpherelntersectionTest(Ray* ray , BoundingSphere shpere)
{
	
	D3DXVECTOR3 v = ray->_origin - shpere.center;

	float b = 2.0f * D3DXVec3Dot(&ray->_direction, &v);
	float c = D3DXVec3Dot(&v, &v) - (shpere.radius * shpere.radius);

	

	//판벽식을 찾는다.
	float discriminant = (b*b) - (4.0f *c);

	//가상의 수에 대한 테스트
	if (discriminant < 0.0f)
		return false;
	
	discriminant =  sqrtf(discriminant);
	float s0 = (-b + discriminant) / 2.0f;
	float s1 = (-b - discriminant) / 2.0f;
	//해가 >= 0일 경우 구체를 교차하는 것이다.
		if (s0 >= 0.0f ||s1 >= 0.0f)
			return true;


		
	
	return false;
}

void cMainGame::BezierSetup()
{
	ST_PN_VERTEX v;
	//>> :hexagon Setup
	//for (int i = 0; i < m_ptMove.size(); i++)// 0 1 2 3 4 5 0 
	//{
	//	v.p.x = m_ptMove[i].x;
	//	m_vecMoveVertex.push_back(v);
	//}

	v.p = m_vecMoveVertex[0].p;
	m_vecMoveVertex.push_back(v);
	//<< : 


	//>>:m_vBezier
	float div = 16;
	float t = 1 / div;

	for (int i = 0; i < m_vecMoveVertex.size() - 1; i += 2)
	{
		for (int j = 0; j < div; j++)
		{
			v.p = pow(1 - (t*j), 2) * m_vecMoveVertex[i].p + 2 * (t*j)*(1 - (t*j))*m_vecMoveVertex[i + 1].p + pow((t*j), 2)*m_vecMoveVertex[i + 2].p;
			m_vecBezierVertex.push_back(v);
		}
	}

	v.p = m_vecBezierVertex[0].p;
	m_vecBezierVertex.push_back(v);


	m_pCubeMan->cCharacter::SetupMove(m_vecBezierVertex.size() , m_vecBezierVertex);

	//m_iSize = m_vecBezierVertex.size();
}



void cMainGame::Setup_MeshObejct()
{
	D3DXCreateTeapot(g_pD3DDvice, &m_pMeshTeapot, NULL);
	

	ZeroMemory(&m_stMtlTeapot, sizeof(D3DMATERIAL9));
	m_stMtlTeapot.Ambient = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Diffuse = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);
	m_stMtlTeapot.Specular = D3DXCOLOR(0.0f, 0.7f, 0.7f, 1.0f);


	for(int i = 0 ; i < 10; i++)
	{
		D3DXCreateSphere(g_pD3DDvice, 0.5f, 10, 10, &m_pMeshSphere[i], NULL);
		ZeroMemory(&m_stMtlSphere[i], sizeof(D3DMATERIAL9));
		m_stMtlSphere[i].Ambient = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
		m_stMtlSphere[i].Diffuse = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
		m_stMtlSphere[i].Specular = D3DXCOLOR(0.7f, 0.7f, 0.0f, 1.0f);
		m_stBoundShpere[i].center = D3DXVECTOR3(0, 0, 2*i);
		m_stBoundShpere[i].radius = 0.5f;
	}
	


	//Mesh Loader사용
	cObjLoader l;
	m_pObjMesh = l.LoadMesh(m_vecObjMtltex, "obj", "map.obj");

	
}

void cMainGame::Mesh_Render()
{
	g_pD3DDvice->SetTexture(0, NULL);
	
	D3DXMATRIXA16 matWorld, matS, matR ,matT;

	//{
	//	D3DXMatrixIdentity(&matS);
	//	D3DXMatrixIdentity(&matR);
	//	matWorld = matS* matR;
	//	D3DXMatrixTranslation(&matWorld, 0, 0, 10);

	//	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	//	g_pD3DDvice->SetMaterial(&m_stMtlTeapot);
	//	m_pMeshTeapot->DrawSubset(0); //지금은 속성이 하나뿐이니까 0해주면대 여러개면 값을 넣어주면되고
	//	
	//}

	for(int i = 0 ; i < 10 ; i++)
	{
		D3DXMatrixIdentity(&matS);
		D3DXMatrixIdentity(&matR);
		D3DXMatrixIdentity(&matT);
		D3DXMatrixTranslation(&matT, 0, 0, 2*i);
		matWorld = matS* matR * matT;
		
		g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDvice->SetMaterial(&m_stMtlSphere[i]);
		m_pMeshSphere[i]->DrawSubset(0); //지금은 속성이 하나뿐이니까 0해주면대 여러개면 값을 넣어주면되고
	

	
	}



	

	/*{
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

	*/
}
