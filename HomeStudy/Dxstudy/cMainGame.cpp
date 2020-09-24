#include "stdafx.h"
#include "cMainGame.h"
#include "cDeviceManager.h"


//D3DXMatrixRotationX()
//D3Dxvec3TransformNormal 사용  등등 이름비슷하니까 찾아쓰도록
//각점별로 색을가지고있으면 색이 서로 막 이쁘게 그라데이션효과가짐

cMainGame::cMainGame()
	:vEye(D3DXVECTOR3(20, 5, 10.0f)),
	vLookAt(D3DXVECTOR3(0, 0, 0)),
	vUp(D3DXVECTOR3(0, 1, 0))
{
	/*vEye = D3DXVECTOR3(20, 5, 10.0f);
	vLookAt = D3DXVECTOR3(0, 0, 0);
	vUp = D3DXVECTOR3(0, 1, 0);*/
}


cMainGame::~cMainGame()
{
	g_pDeveceManager->Destroy();
}

void cMainGame::Setup()
{
	m_vPosition = D3DXVECTOR3(0, 0, 0);
	m_vBoxDirection = D3DXVECTOR3(0, 0, 1);
	m_vCamRotAngle = D3DXVECTOR3(0, 0, 0);
	m_fBoxRotY = 0;
	m_fCameraDistance = 5.0f;
	//Setup_Line();
	Setup_Grid();
	//Setup_Triangle();
	Setup_Rectangle();
	Setup_Pyramid();
	m_isButtonDown= false;

	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);//라이트 끄기

}

void cMainGame::Update()
{

	Update_Move();
	Update_Rotation();

	D3DXMATRIXA16 matRx , matRy;
	D3DXMatrixRotationX(&matRx, m_vCamRotAngle.x);
	D3DXMatrixRotationY(&matRy,m_vCamRotAngle.y);
	m_matR = matRx *matRy;
	
	vEye = D3DXVECTOR3(0, m_fCameraDistance, -m_fCameraDistance);
	D3DXVec3TransformCoord(&vEye,&vEye, &m_matR);
	
	D3DXMatrixTranslation(&m_matTranslate,m_vPosition.x, m_vPosition.y, m_vPosition.z);
	D3DXMatrixRotationY(&m_matR, m_fBoxRotY);
	m_vBoxDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vBoxDirection,&m_vBoxDirection,&m_matR);
	
	// >:플레이어 이동
	vLookAt = m_vPosition;
	vEye = vEye + m_vPosition;
	// <:
}

void cMainGame::Render()
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);

	D3DXMATRIXA16 matView;
	
	D3DXMatrixLookAtLH(&matView, &vEye, &vLookAt, &vUp);

	g_pD3DDvice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	g_pD3DDvice->SetTransform(D3DTS_PROJECTION, &matProj);
	
	
	g_pD3DDvice->Clear(0, 0, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER,D3DCOLOR_XRGB(47,121,122), 1.0f, 0);

	g_pD3DDvice->BeginScene();

	//Draw_Line();
	//Draw_Triangle();
	Draw_Grid();
	Draw_Rectangle();
	Draw_Pyramid();
	g_pD3DDvice->EndScene();
	
	g_pD3DDvice->Present(NULL, NULL, NULL, NULL);
}

void cMainGame::WndProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_LBUTTONDOWN:
	{
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		m_isButtonDown = true;
	}
	break;
	case WM_LBUTTONUP:
	{
		m_isButtonDown = false;
	}
	break;
	case WM_MOUSEMOVE:
	{
		if (m_isButtonDown)
		{
			POINT ptCurMouse;
			ptCurMouse.x = LOWORD(lParam);
			ptCurMouse.y = HIWORD(lParam);

			float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
			float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
			m_vCamRotAngle.y = (m_vCamRotAngle.y + (fDeltaX / 100.f)); //fDeltaX 축으로
			m_vCamRotAngle.x = (m_vCamRotAngle.x + (fDeltaY / 100.f)); //fDeltaY 축으로 /100이유모름

			if (m_vCamRotAngle.x < -200 / 2.0f + 0.0001f)
				m_vCamRotAngle.x =(-200 / 2.0f + 0.0001f);

			if (m_vCamRotAngle.x > 90 / 2.0f - 0.0001f)
				m_vCamRotAngle.x =(90 / 2.0f - 0.0001f);

			m_ptPrevMouse = ptCurMouse;

		}
	}
	break;
	case WM_MOUSEWHEEL:
	{
		m_fCameraDistance -= (GET_WHEEL_DELTA_WPARAM(wParam) / 250.0f);
		if (m_fCameraDistance < 0.0001f)
			m_fCameraDistance = 0.0001f;
	}
	break;
	case WM_KEYDOWN:
		break;
	default:
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
	v.c = D3DCOLOR_XRGB(255, 0, 0);
	v.p = D3DXVECTOR3(-1.0f, -1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

	v.p = D3DXVECTOR3(-1.0f, 1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

	v.p = D3DXVECTOR3(1.0f, 1.0f, 0.0f);
	m_vecTriangleVertex.push_back(v);

}

void cMainGame::Setup_Grid()
{
	ST_PC_VERTEX	v;
	v.c = D3DCOLOR_XRGB(255, 120, 0);
	
	int nNumHalfTile = 10;
	float fInterval = 2.0f;
	float fMax = nNumHalfTile *fInterval;
	float fMin = -nNumHalfTile *fInterval;

	for (int i = 1; i < nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecLineVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecLineVertex.push_back(v);

		v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		m_vecLineVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		m_vecLineVertex.push_back(v);
	}
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecLineVertex.push_back(v);

	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecLineVertex.push_back(v);


	v.c = D3DCOLOR_XRGB(255, 255, 0);

	nNumHalfTile = 2;
	fInterval = 10.0f;
	fMax = nNumHalfTile *fInterval;
	fMin = -nNumHalfTile *fInterval;

	for (int i = 1; i < nNumHalfTile; i++)
	{
		v.p = D3DXVECTOR3(fMin, 0, i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, i*fInterval);
		m_vecLineVertex.push_back(v);

		v.p = D3DXVECTOR3(fMin, 0, -i*fInterval);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(fMax, 0, -i*fInterval);
		m_vecLineVertex.push_back(v);

		v.p = D3DXVECTOR3(i*fInterval, 0, fMin);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(i*fInterval, 0, fMax);
		m_vecLineVertex.push_back(v);

		v.p = D3DXVECTOR3(-i*fInterval, 0, fMin);
		m_vecLineVertex.push_back(v);
		v.p = D3DXVECTOR3(-i*fInterval, 0, fMax);
		m_vecLineVertex.push_back(v);
	}
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecLineVertex.push_back(v);

	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecLineVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(255, 0, 0);
	
	//x라인
	v.p = D3DXVECTOR3(fMin, 0, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(fMax, 0, 0);
	m_vecLineVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 255, 0);
	//y라인
	v.p = D3DXVECTOR3(0, fMin, 0);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, fMax, 0);
	m_vecLineVertex.push_back(v);

	v.c = D3DCOLOR_XRGB(0, 0, 255);
	//z라인
	v.p = D3DXVECTOR3(0, 0, fMin);
	m_vecLineVertex.push_back(v);
	v.p = D3DXVECTOR3(0, 0, fMax);
	m_vecLineVertex.push_back(v);
	

}
void cMainGame::Setup_Rectangle()
{
	ST_PC_VERTEX	v;
	
	v.p = D3DXVECTOR3(-1.0f, 0.0f, -1.0f);
	m_vecRectangleVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 2.0f, -1.0f);
	m_vecRectangleVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 2.0f, -1.0f);
	m_vecRectangleVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 0.0f, -1.0f);
	m_vecRectangleVertex.push_back(v);
	//뒷면
	v.p = D3DXVECTOR3(-1.0f, 0.0f, 1.0f);
	m_vecRectangleVertex.push_back(v);
	v.p = D3DXVECTOR3(-1.0f, 2.0f, 1.0f);
	m_vecRectangleVertex.push_back(v);
	v.p = D3DXVECTOR3( 1.0f, 2.0f, 1.0f);
	m_vecRectangleVertex.push_back(v);
	v.p = D3DXVECTOR3(1.0f, 0.0f, 1.0f);
	m_vecRectangleVertex.push_back(v);

	{
		//앞 삼각형

		m_vecRectangleVertex[0].c = D3DCOLOR_XRGB(34,177,76);
		m_vecRectangleVertex[1].c = D3DCOLOR_XRGB(34,177,76);
		m_vecRectangleVertex[2].c = D3DCOLOR_XRGB(34,177,76);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[0]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[1]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[2]);

		m_vecRectangleVertex[0].c = D3DCOLOR_XRGB(34, 177, 76);
		m_vecRectangleVertex[2].c = D3DCOLOR_XRGB(34, 177, 76);
		m_vecRectangleVertex[3].c = D3DCOLOR_XRGB(34, 177, 76);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[0]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[2]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[3]);

		////삼각형 클럭아이즈  시계방향 012  023 465 476 다시계방향이야
		////465가 왜시계방향이야? : 뒷면이니까 바깥쪽에서 봤을떈 465가 시계방향임

		////뒤
		m_vecRectangleVertex[4].c = D3DCOLOR_XRGB(0,0,255);
		m_vecRectangleVertex[6].c = D3DCOLOR_XRGB(0,0,255);
		m_vecRectangleVertex[5].c = D3DCOLOR_XRGB(0,0,255);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[4]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[6]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[5]);

		m_vecRectangleVertex[4].c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecRectangleVertex[7].c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecRectangleVertex[6].c = D3DCOLOR_XRGB(0, 0, 255);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[4]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[7]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[6]);

		//왼쪽
		m_vecRectangleVertex[4].c = D3DCOLOR_XRGB(255,128,0);
		m_vecRectangleVertex[5].c = D3DCOLOR_XRGB(255,128,0);
		m_vecRectangleVertex[1].c = D3DCOLOR_XRGB(255,128,0);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[4]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[5]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[1]);

		m_vecRectangleVertex[4].c = D3DCOLOR_XRGB(255, 128, 0);
		m_vecRectangleVertex[1].c = D3DCOLOR_XRGB(255, 128, 0);
		m_vecRectangleVertex[0].c = D3DCOLOR_XRGB(255, 128, 0);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[4]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[1]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[0]);

		//오른쪽
		m_vecRectangleVertex[3].c = D3DCOLOR_XRGB(128,25,0);
		m_vecRectangleVertex[2].c = D3DCOLOR_XRGB(128,25,0);
		m_vecRectangleVertex[6].c = D3DCOLOR_XRGB(128,25,0);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[3]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[2]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[6]);
		
		m_vecRectangleVertex[3].c = D3DCOLOR_XRGB(128, 25, 0);
		m_vecRectangleVertex[6].c = D3DCOLOR_XRGB(128, 25, 0);
		m_vecRectangleVertex[7].c = D3DCOLOR_XRGB(128, 25, 0);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[3]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[6]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[7]);

		//위
		m_vecRectangleVertex[1].c = D3DCOLOR_XRGB(255,128,255);
		m_vecRectangleVertex[5].c = D3DCOLOR_XRGB(255,128,255);
		m_vecRectangleVertex[6].c = D3DCOLOR_XRGB(255,128,255);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[1]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[5]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[6]);

		m_vecRectangleVertex[1].c = D3DCOLOR_XRGB(255, 128, 255);
		m_vecRectangleVertex[6].c = D3DCOLOR_XRGB(255, 128, 255);
		m_vecRectangleVertex[2].c = D3DCOLOR_XRGB(255, 128, 255);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[1]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[6]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[2]);

		//아래
		m_vecRectangleVertex[4].c = D3DCOLOR_XRGB(255,0,128);
		m_vecRectangleVertex[0].c = D3DCOLOR_XRGB(255,0,128);
		m_vecRectangleVertex[3].c = D3DCOLOR_XRGB(255,0,128);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[4]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[0]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[3]);

		m_vecRectangleVertex[4].c = D3DCOLOR_XRGB(255, 0, 128);
		m_vecRectangleVertex[3].c = D3DCOLOR_XRGB(255, 0, 128);
		m_vecRectangleVertex[7].c = D3DCOLOR_XRGB(255, 0, 128);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[4]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[3]);
		m_vecRectangleIndex.push_back(m_vecRectangleVertex[7]);

	}
	
}

void cMainGame::Setup_Pyramid()
{
	ST_PC_VERTEX	v;

	//y축
	{
	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecPyramidVertex.push_back(v); //0

	v.p = D3DXVECTOR3(0.3f, 5.0f, -0.3f);
	m_vecPyramidVertex.push_back(v); //1

	v.p = D3DXVECTOR3(-0.3f, 5.0f, -0.3f);
	m_vecPyramidVertex.push_back(v); //2

	v.p = D3DXVECTOR3(-0.3f, 5.0f, 0.3f);
	m_vecPyramidVertex.push_back(v);//3

	v.p = D3DXVECTOR3(0.3f, 5.0f, 0.3f);
	m_vecPyramidVertex.push_back(v);//4
	}
		
	{
		//앞 삼각형
		m_vecPyramidVertex[0].c = D3DCOLOR_XRGB(0,255,0);
		m_vecPyramidVertex[1].c = D3DCOLOR_XRGB(0,255,0);
		m_vecPyramidVertex[2].c = D3DCOLOR_XRGB(0,255,0);
		m_vecPyramidVertex[3].c = D3DCOLOR_XRGB(0,255,0);
		m_vecPyramidVertex[4].c = D3DCOLOR_XRGB(0,255,0);

		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);

		//뒤삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);

		//오른쪽삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		//왼쪽 삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		//밑삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);

		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);
	}

	
	m_vecPyramidVertex.clear();
	//x축
	{
	v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vecPyramidVertex.push_back(v); //0

	v.p = D3DXVECTOR3(5.0f, 0.3f, -0.3f);
	m_vecPyramidVertex.push_back(v); //1

	v.p = D3DXVECTOR3(5.0, -0.3f, -0.3f);
	m_vecPyramidVertex.push_back(v); //2

	v.p = D3DXVECTOR3(5.0f ,-0.3f , 0.3f);
	m_vecPyramidVertex.push_back(v);//3

	v.p = D3DXVECTOR3( 5.0f,0.3f, 0.3f);
	m_vecPyramidVertex.push_back(v);//4
	}
	
	{
		//앞 삼각형
		m_vecPyramidVertex[0].c = D3DCOLOR_XRGB(255, 0,0);
		m_vecPyramidVertex[1].c = D3DCOLOR_XRGB(255, 0,0);
		m_vecPyramidVertex[2].c = D3DCOLOR_XRGB(255, 0,0);
		m_vecPyramidVertex[3].c = D3DCOLOR_XRGB(255, 0,0);
		m_vecPyramidVertex[4].c = D3DCOLOR_XRGB(255, 0,0);

		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);

		//뒤삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);

		//오른쪽삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		//왼쪽 삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		//밑삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);

		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);
	}


	m_vecPyramidVertex.clear();
	//z축
	{
		v.p = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		m_vecPyramidVertex.push_back(v); //0

		v.p = D3DXVECTOR3(-0.3f, 0.3f, 5.0f);
		m_vecPyramidVertex.push_back(v); //1

		v.p = D3DXVECTOR3(-0.3f, -0.3f, 5.0f);
		m_vecPyramidVertex.push_back(v); //2

		v.p = D3DXVECTOR3(0.3f, -0.3f, 5.0f);
		m_vecPyramidVertex.push_back(v);//3

		v.p = D3DXVECTOR3(0.3f, 0.3f, 5.0f);
		m_vecPyramidVertex.push_back(v);//4
	}

	{
		//앞 삼각형
		m_vecPyramidVertex[0].c = D3DCOLOR_XRGB(0, 0,255);
		m_vecPyramidVertex[1].c = D3DCOLOR_XRGB(0, 0,255);
		m_vecPyramidVertex[2].c = D3DCOLOR_XRGB(0, 0,255);
		m_vecPyramidVertex[3].c = D3DCOLOR_XRGB(0, 0,255);
		m_vecPyramidVertex[4].c = D3DCOLOR_XRGB(0, 0,255);

		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);

		//뒤삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);

		//오른쪽삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		//왼쪽 삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[0]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		//밑삼각형
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[2]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);

		m_vecPyramidIndex.push_back(m_vecPyramidVertex[3]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[1]);
		m_vecPyramidIndex.push_back(m_vecPyramidVertex[4]);
	}

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
	//g_pD3DDvice->DrawPrimitive()//지금안쓸거야 정희한 포멧을 쓸거니까.
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecTriangleVertex.size() / 3,
		&m_vecTriangleVertex[0],
		sizeof(ST_PC_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부
}

void cMainGame::Draw_Grid()
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

void cMainGame::Draw_Rectangle()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld); //항등행렬로 초기화
	
	matWorld = matWorld *m_matR * m_matTranslate;
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	//g_pD3DDvice->DrawPrimitive()//지금안쓸거야 정희한 포멧을 쓸거니까.
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecRectangleIndex.size() / 3,
		&m_vecRectangleIndex[0],
		sizeof(ST_PC_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부	
}


void cMainGame::Draw_Pyramid()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld); //항등행렬로 초기화
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetFVF(ST_PC_VERTEX::FVF);
	g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		m_vecPyramidIndex.size() / 3,
		&m_vecPyramidIndex[0],
		sizeof(ST_PC_VERTEX));//1번쨰 는 타입 선인지 , 점인지  1번째타입 사용법은 따로공부

}

void cMainGame::Update_Move()
{
	if (GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vBoxDirection * 0.1);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vBoxDirection * 0.1);
	}
	

}

void cMainGame::Update_Rotation()
{

	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 0.1f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 0.1f;
	}

}
