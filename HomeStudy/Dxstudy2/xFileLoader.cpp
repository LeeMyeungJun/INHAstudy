#include "stdafx.h"
#include "xFileLoader.h"


xFileLoader::xFileLoader()
		:Mesh(NULL)
{
}


xFileLoader::~xFileLoader()
{
}

void xFileLoader::Setup_Xfile(char* FileName)
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD numMtrls = 0;

	hr = D3DXLoadMeshFromXA(
		FileName,
		D3DXMESH_MANAGED,
		g_pD3DDvice,
		&adjBuffer,
		&mtrlBuffer,
		0, &numMtrls, &Mesh);

	if (FAILED(hr))
		return;

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
				D3DXCreateTextureFromFileA(
					g_pD3DDvice,
					mtrls[i].pTextureFilename,
					&tex); //내가바꾼거 A
				//x파일에 
				Textures.push_back(tex); //*붙이기
			}
			else
			{
				Textures.push_back(0);// ?
			}

		}//:<< for
	}//:<< if
}

void xFileLoader::Render_Xfile()
{

	D3DXMATRIXA16 matWorld ,matS,matR,matT;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixRotationY(&matR, 0); 
	D3DXMatrixTranslation(&matT, 0.0f, 0.0f, 0.0f);
	D3DXMatrixScaling(&matS, 3.0f, 3.0f, 3.0f);
	
	matWorld = matS * matR *matT;
	
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, true);
	for (int i = 0; i <Mtrls.size(); i++)
	{
		g_pD3DDvice->SetMaterial(&Mtrls[i]);
		g_pD3DDvice->SetTexture(0, Textures[i]);
		Mesh->DrawSubset(i);
	}

	//g_pD3DDvice->SetRenderState(D3DRS_LIGHTING, false);
}

