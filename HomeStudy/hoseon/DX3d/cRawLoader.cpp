#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
{
}


cRawLoader::~cRawLoader()
{
}

void cRawLoader::LoadRaw(vector<ST_PNT_VERTEX>& vec, char* szFolder, char* szFile)
{
	int tmp = 0;
	int px = 0, pz = 0;
	ST_PNT_VERTEX v;
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "rb");

	while (true)
	{
		if (feof(fp)) 
			break;

		tmp = getc(fp);
		v.p.x = px;
		v.p.y = (float)tmp / 10;
		v.p.z = pz;
		v.n = D3DXVECTOR3(0, 1, 0);

		vec.push_back(v);

		/*px += 1;
		if(px % 256 == 0 && px != 0)
		{
			px = 0;
			pz += 1;
		}*/
	}
	float range = 1.0f;
	for (int i = 0; i < 257; i++)
	{
		for (int j = 0; j < 257; j++)
		{
			vec[i * 257 + j].p.x = (float)j*range;
			vec[i * 257 + j].p.z = (float)i*range;
		}
	}

	fclose(fp);
}
