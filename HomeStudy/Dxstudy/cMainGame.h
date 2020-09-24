#pragma once
#include "stdafx.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	vector<ST_PC_VERTEX>	m_vecLineVertex;
	vector<ST_PC_VERTEX>	m_vecTriangleVertex;
	
	vector<ST_PC_VERTEX>	m_vecRectangleVertex;
	vector<ST_PC_VERTEX>	m_vecRectangleIndex;//정점에 숫자를 맥일거다 .

	vector<ST_PC_VERTEX>	m_vecPyramidVertex;
	vector<ST_PC_VERTEX>	m_vecPyramidIndex;

	
	D3DXVECTOR3		m_vPosition; //박스위치
	POINT			m_ptPrevMouse; //마우스 이동량체크하면서 회전을 체크
	bool			m_isButtonDown;//마우스가 눌렷나안눌렸나
	float			m_fCameraDistance; //카메라 거리

	D3DXVECTOR3		m_vCamRotAngle; //카메라 회전

	float			m_fBoxRotY; //박스자체 회전량
	D3DXVECTOR3		m_vBoxDirection; //박스가바라보고있는 방향

	D3DXVECTOR3		vEye;
	D3DXVECTOR3		vLookAt;
	D3DXVECTOR3		vUp;
	
	D3DXMATRIXA16	m_matTranslate;
	D3DXMATRIXA16	m_matR;
	
	
public:
	void Setup();
	void Update();
	void Render();
	void WndProc(UINT message, WPARAM wParam, LPARAM lParam);

	
	void Setup_Line();
	void Draw_Line();

	void Setup_Triangle();
	void Draw_Triangle();

	void Setup_Grid();
	void Draw_Grid();

	void Setup_Rectangle();
	void Draw_Rectangle();

	void Setup_Pyramid();
	void Draw_Pyramid();


	void Update_Move();
	void Update_Rotation();

};

