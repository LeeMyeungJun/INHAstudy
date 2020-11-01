#pragma once
class cBox;

class cObjParser
{
private:
	char m_mtlPath[16];
	char m_texPath[16];

public:
	cObjParser();
	~cObjParser();

	void ReadFile(char* _filename, cBox *_box);
};