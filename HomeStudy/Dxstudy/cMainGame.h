#pragma once
#include "stdafx.h"

class cMainGame
{
public:
	cMainGame();
	~cMainGame();

private:
	LPDIRECT3D9		m_pD3D;//얘 정보를 설정해야 인터페이스 
	LPDIRECT3DDEVICE9 m_pDevice;//이친구를 설정할수있음 Divece

public:
	void Setup();
	void Update();
	void Render();
};

