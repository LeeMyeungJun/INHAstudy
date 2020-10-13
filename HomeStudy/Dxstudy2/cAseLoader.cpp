#include "stdafx.h"
#include "cAseLoader.h"


cAseLoader::cAseLoader()
{
}


cAseLoader::~cAseLoader()
{
}

void cAseLoader::Load(vector<cGroup*>& vecGroup, char* szFolder, char* szFile)
{
	vector<D3DXVECTOR3> vecV;// 버텍스 정보만 가지고있으면댄다 .
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));


	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;

	while (true)
	{
		if (feof(fp))break;

		char szTemp[1024];
		char szToken[1024];
		int iCnt;

		fgets(szTemp, 1024, fp);
		sscanf_s(szTemp, "%s", &szToken,1024);
		
		if (strcmp("*SCENE {", szToken))
		{
			/*while(true)
			{
				
			}*/
		}
		else if (strcmp("*MATERIAL_LIST {", szToken))
		{
			fgets(szTemp, 1024, fp);
			sscanf_s(szTemp, "\t%*s %d", iCnt);

			cout << iCnt;
			/*for(int i = 0 ; i < iCnt;i++)
			{
				
			}*/

			

		}
		else if (strcmp("GEOMOBJECT", szToken))
		{
		}

	}// <<: while

	fclose(fp);


}
