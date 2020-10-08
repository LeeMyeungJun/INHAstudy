#pragma once
class cHex
{

public:
	D3DXVECTOR3* m_vHexagon;
	D3DXVECTOR3* m_vBezier;
	vector<ST_PNT_VERTEX> m_vecVertex;


public:
	cHex();
	~cHex();

	void Render();
	void Setup();




	
};

