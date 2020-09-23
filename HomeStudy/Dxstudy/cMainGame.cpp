#include "stdafx.h"
#include "cMainGame.h"

cMainGame::cMainGame()
{
	
}


cMainGame::~cMainGame()
{
	
}

void cMainGame::Setup()
{
	IDirect3D9* _d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(D3DPRESENT_PARAMETERS));

	//d3dpp.BackBufferWidth = 800;
	//d3dpp.BackBufferHeight = 600;
	d3dpp.BackBufferFormat = D3DFMT_R8G8B8;
	d3dpp.BackBufferCount = 1;
	//d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	//d3dpp.MultiSampleQuality = 0;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = g_hWnd;
	d3dpp.Windowed = true;
	//d3dpp.EnableAutoDepthStencil = true;
	//d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	d3dpp.Flags = 0;
	//d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	m_pDevice = 0;
	HRESULT hr = _d3d9->CreateDevice
	(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&m_pDevice
	);

	if (FAILED(hr))
	{
		::MessageBox(0, TEXT("CreateDevice() - FAILED!"), 0, 0);
		return;
	}

		
}

void cMainGame::Update()
{
	
}

void cMainGame::Render()
{
	
	if (m_pDevice)
		m_pDevice ->Clear(0, 0, D3DCLEAR_TARGET ,
			D3DCOLOR_XRGB(0, 0,255), 1.0f, 0); //RGB
	m_pDevice ->Present(0, 0, 0,0); // 후연 버떠를 시연한다.
		return;
}
