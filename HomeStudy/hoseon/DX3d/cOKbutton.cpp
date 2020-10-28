#include "stdafx.h"
#include "cOKbutton.h"


cOKbutton::cOKbutton(char* path, char* FileName)
{
	string sFullPath(path);
	sFullPath += (string("/") + string(FileName));


	D3DXCreateTextureFromFileExA(
		g_pD3DDevice,
		sFullPath.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT,
		0,
		D3DFMT_UNKNOWN, //난모르니 너가알아서
		D3DPOOL_MANAGED,
		D3DX_FILTER_NONE,
		D3DX_DEFAULT,
		0,
		&m_stImageInfo,
		NULL,
		&m_pTextureUI
	);
}


cOKbutton::~cOKbutton()
{
}

void cOKbutton::Setup(D3DXVECTOR2 vecTranslation)
{
	D3DXMatrixTranslation(&matTranslation, vecTranslation.x, vecTranslation.y, 0);

}

