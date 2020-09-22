#include "stdafx.h"
#include "cMainGame.h"

const int speed = 2;
const int angle = 10;
cMainGame::cMainGame()
	:m_hBitmap(NULL)
	, m_vEye(0, 0, -5) //카메라를 살짝 뒤로
	, m_vLookAt(0, 0, 0)  //원점을바라보고
	, m_vUp(0, 1, 0)
{
	
}


cMainGame::~cMainGame()
{
	SelectObject(m_MemDC, m_hOldBitmap);
	DeleteObject(m_hBitmap);
	DeleteDC(m_MemDC);
}

void cMainGame::Setup()
{
	m_iMouseX = 0, m_iMouseY = 0;
	m_bMouseClickCheck = false;
	m_fAngle = 0.0f;
	HDC hdc = GetDC(g_hWnd);
	m_MemDC = CreateCompatibleDC(hdc);
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_hBitmap = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);

	m_hOldBitmap = (HBITMAP)SelectObject(m_MemDC, m_hBitmap);
	ReleaseDC(g_hWnd, hdc);
	//앞면
	m_vecVecrtex.push_back(cVector3(-1.0f, -1.0f, -1.0f));
	m_vecVecrtex.push_back(cVector3(-1.0f,  1.0f, -1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f,  1.0f, -1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f,  -1.0f, -1.0f));
	//뒷면
	m_vecVecrtex.push_back(cVector3(-1.0f, -1.0f, 1.0f));
	m_vecVecrtex.push_back(cVector3(-1.0f,  1.0f, 1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f,  1.0f, 1.0f));
	m_vecVecrtex.push_back(cVector3( 1.0f, -1.0f, 1.0f));

	{
		
	
	//
	//앞 삼각형
	
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(2);

	m_vecIndex.push_back(0);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(3);

	//삼각형 클럭아이즈  시계방향 012  023 465 476 다시계방향이야
	//465가 왜시계방향이야? : 뒷면이니까 바깥쪽에서 봤을떈 465가 시계방향임

	//뒤
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(5);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(7);
	m_vecIndex.push_back(6);

	//왼쪽
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(1);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(0);
	
	//오른쪽
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(2);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(3);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(7);

	//위
	m_vecIndex.push_back(1);
	m_vecIndex.push_back(5);
	m_vecIndex.push_back(6);

	m_vecIndex.push_back(1);
	m_vecIndex.push_back(6);
	m_vecIndex.push_back(2);

	//아래
	m_vecIndex.push_back(4);
	m_vecIndex.push_back(0);
	m_vecIndex.push_back(3);

	m_vecIndex.push_back(4);
	m_vecIndex.push_back(3);
	m_vecIndex.push_back(7);

	}
	for (int i = 0; i < 10; i++)
	{
		row.emplace_back(-10, 0, -10+(i * 2));
		row.emplace_back(+8, 0, -10 + (i * 2));
	}

	for (int i = 0; i < 10; i++)
	{
		col.emplace_back(-10 + (i * 2), 0, -10);
		col.emplace_back(-10 + (i * 2), 0, 8);
	}


	
	m_matGridWorld = cMatrix::Identity(4);
	m_matView = cMatrix::Identity(4);
	m_matProj = cMatrix::Identity(4);
	m_matViewport = cMatrix::Identity(4);


	m_FrontVec = cVector3(0, 0, 1).Normlize();

	m_GridRotation  = cMatrix::Identity(4);
	m_GridScale		= cMatrix::Identity(4);
	m_GridTranslate = cMatrix::Identity(4);

	m_RectRotation  = cMatrix::Identity(4);
	m_RectScale		= cMatrix::Identity(4);
	m_RectTranslate = cMatrix::Identity(4);
	m_fCameraZoom = 20.0f;
	m_fCameraDistance = -5;
	m_fCameraAngle = 0;
	RowCoord.resize(20);
	ColCoord.resize(20);
}

void cMainGame::Update()
{

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	m_vLookAt = cVector3(0.0f, 0.0f, 0.0f);
	m_vEye = cVector3(m_fCameraAngle, m_fCameraZoom, m_fCameraDistance);//뒤로 물러나서 봐야겠지

	m_matView	  = cMatrix::View(m_vEye, m_vLookAt, m_vUp);
	m_matProj	  = cMatrix::Projection(45, rc.right / (float)rc.bottom, 1.0f, 1000.0f);
	m_matViewport = cMatrix::ViewPort(0, 0, rc.right, rc.bottom, 0, 1);
}

void cMainGame::Render(HDC hdc)
{
	RECT rc;
	GetClientRect(g_hWnd, &rc);
	PatBlt(m_MemDC, rc.left, rc.top, rc.right, rc.bottom, WHITENESS); //배경을 하양색으로 싹칠해버리겠다는 의미

	m_matGridWorld =  m_GridScale * m_GridRotation * m_GridTranslate;
	m_matRectWorld =  m_RectScale * m_RectRotation * m_RectTranslate;

	cMatrix matGridWVP = m_matGridWorld * m_matView * m_matProj;

	cMatrix matRectWVP = m_matRectWorld * m_matView * m_matProj;
	
	
	for(size_t i = 0 ; i < m_vecIndex.size(); i+=3)
	{
		cVector3 v1 = m_vecVecrtex[m_vecIndex[i+0]];
		cVector3 v2 = m_vecVecrtex[m_vecIndex[i+1]];
		cVector3 v3 = m_vecVecrtex[m_vecIndex[i+2]];

		v1 = cVector3::TransformCoord(v1, matRectWVP);
		v2 = cVector3::TransformCoord(v2, matRectWVP);
		v3 = cVector3::TransformCoord(v3, matRectWVP);

		v1 = cVector3::TransformCoord(v1, m_matViewport);
		v2 = cVector3::TransformCoord(v2, m_matViewport);
		v3 = cVector3::TransformCoord(v3, m_matViewport);

		MoveToEx(m_MemDC, v1.getX(), v1.getY(), NULL);
		LineTo(m_MemDC, v2.getX(), v2.getY());
		LineTo(m_MemDC, v3.getX(), v3.getY());
		LineTo(m_MemDC, v1.getX(), v1.getY());	
	}
	
	{
		
		int i = 0;
		for (cVector3 c_vectorRow : row)
		{
			c_vectorRow = cVector3::TransformCoord(c_vectorRow, matGridWVP);
			RowCoord[i] = (c_vectorRow = cVector3::TransformCoord(c_vectorRow, m_matViewport));
			i++;
		}
		i = 0;
		for (cVector3 c_vectorCol : col)
		{
			c_vectorCol = cVector3::TransformCoord(c_vectorCol, matGridWVP);
			ColCoord[i] = (c_vectorCol = cVector3::TransformCoord(c_vectorCol, m_matViewport));
			i++;
		}

		for (i = 0; i < 10 * 2; i += 2)
		{
			MoveToEx(m_MemDC, RowCoord[i].getX(), RowCoord[i].getY(), NULL);
			LineTo(m_MemDC, RowCoord[i + 1].getX(), RowCoord[i + 1].getY());
		}

		for (i = 0; i < 10 * 2; i += 2)
		{
			MoveToEx(m_MemDC, ColCoord[i].getX(), ColCoord[i].getY(), NULL);
			LineTo(m_MemDC, ColCoord[i + 1].getX(), ColCoord[i + 1].getY());
		}
	}
	
	BitBlt(hdc, 0, 0, rc.right, rc.bottom, m_MemDC, 0, 0, SRCCOPY);
}

void cMainGame::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{


	switch (message)
	{
	case WM_LBUTTONDOWN:
		m_bMouseClickCheck = true;
		m_iMouseX = LOWORD(lParam);
		m_iMouseY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		m_bMouseClickCheck = false;
		break;
	case WM_MOUSEMOVE:
		if (m_bMouseClickCheck)
		{
			if (m_iMouseX > LOWORD(lParam))
			{
				m_fCameraAngle++;
			}
			else
			{
				m_fCameraAngle--;
			}

			if (m_iMouseY > HIWORD(lParam))
			{
				m_fCameraDistance++;
			}
			else
			{
				m_fCameraDistance--;
			}

			m_iMouseX = LOWORD(lParam);
			m_iMouseY = HIWORD(lParam);
		}
		break;
	case WM_MOUSEWHEEL:
	{
		short mouse = GET_WHEEL_DELTA_WPARAM(wParam);

		if (mouse > 0)
		{
			m_fCameraZoom++;
		}
		else if (mouse < 0)
		{
			m_fCameraZoom--;
		}





	}
		break;
	case WM_KEYDOWN:
		{
		if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
		{
			m_fAngle += angle;
			m_FrontVec = cVector3::TransformNormal(m_FrontVec, cMatrix::RotatinY(10 * -1)).Normlize(); //좌표가아닌 점곱이아닌 벡터 곱에쓰는함수 .
			m_RectRotation = cMatrix::RotatinY(m_fAngle); //회전각도이기떄문에 누적값이지만.  
			//방향과 힘

			m_vLookAt = m_vLookAt + m_FrontVec;
		}
		if (GetAsyncKeyState(VK_LEFT) & 0x8000)
		{
			//float으로 값을 누적을받아 넘겨줘라 .
			m_fAngle -= angle;
			m_FrontVec = cVector3::TransformNormal(m_FrontVec, cMatrix::RotatinY(10)).Normlize(); //누계된 변수값이 들어가면된다 ? 
			m_RectRotation = cMatrix::RotatinY(m_fAngle);

			m_vLookAt = m_vLookAt + m_FrontVec;
		}
		if (GetAsyncKeyState(VK_UP) & 0x8000)
		{
			m_PositionVec = m_PositionVec + (m_FrontVec*speed);
			m_RectTranslate = cMatrix::Translation(m_PositionVec);
			//Translation 에넣어야할것은 변이값인데 내가 넣은값은 방향벡터, 속도가 곱해져있는값 

			m_vLookAt = m_vLookAt + m_PositionVec;
		}
		if (GetAsyncKeyState(VK_DOWN) & 0x8000)
		{
			//for (size_t i = 0; i < m_vecVecrtex.size(); i++)
			//{
			//	m_vecVecrtex[i] = m_vecVecrtex[i] - m_FrontVec;
			//}

			m_PositionVec = m_PositionVec - (m_FrontVec*speed);
			m_RectTranslate = cMatrix::Translation(m_PositionVec);

			m_vLookAt = m_vLookAt + m_PositionVec;
		}
	

		}
		break;
	default:
		break;
	}
}
