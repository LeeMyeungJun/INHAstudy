#include "stdafx.h"
#include "cObjLoader.h"
<<<<<<< HEAD
#include "cMtlTex.h"
#include "cGroup.h"

=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b

cObjLoader::cObjLoader()
{
}


cObjLoader::~cObjLoader()
{
}
<<<<<<< HEAD

void cObjLoader::Load(vector<cGroup*>& vecGroup, char* szFolder, char* szFile)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;

	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	while (true)
	{
		if (feof(fp))break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if(szTemp[0] == '#') //주석이자나
		{
			continue;
		}
		else if(szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024); //*붙은이유  *붙은 앞에껀 버리고 뒤에꺼만
			//mtllib ./box.mtl        ./box.mtl  이것만 가지고있겟다는거임
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if(szTemp[0] == 'g')
		{
			if(!vecVertex.empty())//버텍스정보가 0이아니면  생성하고 
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetmtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if (szTemp[0] == 'v')
		{
			if(szTemp[1] == ' ')//버텍스정보잖아
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z );
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if(szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if(szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if(szTemp[0] =='u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if(szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]
			);

			for(int i = 0 ; i < 3; i++)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}//<<:for
		}// : if
		
	}// <<: while

	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SafeRelease(it.second); // 두번쨰요소
	}
	m_mapMtlTex.clear();
}// <<: Load()

void cObjLoader::LoadMtlLib(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE *fp;
	fopen_s(&fp, sFullPath.c_str(), "r");
	string sMtlName;
	int nCnt = 0;
	while (true)
	{
		if (feof(fp)) break;


		char szTemp[1024];
		fgets(szTemp, 1024, fp);
		if(szTemp[0] == '#')
		{
			continue;
		}
		else if(szTemp[0] == 'n')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
			if(m_mapMtlTex.find(sMtlName) == m_mapMtlTex.end())
			{
				m_mapMtlTex[sMtlName] = new cMtlTex;
				//Mesh 여기 추가
				m_mapMtlTex[sMtlName]->SetAttrID(nCnt++);
				//m_mapMtlTex[sMtlName]->SetAttrID(m_mapMtlTex.size()-1);

			}
		}
		else if(szTemp[0] =='K')
		{
			if(szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;


			}
			else if(szTemp[1] =='d')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;

			}
			else if(szTemp[1] == 's')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if(szTemp[0] == 'd')
		{
			float d;
			sscanf_s(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		else if(szTemp[0] =='m')
		{
			char szTextFile[1024];
			sscanf_s(szTemp, "%*s %s", szTextFile, 1024);
			sFullPath = string(szFolder);
			sFullPath += (string("/") + string(szTextFile));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
		} // <: if
	}// <<:while
	fclose(fp);
}// << :LoadMtlLib()
void cObjLoader::LoadSurface(vector<D3DXVECTOR3>& vecSurface, char* szFolder, char* szFile, D3DXMATRIXA16* pmat)
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
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#') //주석이자나
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
		
		}
		else if (szTemp[0] == 'g')
		{
			
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')//버텍스정보잖아
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]

			);

			for (int i = 0; i < 3; i++)
			{
				vecSurface.push_back(vecV[nIndex[i] - 1]);
			}//<<:for
		}// : if

	}// <<: while

	fclose(fp);

	if(pmat)// 여기에들어왔다는건 스케일링이 생겼다든지 이동이생겻다든지
	{
		for(size_t i = 0 ; i < vecSurface.size(); i++)
		{
			D3DXVec3TransformCoord(&vecSurface[i], &vecSurface[i], pmat);
		}
	}
	
}

LPD3DXMESH cObjLoader::LoadMesh(vector<cMtlTex*>& vecMtlTex, char* szFolder, char* szFile)
{
	vector<DWORD>		vecAttrBuf;//속성에대한 벡터
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;
	vector<ST_PNT_VERTEX> vecVertex;

	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	while (true)
	{
		if (feof(fp))break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#') //주석이자나
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024); //*붙은이유  *붙은 앞에껀 버리고 뒤에꺼만
														 //mtllib ./box.mtl        ./box.mtl  이것만 가지고있겟다는거임
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
			//if (!vecVertex.empty())//버텍스정보가 0이아니면  생성하고 
			//{
			//	cGroup* pGroup = new cGroup;
			//	pGroup->SetVertex(vecVertex);
			//	pGroup->SetmtlTex(m_mapMtlTex[sMtlName]);
			//	vecGroup.push_back(pGroup);
			//	vecVertex.clear();
			//}
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')//버텍스정보잖아
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				float u, v;
				sscanf_s(szTemp, "%*s %f %f %*f", &u, &v);
				vecVT.push_back(D3DXVECTOR2(u, v));
			}
			else if (szTemp[1] == 'n')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecVN.push_back(D3DXVECTOR3(x, y, z));
			}
		}
		else if (szTemp[0] == 'u')
		{
			char szMtlName[1024];
			sscanf_s(szTemp, "%*s %s", szMtlName, 1024);
			sMtlName = string(szMtlName);
		}
		else if (szTemp[0] == 'f') //텍스쳐 노말 이런애들 불러오는애들이잖아  여기서하면된다구 
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]
			);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}//<<:for
			//
			//cMtlTex.h 추가하고 밑에 푸쉬백 Synthesize(int, m_nAttrID, AttrID);
			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID()); //아이디값을얻어와서 mtl을 넣어주는거야  LoadMtl 좀 수정하구옵시다 .
		}// : if

	}// <<: while

	fclose(fp);

	//=========================================================
	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttrID()] = it.second;
	}
	LPD3DXMESH pMesh = NULL;
	D3DXCreateMeshFVF(vecAttrBuf.size(), vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDvice, &pMesh);


	//버텍스버퍼 생성
	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));

	pMesh->UnlockVertexBuffer();


	 //인덱스버퍼 생성
	WORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)& pI);
	for(int i = 0 ; i < vecVertex.size(); i++)
	{
		pI[i] = i;
		
	}
	pMesh->UnlockIndexBuffer();
	

	//속성버퍼 생성
	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();
	//여기까지만해도 매쉬그리는데 문제가없어 하지만 최적화를 해줘야겠지? 그부분이 밑에
	vector<DWORD> vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]); //0.0000000000001 정도의 오차범위를 하겠다 첫번쨰인자설명
	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0); //D3DXMESHOPT_ATTRSORT 최적화를 시작 D3DXMESHOPT_COMPACT쓸데없는걸 지우기 

	m_mapMtlTex.clear();

	return pMesh;
}
=======
>>>>>>> 41302b6992cdd6e25a5b860ae2afd9f7e1656f1b
