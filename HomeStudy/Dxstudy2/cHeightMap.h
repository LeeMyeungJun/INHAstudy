#pragma once
#include "iMap.h"
class cHeightMap :
	public iMap
{
public:
	cHeightMap();
	virtual ~cHeightMap();

private:
	LPD3DXMESH			m_pMesh; //맵을 매쉬로갓다가 만들거야
	vector<D3DXVECTOR3> m_vecVertex;
	D3DMATERIAL9		m_stMtl;//매쉬로그리잖아
	LPDIRECT3DTEXTURE9	m_pTexture;
	int					m_nTileN;

public:
	void Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel = 1);//간혹가서 3바이트일수도있어 그래서 1이라고 명시해줘
	virtual bool GetHeight(IN float x, OUT float& y, IN float z)override;
	virtual void Render() override;
	void Destroy();
};

