#pragma once
class cPyramid;

class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	vector<ST_PC_VERTEX>			m_vecVertex;
	vector<ST_PNT_VERTEX>			m_vecVertexPlane;


	vector<ST_Tile>					m_vecTiles;
	
	vector<cPyramid*>				m_vecPyramid;
	D3DMATERIAL9					m_stMt1;
	D3DMATERIAL9					m_stMt2;

	LPDIRECT3DTEXTURE9				m_PlaneTexture;

public:
	void Setup(int nNumHalfTile = 15, float fInterval = 1.0f);
	void Render();
};

