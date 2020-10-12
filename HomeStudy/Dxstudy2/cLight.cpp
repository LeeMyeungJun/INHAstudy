#include "stdafx.h"
#include "cLight.h"
#include "cCubePC.h"

cLight::cLight()
	:fspotZ(-1)
	,fRange(10)
	,m_Spotcube(NULL)
	,m_Pointcube(NULL)
{
}


cLight::~cLight()
{
}

void cLight::Update()
{
	KeyInput();
	
	D3DXMATRIXA16 RotZ;
	D3DXVECTOR3 temp = stLight[1].Direction;
	D3DXMatrixRotationZ(&RotZ, 0.01f);
	
	D3DXVec3TransformNormal(&temp,&temp,&RotZ);
	
	stLight[1].Direction = temp;
	g_pD3DDvice->SetLight(1, &stLight[1]);
}


void cLight::Setup()
{
	Set_DirectionLight();
	Set_PointLight();
	Set_SpotLight();
	
}

void cLight::Render()
{
	m_Pointcube->Render();
	m_Spotcube->Render();
}

void cLight::Set_PointLight()
{
	ZeroMemory(&stLight[0], sizeof(D3DLIGHT9));
	stLight[0].Type = D3DLIGHT_POINT;
	stLight[0].Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight[0].Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight[0].Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	stLight[0].Attenuation0 = 0.0f;
	stLight[0].Attenuation1 = 0.0f;
	stLight[0].Attenuation2 = 0.0625f;
	stLight[0].Range = fRange;
	stLight[0].Position = D3DXVECTOR3(0, 5, 0);
	m_Pointcube = new cCubePC;
	m_Pointcube->Setup(0, 5, 0);
	D3DXVECTOR3 vDir(0, 0, 0);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight[0].Direction = vDir;
	g_pD3DDvice->SetLight(0, &stLight[0]);
	g_pD3DDvice->LightEnable(0, true);
}

void cLight::Reset_PointLight()
{
	stLight[0].Range = fRange;
	g_pD3DDvice->SetLight(0, &stLight[0]);
	g_pD3DDvice->LightEnable(0, true);
}

void cLight::Set_DirectionLight()
{
	ZeroMemory(&stLight[1], sizeof(D3DLIGHT9));
	stLight[1].Type = D3DLIGHT_DIRECTIONAL;
	stLight[1].Ambient = D3DXCOLOR(0.8f, 0, 0, 1.0f);
	stLight[1].Diffuse = D3DXCOLOR(0.8f, 0, 0, 1.0f);
	stLight[1].Specular = D3DXCOLOR(0.8f, 0, 0, 1.0f);

	D3DXVECTOR3 vDir(0, -1.0f, 0);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight[1].Direction = vDir;
	g_pD3DDvice->SetLight(1, &stLight[1]);
	g_pD3DDvice->LightEnable(1, true);
}

void cLight::Set_SpotLight()
{
	ZeroMemory(&(stLight[2]), sizeof(D3DLIGHT9));
	stLight[2].Type = D3DLIGHT_SPOT;
	stLight[2].Ambient = D3DXCOLOR(0, 0, 0.8f, 1.0f);
	stLight[2].Diffuse = D3DXCOLOR(0, 0, 0.8f, 1.0f);
	stLight[2].Specular = D3DXCOLOR(0, 0, 0.8f, 1.0f);
	stLight[2].Range =15.0f;
	stLight[2].Position = D3DXVECTOR3(5,5,3);
	m_Spotcube = new cCubePC;
	m_Spotcube->Setup(5, 5, 3);
	
	stLight[2].Falloff = 1.0f;
	stLight[2].Attenuation0 = 0;
	stLight[2].Attenuation1 = 0.2f;
	stLight[2].Attenuation2 = 0;

	
	
	D3DXVECTOR3 vDir =  D3DXVECTOR3(0, 0, fspotZ) - D3DXVECTOR3(5, 5, 3);

	D3DXVec3Normalize(&vDir, &vDir);
	stLight[2].Direction = vDir;
	stLight[2].Theta = D3DX_PI / 4.0f; //내부각
	stLight[2].Phi = D3DX_PI / 0.5f; //외부각

	g_pD3DDvice->SetLight(2, &stLight[2]);
	g_pD3DDvice->LightEnable(2, true);
	
}

void cLight::Reset_SpotLight()
{
	D3DXVECTOR3 vDir = D3DXVECTOR3(0, 0, fspotZ) - D3DXVECTOR3(0, 5, 0);

	D3DXVec3Normalize(&vDir, &vDir);
	stLight[2].Direction = vDir;
	g_pD3DDvice->SetLight(2, &stLight[2]);
}


void cLight::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

}
void cLight::KeyInput()
{
	if (GetKeyState('Z') & 0X8000)
	{
		fspotZ +=1;
		Reset_SpotLight();
	}
	else if (GetKeyState('X') & 0X8000)
	{
		fspotZ -= 1;
		Reset_SpotLight();
	}

	if (GetKeyState('Q') & 0X8000)
	{
		fRange += 0.1f;
		Reset_PointLight();
	}
	else if (GetKeyState('E') & 0X8000)
	{
		fRange -= 0.1f;
		Reset_PointLight();
	}
}
