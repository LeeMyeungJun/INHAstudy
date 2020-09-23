#include "stdafx.h"
#include "cMainGame.h"

const float speed = 0.1f;
const int angle = 10;
cMainGame::cMainGame()
	:m_hBitmap(NULL)
	, m_vEye(0, 0, -5) //ī�޶� ��¦ �ڷ�
	, m_vLookAt(0, 0, 0)  //�������ٶ󺸰�
	, m_vUp(0, 1, 0)
	, m_vPosition(0, 0, 0)
	, m_fCameraDistance(5.0f)
	, m_isButtonDown(false)
	, m_vCamRotAngle(0,0,0)
	, m_fBoxRotY(0.0f)
	, m_vBoxDirection(0,0,1)
	, m_ptPrevMouse{0,0}
{

	
}


cMainGame::~cMainGame()
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void cMainGame::SetGrid()
{
	int nNumHalfTile = 5;
	float fInterval = 1.0f;
	float fMax = nNumHalfTile *fInterval;
	float fMin = -nNumHalfTile *fInterval;

	for (int i = 1; i < nNumHalfTile; i++)
	{
		m_vecLineVertex.push_back(cVector3(fMin, 0, i*fInterval));
		m_vecLineVertex.push_back(cVector3(fMax, 0, i*fInterval));

		m_vecLineVertex.push_back(cVector3(fMin, 0, -i*fInterval));
		m_vecLineVertex.push_back(cVector3(fMax, 0, -i*fInterval));

		m_vecLineVertex.push_back(cVector3(i*fInterval, 0,fMin	));
		m_vecLineVertex.push_back(cVector3(i*fInterval, 0, fMax));

		m_vecLineVertex.push_back(cVector3(-i*fInterval, 0, fMin));
		m_vecLineVertex.push_back(cVector3(-i*fInterval, 0, fMax));
	}
	m_vecLineVertex.push_back(cVector3(0, 0, fMin));
	m_vecLineVertex.push_back(cVector3(0, 0, fMax));
	
	m_vecLineVertex.push_back(cVector3(fMin, 0, 0));
	m_vecLineVertex.push_back(cVector3(fMax, 0, 0));

	m_vAxisXTexPosition = cVector3(fMax, 0, 0);
	m_vAxisZTexPosition = cVector3(0, 0, fMax);
}

void cMainGame::DrawGrid()
{
	cMatrix mat = m_matView * m_matProj * m_matViewport;


	for(size_t i = 0 ; i < m_vecLineVertex.size();  i+= 2)
	{
		cVector3 v1 = m_vecLineVertex[i + 0];
		cVector3 v2 = m_vecLineVertex[i + 1];

		v1 = cVector3::TransformCoord(v1, mat);
		v2 = cVector3::TransformCoord(v2, mat);

		MoveToEx(m_MemDC, v1.getX(), v1.getY(), NULL);
		LineTo(m_MemDC, v2.getX(), v2.getY());
	}
	cVector3 v = m_vAxisXTexPosition;
	v = cVector3::TransformCoord(v, mat);
	TextOut(m_MemDC, v.getX(), v.getY(), (LPCWSTR)"X", 1);

	v = m_vAxisZTexPosition;
	v = cVector3::TransformCoord(v, mat);
	TextOut(m_MemDC, v.getX(), v.getY(), (LPCWSTR)"Z", 1);

}

void cMainGame::Update_Move()
{
	if(GetKeyState('W') & 0x8000)
	{
		m_vPosition = m_vPosition + (m_vBoxDirection * 0.1f);
	}

	if (GetKeyState('S') & 0x8000)
	{
		m_vPosition = m_vPosition - (m_vBoxDirection * 0.1f);
	}
}

void cMainGame::Update_Rotation()
{

	if (GetKeyState('A') & 0x8000)
	{
		m_fBoxRotY -= 1.5f;
	}

	if (GetKeyState('D') & 0x8000)
	{
		m_fBoxRotY += 1.5f;
	}
}

bool cMainGame::IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3)
{
	cVector3 bc1 = v2 - v1;
	cVector3 bc2 = v3 - v1;
	cVector3 bc3 = cVector3::Cross(bc1, bc2).Normlize();
	if (bc3.getZ() > 0)
	{
		return true;
	}

	return false;
}


void cMainGame::Setup()
{
	
	HDC hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(hdc);
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);

	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
	ReleaseDC(g_hWnd, hdc);
	//�ո�
	m_vecVecrtex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
	m_vecVecrtex.push_back(cVector3(-1.0f,  1.0f, -1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f,  1.0f, -1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f,  -1.0f, -1.0f));
	//�޸�
	m_vecVecrtex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
	m_vecVecrtex.push_back(cVector3(-1.0f,  1.0f, 1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f,  1.0f, 1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f, -1.0f, 1.0f));

	{
		
	
	//
	//�� �ﰢ��
	
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	//�ﰢ�� Ŭ��������  �ð���� 012  023 465 476 �ٽð�����̾�
	//465�� �ֽð�����̾�? : �޸��̴ϱ� �ٱ��ʿ��� ������ 465�� �ð������

	//��
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);

	//����
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);
	
	//������
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	//��
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	//�Ʒ�
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	}
	
	
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);

	SetGrid(); //<<�׸��� �����ϴ°� ȣ��

	////m_FrontVec = cVector3(0, 0, 1).Normlize();

	//m_Rotation  = cMatrix::Identity(4);
	//m_Scale		= cMatrix::Identity(4);
	//m_Translate = cMatrix::Identity(4);
	////m_fCameraZoom = 20.0f;
	//m_fCameraDistance = -5;
	////m_fCameraAngle = 0;

}

void cMainGame::Update()
{

	//����� ������ ���߰���? 
	Update_Rotation(); //R
	Update_Move(); // T���ݾ� 
	
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	//���콺 ȸ��ó��
	cMatrix matRx = cMatrix::RotatinX(m_vCamRotAngle.getX());
	cMatrix matRy = cMatrix::RotatinY(m_vCamRotAngle.getY());
	cMatrix matR = matRx *matRy;
	
	m_vEye = cVector3(0, m_fCameraDistance, -m_fCameraDistance);//�������������� y���� �����������
	m_vEye = cVector3::TransformCoord(m_vEye, matR); //?? �����̵� ���̴ϱ� ��� ����ؾ��ϴ°žƴѰ��ΰ� . 
	
	m_vLookAt = m_vPosition;
	m_vEye = m_vEye + m_vPosition; //���󰡴°����̰�

	matR = cMatrix::RotatinY(m_fBoxRotY);
	m_vBoxDirection = cVector3(0, 0, 1);
	m_vBoxDirection = cVector3::TransformNormal(m_vBoxDirection, matR);

	m_matWorld = matR * cMatrix::Translation(m_vPosition); //�����Ʈ���� ���� ���������
	

	m_matView	  = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj	  = cMatrix::Projection(45, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::ViewPort(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS); //����� �Ͼ������ ��ĥ�ع����ڴٴ� �ǹ�

	/*m_matRectWorld =  m_RectScale * m_RectRotation * m_RectTranslate;
	*/
	cMatrix matRectWVP = m_matWorld * m_matView * m_matProj;

	
	
	for(size_t i = 0 ; i < m_vecIndex.size(); i+=3)
	{
		cVector3 v1 = m_vecVecrtex[m_vecIndex[i+0]];
		cVector3 v2 = m_vecVecrtex[m_vecIndex[i+1]];
		cVector3 v3 = m_vecVecrtex[m_vecIndex[i+2]];

		v1 = cVector3::TransformCoord(v1, matRectWVP);
		v2 = cVector3::TransformCoord(v2, matRectWVP);
		v3 = cVector3::TransformCoord(v3, matRectWVP);
		//���Ʒ� ���� ������������ �����̽��ø��Ϸ���
		if (IsBackFace(v1, v2, v3))
			continue;
		
		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

	
		
		

		MoveToEx(m_MemDC, v1.getX(), v1.getY(), NULL);
		LineTo(m_MemDC, v2.getX(), v2.getY());
		LineTo(m_MemDC, v3.getX(), v3.getY());
		LineTo(m_MemDC, v1.getX(), v1.getY());	
	}
	
	DrawGrid();
	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
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
			if(m_isButtonDown)
			{
				POINT ptCurMouse;
				ptCurMouse.x = LOWORD(lParam);
				ptCurMouse.y = HIWORD(lParam);

				float fDeltaX = (float)ptCurMouse.x - m_ptPrevMouse.x;
				float fDeltaY = (float)ptCurMouse.y - m_ptPrevMouse.y;
				m_vCamRotAngle.SetY(m_vCamRotAngle.getY() + (fDeltaX / 10.f)); //fDeltaX ������
				m_vCamRotAngle.SetX(m_vCamRotAngle.getX() + (fDeltaY / 10.f)); //fDeltaY ������ /100������

				if (m_vCamRotAngle.getX() < -200 / 2.0f + 0.0001f)
					m_vCamRotAngle.SetX(-200 / 2.0f + 0.0001f);

				if (m_vCamRotAngle.getX() > 90 / 2.0f - 0.0001f)
					m_vCamRotAngle.SetX(90 / 2.0f - 0.0001f);

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
