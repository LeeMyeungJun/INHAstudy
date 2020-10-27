#include "stdafx.h"
#include "cLight.h"


cLight::cLight()
{
	m_vDir = D3DXVECTOR3(0, 0, 0);
	m_vSpotDir = D3DXVECTOR3(0, 0, 0);
}

cLight::~cLight()
{
}

void cLight::Init()
{
	ZeroMemory(&m_stLight[0], sizeof(D3DLIGHT9));
	m_stLight[0].Type = D3DLIGHT_DIRECTIONAL;
	m_stLight[0].Ambient = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	m_stLight[0].Diffuse = D3DXCOLOR(1.0f, 0.6f, 0.6f, 1.0f);
	m_stLight[0].Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	m_vDir = D3DXVECTOR3(1.0f, -1.0f, 1.0f);
	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_stLight[0].Direction = m_vDir;
	g_pD3DDevice->SetLight(0, &m_stLight[0]);
	g_pD3DDevice->LightEnable(0, true);

	ZeroMemory(&m_stLight[1], sizeof(D3DLIGHT9));
	m_stLight[1].Type = D3DLIGHT_POINT;
	m_stLight[1].Ambient = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_stLight[1].Diffuse = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	m_stLight[1].Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stLight[1].Position = D3DXVECTOR3(-5.0f, 1.5f, 0);
	m_stLight[1].Attenuation1 = 0.5f;
	m_stLight[1].Range = 2.0f;
	g_pD3DDevice->SetLight(1, &m_stLight[1]);
	g_pD3DDevice->LightEnable(1, true);

	ZeroMemory(&m_stLight[2], sizeof(D3DLIGHT9));
	m_stLight[2].Type = D3DLIGHT_SPOT;
	m_stLight[2].Ambient = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_stLight[2].Diffuse = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
	m_stLight[2].Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

	m_vSpotDir = D3DXVECTOR3(0, -1.0f, 0);
	D3DXVec3Normalize(&m_vSpotDir, &m_vSpotDir);
	m_stLight[2].Direction = m_vSpotDir;
	
	m_stLight[2].Falloff = 1.0f;
	m_stLight[2].Position = D3DXVECTOR3(8.0f, 3.0f, 0);
	m_stLight[2].Attenuation1 = 0.3f;
	m_stLight[2].Range = 999.0f;
	m_stLight[2].Theta = D3DX_PI / 4.0f;
	m_stLight[2].Phi = D3DX_PI / 2.0f;
	g_pD3DDevice->SetLight(2, &m_stLight[2]);
	g_pD3DDevice->LightEnable(2, true);
}

void cLight::Update()
{
	/*D3DXMATRIXA16	matR, matT;
	D3DXMatrixRotationZ(&matR, m_fRotZ);

	m_vDirection = D3DXVECTOR3(0, 0, 1);
	D3DXVec3TransformNormal(&m_vDirection, &m_vDirection, &matR);
	D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

	m_matWorld = matR * matT;

	m_fRotZ -= 0.1f;*/
	D3DXMATRIXA16 matRZ;
	D3DXMatrixRotationZ(&matRZ, 0.05f);
	D3DXVec3TransformNormal(&m_vDir, &m_vDir, &matRZ);
	D3DXVec3Normalize(&m_vDir, &m_vDir);
	m_stLight[0].Direction = m_vDir;
	g_pD3DDevice->SetLight(0, &m_stLight[0]);

	if (GetKeyState('Q') & 0x8000)
	{
		m_stLight[1].Range += 0.2f;
		g_pD3DDevice->SetLight(1, &m_stLight[1]);
	}
	if (GetKeyState('E') & 0x8000)
	{
		m_stLight[1].Range -= 0.2f;
		g_pD3DDevice->SetLight(1, &m_stLight[1]);
	}

	if (GetKeyState('I') & 0x8000)
	{
		D3DXMATRIXA16 matRX;
		D3DXMatrixIdentity(&matRX);
		D3DXMatrixRotationX(&matRX, -0.03f);
		D3DXVec3TransformNormal(&m_vSpotDir, &m_vSpotDir, &matRX);
		D3DXVec3Normalize(&m_vSpotDir, &m_vSpotDir);
		m_stLight[2].Direction = m_vSpotDir;
		g_pD3DDevice->SetLight(2, &m_stLight[2]);
	}
	if (GetKeyState('K') & 0x8000)
	{
		D3DXMATRIXA16 matRX;
		D3DXMatrixIdentity(&matRX);
		D3DXMatrixRotationX(&matRX, 0.03f);
		D3DXVec3TransformNormal(&m_vSpotDir, &m_vSpotDir, &matRX);
		D3DXVec3Normalize(&m_vSpotDir, &m_vSpotDir);
		m_stLight[2].Direction = m_vSpotDir;
		g_pD3DDevice->SetLight(2, &m_stLight[2]);
	}
	if (GetKeyState('J') & 0x8000)
	{
		D3DXMATRIXA16 matRZ;
		D3DXMatrixIdentity(&matRZ);
		D3DXMatrixRotationZ(&matRZ, -0.03f);
		D3DXVec3TransformNormal(&m_vSpotDir, &m_vSpotDir, &matRZ);
		D3DXVec3Normalize(&m_vSpotDir, &m_vSpotDir);
		m_stLight[2].Direction = m_vSpotDir;
		g_pD3DDevice->SetLight(2, &m_stLight[2]);
	}
	if (GetKeyState('L') & 0x8000)
	{
		D3DXMATRIXA16 matRZ;
		D3DXMatrixRotationZ(&matRZ, 0.03f);
		D3DXVec3TransformNormal(&m_vSpotDir, &m_vSpotDir, &matRZ);
		D3DXVec3Normalize(&m_vSpotDir, &m_vSpotDir);
		m_stLight[2].Direction = m_vSpotDir;
		g_pD3DDevice->SetLight(2, &m_stLight[2]);
	}
}
