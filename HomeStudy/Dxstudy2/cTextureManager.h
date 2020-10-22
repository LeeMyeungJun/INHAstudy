#pragma once

class cTextureManager//ΩÃ±€≈Ê
{
public:
	//cTextureManager();
	//~cTextureManager();

private:
	Singleton(cTextureManager);
	map<string, LPDIRECT3DTEXTURE9> m_mapTexture;
public:
	LPDIRECT3DTEXTURE9 GetTexture(char * szFullPath);
	LPDIRECT3DTEXTURE9 GetTexture(string& sFullPath);
	void Destroy();
	
};

#define g_pTextureManager cTextureManager::GetInstance()

