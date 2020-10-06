#include "stdafx.h"
#include "cLight.h"


cLight::cLight()
	:fRange(4)
{
}


cLight::~cLight()
{
}

void cLight::Update()
{
	if (GetKeyState('Q') & 0X8000)
	{
		LightUpdate_PointLight(0.1f);
	}
	else if (GetKeyState('E') & 0X8000)
	{
		LightUpdate_PointLight(-0.1f);
	}

	if (GetKeyState('Z') & 0X8000)
	{
		LightUpdate_SpotLight(0.1f);
	}
	else if (GetKeyState('X') & 0X8000)
	{
		LightUpdate_SpotLight(-0.1f);
	}

	LightUpdate_DirectionLight();
}

void cLight::Setup()
{
	Set_DirectionLight();
	Set_PointLight();
	Set_SpotLight();

}

void cLight::Render()
{
}

void cLight::Set_PointLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_POINT;
	stLight.Ambient  = D3DXCOLOR(0.8f, 0, 0, 1.0f);
	stLight.Diffuse  = D3DXCOLOR(0.8f, 0, 0, 1.0f);
	stLight.Specular = D3DXCOLOR(0.8f, 0, 0, 1.0f);
	stLight.Attenuation1 = 0.5f;
	stLight.Position = D3DXVECTOR3(3, 3, 3);
	stLight.Range = 4;

	D3DXVECTOR3 vDir(0, -1.0f, 0);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	g_pD3DDvice->SetLight(0, &stLight);
	g_pD3DDvice->LightEnable(0, true);
}

void cLight::Set_SpotLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_SPOT;
	stLight.Ambient =  D3DXCOLOR(0, 0.8f, 0, 1.0f);
	stLight.Diffuse =  D3DXCOLOR(0, 0.8f, 0, 1.0f);
	stLight.Specular = D3DXCOLOR(0, 0.8f, 0, 1.0f);
	stLight.Attenuation1 = 0.5f;
	stLight.Position = D3DXVECTOR3(-3, 3, -3);
	stLight.Range = 4;
	stLight.Falloff = 1.0f;
	stLight.Theta = D3DX_PI / 4;
	stLight.Phi = D3DX_PI / 2;

	D3DXVECTOR3 vDir(0, -1.0f, 0);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	g_pD3DDvice->SetLight(1, &stLight);
	g_pD3DDvice->LightEnable(1, true);
}

void cLight::Set_DirectionLight()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Type = D3DLIGHT_DIRECTIONAL;
	stLight.Ambient  = D3DXCOLOR(0, 0, 0.7f, 1.0f);
	stLight.Diffuse  = D3DXCOLOR(0, 0, 0.7f, 1.0f);
	stLight.Specular = D3DXCOLOR(0, 0, 0.7f, 1.0f);

	D3DXVECTOR3 vDir(0, -1.0f, 0);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;

	g_pD3DDvice->SetLight(2, &stLight);
	g_pD3DDvice->LightEnable(2, true);
}

void cLight::LightUpdate_PointLight(float x)
{
	D3DLIGHT9 stLight;
	g_pD3DDvice->GetLight(0, &stLight);
	stLight.Range += x;
	g_pD3DDvice->SetLight(0, &stLight);

}

void cLight::LightUpdate_SpotLight(float x)
{
	D3DLIGHT9 stLight;
	g_pD3DDvice->GetLight(1, &stLight);
	stLight.Position.x += x;
	g_pD3DDvice->SetLight(1, &stLight);
}

void cLight::LightUpdate_DirectionLight()
{
	D3DLIGHT9 stLight;
	g_pD3DDvice->GetLight(2, &stLight);	
	D3DXMATRIXA16 matR;
	D3DXVECTOR3 temp = stLight.Direction;

	D3DXMatrixRotationZ(&matR, 0.1f);
	D3DXVec3TransformNormal(&temp, &temp, &matR);
	stLight.Direction = temp;

	g_pD3DDvice->SetLight(2, &stLight);
}
