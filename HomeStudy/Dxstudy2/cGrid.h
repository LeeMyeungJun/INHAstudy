#pragma once
class cPyramid;

class cGrid
{
public:
	cGrid();
	~cGrid();

private:
	vector<ST_PC_VERTEX>	m_vecVertex; // gird
	vector<ST_PC_VERTEX>	m_vecVertex2; //line

	
	vector<cPyramid*>		m_vecPyramid;

public:
	void Setup(int nNumHalfTile = 5, float fInterval = 1.0f);
	void Render();
	void Render_Line();


	vector<ST_PC_VERTEX> getGridVertex()
	{
		return m_vecVertex;
	}

	void setGridVertex(vector<ST_PC_VERTEX> setTemp)
	{
		m_vecVertex = setTemp;
	}
};

