#pragma once
class cRawLoader
{
public:
	cRawLoader();
	~cRawLoader();

	void LoadRaw(vector<ST_PNT_VERTEX>& vec, char* szFolder, char* szFile);
};

