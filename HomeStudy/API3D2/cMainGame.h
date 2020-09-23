#include "cMatrix.h"
#include "cVector3.h"
#pragma once


class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	HDC m_MemDC;
	HBITMAP m_hOldBitmap, m_hBitmap;

	vector<cVector3>	m_vecVecrtex;
	vector<DWORD>		 m_vecIndex;//정점에 숫자를 맥일거다 .
	
	
	cMatrix			m_matView;
	cMatrix			m_matProj;
	cMatrix			m_matViewport;
	cMatrix			m_matWorld;

	cMatrix			m_Rotation;
	cMatrix			m_Scale;
	cMatrix			m_Translate;
	
	cVector3		m_vEye;
	cVector3		m_vLookAt;
	cVector3		m_vUp;


	// >> :
	vector<cVector3>m_vecLineVertex; //선을그리기위한 Vertex
	cVector3		m_vPosition; //박스위치
	POINT			m_ptPrevMouse; //마우스 이동량체크하면서 회전을 체크
	bool			m_isButtonDown;//마우스가 눌렷나안눌렸나
	float			m_fCameraDistance; //카메라 거리

	cVector3		m_vCamRotAngle; //카메라 회전
	cVector3		m_vAxisXTexPosition; //카메라 X출 Z축에대한 포지션
	cVector3		m_vAxisZTexPosition;

	float			m_fBoxRotY; //박스자체 회전량
	cVector3		m_vBoxDirection; //박스가바라보고있는 방향
	// << :

	


	
	// >> :
	void SetGrid();
	void DrawGrid();
	void Update_Move();
	void Update_Rotation();
	bool IsBackFace(cVector3& v1, cVector3& v2, cVector3& v3);
	// << :
	

	//


	


public:
	void Setup(); //각종데이터를 가져다가 초기화시킬때 이함수를 호출
	void Update(); //갱신
	void Render(HDC hdc); //그려주기
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

