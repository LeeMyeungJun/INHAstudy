#pragma once
#include "iMap.h"
class cHeightMap :
	public iMap
{
public:
	cHeightMap();
	virtual ~cHeightMap();

private:
	LPD3DXMESH			m_pMesh; //���� �Ž��ΰ��ٰ� ����ž�
	vector<D3DXVECTOR3> m_vecVertex;
	D3DMATERIAL9		m_stMtl;//�Ž��α׸��ݾ�
	LPDIRECT3DTEXTURE9	m_pTexture;
	int					m_nTileN;

public:
	void Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel = 1);//��Ȥ���� 3����Ʈ�ϼ����־� �׷��� 1�̶�� �������
	virtual bool GetHeight(IN float x, OUT float& y, IN float z)override;
	virtual void Render() override;
	void Destroy();
};

