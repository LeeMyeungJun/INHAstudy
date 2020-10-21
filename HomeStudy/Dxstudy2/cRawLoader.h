#pragma once
class cRawLoader
{
public:
	cRawLoader();
	~cRawLoader();
private:
	FILE* m_fp;
public:
	void RawLoader(IN char *FileName,IN char *Texture, OUT vector<ST_PNT_VERTEX>& rawVector);
	void CreateIndex(IN vector<ST_PNT_VERTEX> temp, OUT vector<ST_PNT_VERTEX>& rawVector);

};

