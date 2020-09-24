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
	vector<ST_PC_VERTEX>	m_vecRectangleIndex;//������ ���ڸ� ���ϰŴ� .

	vector<ST_PC_VERTEX>	m_vecPyramidVertex;
	vector<ST_PC_VERTEX>	m_vecPyramidIndex;

	
	D3DXVECTOR3		m_vPosition; //�ڽ���ġ
	POINT			m_ptPrevMouse; //���콺 �̵���üũ�ϸ鼭 ȸ���� üũ
	bool			m_isButtonDown;//���콺�� ���ǳ��ȴ��ȳ�
	float			m_fCameraDistance; //ī�޶� �Ÿ�

	D3DXVECTOR3		m_vCamRotAngle; //ī�޶� ȸ��

	float			m_fBoxRotY; //�ڽ���ü ȸ����
	D3DXVECTOR3		m_vBoxDirection; //�ڽ����ٶ󺸰��ִ� ����

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

