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

	vector<cVector3> row;
	vector<cVector3> col;
	vector<cVector3> RowCoord;
	vector<cVector3> ColCoord;
	
	
	
	
	cMatrix			m_matView;
	cMatrix			m_matProj;
	cMatrix			m_matViewport;

	cMatrix			m_matGridWorld;
	cMatrix			m_matRectWorld;

	cMatrix			m_GridScale;
	cMatrix			m_GridRotation;
	cMatrix			m_GridTranslate;

	cMatrix			m_RectRotation;
	cMatrix			m_RectScale;
	cMatrix			m_RectTranslate;

	cVector3		m_PositionVec;

	cVector3		m_vEye;
	cVector3		m_vLookAt;
	cVector3		m_vUp;

	cVector3		m_FrontVec;

	float			m_fAngle;

	float			m_fCameraZoom;
	float			m_fCameraAngle;
	float			m_fCameraDistance;

	bool			m_bMouseClickCheck;
	int m_iMouseX, m_iMouseY;


public:
	void Setup(); //각종데이터를 가져다가 초기화시킬때 이함수를 호출
	void Update(); //갱신
	void Render(HDC hdc); //그려주기
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

