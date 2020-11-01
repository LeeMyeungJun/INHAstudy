#pragma once
class cXLoader
{
	ID3DXMesh* Mesh;
	vector<D3DMATERIAL9> Mtrls;
	vector<IDirect3DTexture9*> textures;
	
public:
	cXLoader();
	~cXLoader();

	bool Setup();
	bool Display(float timeDelta);
};

