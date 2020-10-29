#include "stdafx.h"



cUITextureManager::cUITextureManager()
{
}


cUITextureManager::~cUITextureManager()
{
}

LPDIRECT3DTEXTURE9 cUITextureManager::GetTexture(char* szFullPath)
{
	if (m_mapTexture.find(szFullPath) == m_mapTexture.end())
	{
		D3DXCreateTextureFromFileExA(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN, //난모르니 너가알아서
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapTextureInFo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]
		);
	}
	return m_mapTexture[szFullPath];
}

LPDIRECT3DTEXTURE9 cUITextureManager::GetTexture(std::string& szFullPath)
{
	return GetTexture((char*)szFullPath.c_str());
}

D3DXIMAGE_INFO cUITextureManager::GetTextureInfo(char* szFullPath)
{
	if (m_mapTextureInFo.find(szFullPath) == m_mapTextureInFo.end())
	{
		D3DXCreateTextureFromFileExA(
			g_pD3DDevice,
			szFullPath,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN, //난모르니 너가알아서
			D3DPOOL_MANAGED,
			D3DX_FILTER_NONE,
			D3DX_DEFAULT,
			0,
			&m_mapTextureInFo[szFullPath],
			NULL,
			&m_mapTexture[szFullPath]
		);
	}
	return m_mapTextureInFo[szFullPath];
}

D3DXIMAGE_INFO cUITextureManager::GetTextureInfo(std::string& szFullpath)
{
	return GetTextureInfo((char*)szFullpath.c_str());
}

D3DXVECTOR2 cUITextureManager::GetTextureSize(char* szFullPath)
{
	D3DXVECTOR2 vTemp(0,0);
	if (m_mapTextureInFo.find(szFullPath) == m_mapTextureInFo.end())
	{
		return vTemp;
	}
	vTemp.x = m_mapTextureInFo[szFullPath].Width;
	vTemp.y = m_mapTextureInFo[szFullPath].Height;
	


	return vTemp;
}

D3DXVECTOR2 cUITextureManager::GetTextureSize(std::string& szFullpath)
{
	return GetTextureSize((char*)szFullpath.c_str());
}

void cUITextureManager::Destroy()
{
	for each(auto it in m_mapTexture)
	{
		SafeRelease(it.second);
	}
	m_mapTexture.clear();
}
