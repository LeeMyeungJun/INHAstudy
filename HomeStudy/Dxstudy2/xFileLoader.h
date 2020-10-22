#pragma once
class xFileLoader
{
public:
	xFileLoader();
	~xFileLoader();

public:
	void Setup_Xfile(char* FileName);
	void Render_Xfile();
	
private:
	ID3DXMesh* Mesh;
	vector<D3DMATERIAL9> Mtrls;
	vector<IDirect3DTexture9*> Textures;

	
};

