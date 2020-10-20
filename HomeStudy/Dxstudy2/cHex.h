#pragma once
class cHex
{

public:
	D3DXVECTOR3* m_vHexagon;
	D3DXVECTOR3* m_vBezier;
	vector<ST_PN_VERTEX> m_vecVertex;
	vector<ST_PN_VERTEX> m_vecBezierVertex;

	int m_iSize;


public:
	cHex();
	~cHex();

	void Render();
	void Setup();

	void Draw_Hexagon();
	void Draw_Bezier();




	
};

