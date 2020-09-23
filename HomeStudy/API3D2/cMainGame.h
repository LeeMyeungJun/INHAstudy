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
	vector<DWORD>		 m_vecIndex;//������ ���ڸ� ���ϰŴ� .
	
	
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
	vector<cVector3>m_vecLineVertex; //�����׸������� Vertex
	cVector3		m_vPosition; //�ڽ���ġ
	POINT			m_ptPrevMouse; //���콺 �̵���üũ�ϸ鼭 ȸ���� üũ
	bool			m_isButtonDown;//���콺�� ���ǳ��ȴ��ȳ�
	float			m_fCameraDistance; //ī�޶� �Ÿ�

	cVector3		m_vCamRotAngle; //ī�޶� ȸ��
	cVector3		m_vAxisXTexPosition; //ī�޶� X�� Z�࿡���� ������
	cVector3		m_vAxisZTexPosition;

	float			m_fBoxRotY; //�ڽ���ü ȸ����
	cVector3		m_vBoxDirection; //�ڽ����ٶ󺸰��ִ� ����
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
	void Setup(); //���������͸� �����ٰ� �ʱ�ȭ��ų�� ���Լ��� ȣ��
	void Update(); //����
	void Render(HDC hdc); //�׷��ֱ�
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

