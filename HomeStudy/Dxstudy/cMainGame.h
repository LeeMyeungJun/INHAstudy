#pragma once
#include "stdafx.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	LPDIRECT3D9		m_pD3D;//�� ������ �����ؾ� �������̽� 
	LPDIRECT3DDEVICE9 m_pDevice;//��ģ���� �����Ҽ����� Divece

public:
	void Setup();
	void Update();
	void Render();
};

