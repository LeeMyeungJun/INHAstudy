#pragma once
class cPyramid;

class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	vector<ST_PN_VERTEX>	m_vecVertex;
	vector<cPyramid*>		m_vecPyramid;

public:
	void Setup(int nNumHalfTile = 200, float fInterval = 0.05f);
	void Render();
};

