#pragma once
class cHexagon
{
private:
	vector<ST_PC_VERTEX> m_vHexagon;
	vector<ST_PC_VERTEX> m_vBezier;

	vector<ST_PC_VERTEX> m_vHexagonPath;
	vector<ST_PC_VERTEX> m_vBezierPath;
	
public:
	cHexagon();
	~cHexagon();

	void Setup();
	void Render();
};

