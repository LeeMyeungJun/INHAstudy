#include "stdafx.h"
#include "cXLoader.h"


cXLoader::cXLoader()
	:Mesh(NULL)
{
}

cXLoader::~cXLoader()
{
}

bool cXLoader::Setup()
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromX(
		L"zealot.X",
		D3DXMESH_MANAGED,
		g_pD3DDevice,
		&adjBuffer,
		&mtrlBuffer,
		0, &numMtrls, &Mesh);

	if (FAILED(hr))
		return false;

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

		for (int i = 0; i < numMtrls; i++)
		{
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			Mtrls.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(g_pD3DDevice, mtrls[i].pTextureFilename, &tex);

				textures.push_back(tex);
			}
			else
				textures.push_back(0);
		}
	}
	return true;
}

bool cXLoader::Display(float timeDelta)
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	if (g_pD3DDevice)
	{
		static float y = 0.0f;
		D3DXMATRIXA16 yRot;
		D3DXMatrixRotationY(&yRot, y);
		y += timeDelta;

		if (y >= 6.28f)
			y = 0.0f;

		D3DXMATRIXA16 world = yRot;

		g_pD3DDevice->SetTransform(D3DTS_WORLD, &world);

		//g_pD3DDevice->Clear(0, 0, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0xffffffff, 1.0f, 0);

		for(int i = 0; i < Mtrls.size(); i++)
		{
			g_pD3DDevice->SetMaterial(&Mtrls[i]);
			g_pD3DDevice->SetTexture(0, textures[i]);
			Mesh->DrawSubset(i);
		}
	}
	return true;
}
