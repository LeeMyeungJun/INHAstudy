#include "stdafx.h"
#include "cObjLoader.h"

#include <iostream>

#include "cMtlTex.h"
#include "cGroup.h"


cObjLoader::cObjLoader()
{
}

cObjLoader::~cObjLoader()
{
}

void cObjLoader::Load(std::vector<cGroup*>& vecGroup, char* szFolder, char* szFile)
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
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if(szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);	//%*s = 생략
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if(szTemp[0] == 'g')
		{
			if(!vecVertex.empty())
			{
				cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();
			}
		}
		else if(szTemp[0] == 'v')
		{
			if(szTemp[1] == ' ')
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
		else if(szTemp[0] == 'u')
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
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for(int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
		}
	}

	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SafeRelease(it.second);
	}
	m_mapMtlTex.clear();
}

void cObjLoader::LoadMtlLib(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	int nCnt = 0;
	
	while(true)
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
				m_mapMtlTex[sMtlName]->SetAttrID(nCnt++);
			}
		}
		else if (szTemp[0] == 'K')
		{
			if (szTemp[1] == 'a')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Ambient.a = 1.0f;
			}
			else if (szTemp[1] == 'd')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Diffuse.a = 1.0f;
			}
			else if (szTemp[1] == 's')
			{
				float r, g, b;
				sscanf_s(szTemp, "%*s %f %f %f", &r, &g, &b);
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.r = r;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.g = g;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.b = b;
				m_mapMtlTex[sMtlName]->GetMaterial().Specular.a = 1.0f;
			}
		}
		else if (szTemp[0] == 'd')
		{
			float d;
			sscanf_s(szTemp, "%*s %f", &d);
			m_mapMtlTex[sMtlName]->GetMaterial().Power = d;
		}
		else if (szTemp[0] == 'm')
		{
			char szTextFile[1024];
			sscanf_s(szTemp, "%*s %s", szTextFile, 1024);
			sFullPath = string(szFolder);
			sFullPath += (string("/") + string(szTextFile));

			LPDIRECT3DTEXTURE9 pTexture = g_pTextureManager->GetTexture(sFullPath);
			m_mapMtlTex[sMtlName]->SetTexture(pTexture);
		}
	}

	fclose(fp);
}

void cObjLoader::LoadSurface(vector<D3DXVECTOR3>& vecSurface, char* szFolder, char* szFile, D3DXMATRIXA16* pmat)
{
	vector<D3DXVECTOR3> vecV;	//버텍스 정보만 필요
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	//string sMtlName;
	while (true)
	{
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
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
			if (szTemp[1] == ' ')
			{
				float x, y, z;
				sscanf_s(szTemp, "%*s %f %f %f", &x, &y, &z);
				vecV.push_back(D3DXVECTOR3(x, y, z));
			}
			else if (szTemp[1] == 't')
			{
				
			}
			else if (szTemp[1] == 'n')
			{
				
			}
		}
		else if (szTemp[0] == 'u')
		{
			
		}
		else if (szTemp[0] == 'f')
		{
			int nIndex[3];
			sscanf_s(szTemp, "%*s %d/%*d/%*d %d/%*d/%*d %d/%*d/%*d",
				&nIndex[0], &nIndex[1], &nIndex[2]);

			for (int i = 0; i < 3; i++)
			{
				vecSurface.push_back(vecV[nIndex[i] - 1]);
			}
		}
	}

	fclose(fp);

	if(pmat)
	{
		for(size_t i = 0; i < vecSurface.size(); i++)
		{
			D3DXVec3TransformCoord(&vecSurface[i], &vecSurface[i], pmat);
		}
	}
}

LPD3DXMESH cObjLoader::LoadMesh(vector<cMtlTex*>& vecMtlTex, char* szFolder, char* szFile)
{
	vector<DWORD>		vecAttrBuf;
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
		if (feof(fp)) break;

		char szTemp[1024];
		fgets(szTemp, 1024, fp);

		if (szTemp[0] == '#')
		{
			continue;
		}
		else if (szTemp[0] == 'm')
		{
			char szMtlFile[1024];
			sscanf_s(szTemp, "%*s %s", szMtlFile, 1024);	//%*s = 생략
			LoadMtlLib(szFolder, szMtlFile);
		}
		else if (szTemp[0] == 'g')
		{
			if (!vecVertex.empty())
			{
				/*cGroup* pGroup = new cGroup;
				pGroup->SetVertex(vecVertex);
				pGroup->SetMtlTex(m_mapMtlTex[sMtlName]);
				vecGroup.push_back(pGroup);
				vecVertex.clear();*/
			}
		}
		else if (szTemp[0] == 'v')
		{
			if (szTemp[1] == ' ')
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
		else if (szTemp[0] == 'f')
		{
			int nIndex[3][3];
			sscanf_s(szTemp, "%*s %d/%d/%d %d/%d/%d %d/%d/%d",
				&nIndex[0][0], &nIndex[0][1], &nIndex[0][2],
				&nIndex[1][0], &nIndex[1][1], &nIndex[1][2],
				&nIndex[2][0], &nIndex[2][1], &nIndex[2][2]);

			for (int i = 0; i < 3; i++)
			{
				ST_PNT_VERTEX v;
				v.p = vecV[nIndex[i][0] - 1];
				v.t = vecVT[nIndex[i][1] - 1];
				v.n = vecVN[nIndex[i][2] - 1];
				vecVertex.push_back(v);
			}
			vecAttrBuf.push_back(m_mapMtlTex[sMtlName]->GetAttrID());
		}
	}

	fclose(fp);

	vecMtlTex.resize(m_mapMtlTex.size());
	for each(auto it in m_mapMtlTex)
	{
		vecMtlTex[it.second->GetAttrID()] = it.second;
	}

	LPD3DXMESH	pMesh = NULL;
	D3DXCreateMeshFVF(vecAttrBuf.size(), vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDevice, &pMesh);

	ST_PNT_VERTEX* pV = NULL;
	pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	pMesh->UnlockVertexBuffer();

	WORD* pI = NULL;
	pMesh->LockIndexBuffer(0, (LPVOID*)& pI);
	for (int i = 0; i < vecVertex.size(); i++)
		pI[i] = i;
	pMesh->UnlockIndexBuffer();

	DWORD* pA = NULL;
	pMesh->LockAttributeBuffer(0, &pA);
	memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	pMesh->UnlockAttributeBuffer();

	vector<DWORD> vecAdj(vecVertex.size());
	pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);
	pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0], 0, 0, 0);

	m_mapMtlTex.clear();

	return pMesh;
}

void cObjLoader::LoadASE(std::vector<cGroup*>& vecGroup, char* szFolder, char* szsFile)
{
	int open = 1, close = 0;

	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<D3DXVECTOR3> vecVN;

	vector<ST_PNT_VERTEX> vecVertex;
	
	string sFullPath(szFolder);
	sFullPath += (string("/") + string(szsFile));

	FILE* fp;
	fopen_s(&fp, sFullPath.c_str(), "r");

	string sMtlName;
	while (open - close != 0)
	{
		if (feof(fp)) break;
		
		char szTemp[1024];
		int pos = 0;
		fgets(szTemp, 1024, fp);

		char *ptr = strtok(szTemp, " ");
		EliminateChar(ptr, '\t');
		
		if (strcmp(ptr, "*SCENE") == 0)
		{
			ptr = strtok(NULL, " ");
			if (strcmp(ptr, "{\n") == 0)
			{
				while (1)
				{
					fgets(szTemp, 1024, fp);
					ptr = strtok(szTemp, " ");
					EliminateChar(ptr, '\t');
					
					if (strcmp(ptr, "*SCENE_FILENAME") == 0)
					{
						char SCENE_FILENAME[32];
						ptr = strtok(NULL, " ");
						EliminateChar(ptr, '"');
						strcpy(SCENE_FILENAME, ptr);
						cout << SCENE_FILENAME << endl;
						SCENE_FILENAME[strlen(SCENE_FILENAME) - 1] = '\0';
					}
					else if(strcmp(ptr, "*SCENE_FIRSTFRAME") == 0)
					{
						int SCENE_FIRSTFRAME = 0;
						ptr = strtok(NULL, " ");
						SCENE_FIRSTFRAME = stof(ptr);
						cout << SCENE_FIRSTFRAME << endl;
					}
					else if (strcmp(ptr, "*SCENE_LASTFRAME") == 0)
					{
						int SCENE_LASTFRAME = 0;
						ptr = strtok(NULL, " ");
						SCENE_LASTFRAME = stof(ptr);
						cout << SCENE_LASTFRAME << endl;
					}
					else if (strcmp(ptr, "*SCENE_TICKSPERFRAME") == 0)
					{
						int SCENE_TICKSPERFRAME = 0;
						ptr = strtok(NULL, " ");
						SCENE_TICKSPERFRAME = stof(ptr);
						cout << "SCENE_TICKSPERFRAME : " << SCENE_TICKSPERFRAME << endl;
					}
					else if (strcmp(ptr, "}\n") == 0)
						break;
				}
				close++;
				open = 1, close = 0;
			}
		}
		else if (strcmp(ptr, "*MATERIAL_LIST") == 0)
		{
			continue;
		}
		else if (strcmp(ptr, "*GEOMOBJECT") == 0)
		{
			while (open - close != 0)
			{
				ptr = strtok(NULL, " ");
				if (strcmp(ptr, "{\n") == 0)
				{
					while (1)
					{
						fgets(szTemp, 1024, fp);
						char line[64];
						strcpy(line, szTemp);
						ptr = strtok(szTemp, " ");
						EliminateChar(ptr, '\t');
						
						if (strcmp(ptr, "*NODE_NAME") == 0)
						{
							char NODE_NAME[32];
							sscanf_s(line, "%*s %[^\n]", NODE_NAME, 1024);
							EliminateChar(NODE_NAME, '"');
							cout << "NODE_NAME : " << NODE_NAME << endl;
						}
						else if (strcmp(ptr, "*NODE_PARENT") == 0)
						{
							char NODE_PARENT[32];
							ptr = strtok(NULL, " ");
							EliminateChar(ptr, '"');
							strcpy(NODE_PARENT, ptr);
							NODE_PARENT[strlen(NODE_PARENT) - 1] = '\0';
							cout << "NODE_PARENT : " << NODE_PARENT << endl;
						}
						else if (strcmp(ptr, "*NODE_TM") == 0)
						{
							ptr = strtok(NULL, " ");
							if (strcmp(ptr, "{\n") == 0)
							{
								open++;
								while (1)
								{
									fgets(szTemp, 1024, fp);
									ptr = strtok(szTemp, " ");
									EliminateChar(ptr, '\t');
									
									if (strcmp(ptr, "*NODE_NAME") == 0)
									{
										char NODE_NAME[32];
										ptr = strtok(NULL, " ");
										EliminateChar(ptr, '"');
										strcpy(NODE_NAME, ptr);
										NODE_NAME[strlen(NODE_NAME) - 1] = '\0';
										cout << "NODE_NAME2 : " << NODE_NAME << endl;
									}
									else if(strcmp(ptr, "*INHERIT_POS") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, " ");
										x = stof(ptr);
										ptr = strtok(NULL, " ");
										z = stof(ptr);
										ptr = strtok(NULL, " ");
										y = stof(ptr);
										//cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*INHERIT_ROT") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, " ");
										x = stof(ptr);
										ptr = strtok(NULL, " ");
										z = stof(ptr);
										ptr = strtok(NULL, " ");
										y = stof(ptr);
										//cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*INHERIT_SCL") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, " ");
										x = stof(ptr);
										ptr = strtok(NULL, " ");
										z = stof(ptr);
										ptr = strtok(NULL, " ");
										y = stof(ptr);
										//cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_ROW0") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, "\t");
										x = stof(ptr);
										ptr = strtok(NULL, "\t");
										z = stof(ptr);
										ptr = strtok(NULL, "\t");
										y = stof(ptr);
										cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_ROW1") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, "\t");
										x = stof(ptr);
										ptr = strtok(NULL, "\t");
										z = stof(ptr);
										ptr = strtok(NULL, "\t");
										y = stof(ptr);
										cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_ROW2") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, "\t");
										x = stof(ptr);
										ptr = strtok(NULL, "\t");
										z = stof(ptr);
										ptr = strtok(NULL, "\t");
										y = stof(ptr);
										cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_ROW3") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, "\t");
										x = stof(ptr);
										ptr = strtok(NULL, "\t");
										z = stof(ptr);
										ptr = strtok(NULL, "\t");
										y = stof(ptr);
										cout << x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_POS") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, "\t");
										x = stof(ptr);
										ptr = strtok(NULL, "\t");
										z = stof(ptr);
										ptr = strtok(NULL, "\t");
										y = stof(ptr);
										//cout <<"TM_POS : "<< x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_ROTAXIS") == 0)
									{
										float x, y, z;
										ptr = strtok(NULL, "\t");
										x = stof(ptr);
										ptr = strtok(NULL, "\t");
										z = stof(ptr);
										ptr = strtok(NULL, "\t");
										y = stof(ptr);
										//cout << "TM_ROTAXIS : " << x << y << z << endl;
									}
									else if (strcmp(ptr, "*TM_ROTANGLE") == 0)
									{
										float rotAngle;
										ptr = strtok(NULL, " ");
										rotAngle = stof(ptr);
										//cout << "rotAngle : "<<rotAngle << endl;
									}
									else if (strcmp(ptr, "}\n") == 0)	break;
								}
								close++;
							}
						}
						else if (strcmp(ptr, "*MESH") == 0)
						{
							ptr = strtok(NULL, " ");
							if (strcmp(ptr, "{\n") == 0)
							{
								open++;
								while (1)
								{
									fgets(szTemp, 1024, fp);
									ptr = strtok(szTemp, " ");
									EliminateChar(ptr, '\t');

									if (strcmp(ptr, "*TIMEVALUE") == 0)
									{
										float TIMEVALUE;
										ptr = strtok(NULL, " ");
										TIMEVALUE = stof(ptr);
										cout << "TIMEVALUE : " << TIMEVALUE << endl;
									}
									else if (strcmp(ptr, "*MESH_NUMVERTEX") == 0)
									{
										float MESH_NUMVERTEX;
										ptr = strtok(NULL, " ");
										MESH_NUMVERTEX = stof(ptr);
										cout << "MESH_NUMVERTEX : " << MESH_NUMVERTEX << endl;
									}
									else if (strcmp(ptr, "*MESH_NUMFACES") == 0)
									{
										float MESH_NUMFACES;
										ptr = strtok(NULL, " ");
										MESH_NUMFACES = stof(ptr);
										cout << "MESH_NUMFACES : " << MESH_NUMFACES << endl;
									}
									else if (strcmp(ptr, "*MESH_VERTEX_LIST") == 0)
									{
										ptr = strtok(NULL, " ");
										if (strcmp(ptr, "{\n") == 0)
										{
											while (1)
											{
												fgets(szTemp, 1024, fp);
												ptr = strtok(szTemp, " ");
												EliminateChar(ptr, '\t');

												if (strcmp(ptr, "*MESH_VERTEX") == 0)
												{
													float index, x, y, z;
													ptr = strtok(NULL, "\t");
													index = stof(ptr);
													ptr = strtok(NULL, "\t");
													x = stof(ptr);
													ptr = strtok(NULL, "\t");
													z = stof(ptr);
													ptr = strtok(NULL, "\t");
													y = stof(ptr);
													cout << "MESH_VERTEX_LIST : " << x << y << z << endl;
												}
												else if (strcmp(ptr, "}\n") == 0)	break;
											}
										}
									}
									else if (strcmp(ptr, "*MESH_FACE_LIST") == 0)
									{
										ptr = strtok(NULL, " ");
										if (strcmp(ptr, "{\n") == 0)
										{
											while (1)
											{
												fgets(szTemp, 1024, fp);
												ptr = strtok(szTemp, " ");
												EliminateChar(ptr, '\t');

												if (strcmp(ptr, "*MESH_FACE") == 0)
												{
													float index, a, b, c;

													ptr = strtok(NULL, " ");
													EliminateChar(ptr, ':');
													index = stof(ptr);
													ptr = strtok(NULL, " ");
													ptr = strtok(NULL, " ");
													a = stof(ptr);
													ptr = strtok(NULL, " ");
													ptr = strtok(NULL, " ");
													c = stof(ptr);
													ptr = strtok(NULL, " ");
													ptr = strtok(NULL, " ");
													b = stof(ptr);
													cout << "MESH_FACE : " << a << b << c << endl;
												}
												else if (strcmp(ptr, "}\n") == 0)	break;
											}
										}
									}
									else if (strcmp(ptr, "*MESH_NUMTVERTEX") == 0)
									{
										float MESH_NUMTVERTEX;
										ptr = strtok(NULL, " ");
										MESH_NUMTVERTEX = stof(ptr);
										cout << "MESH_NUMTVERTEX : " << MESH_NUMTVERTEX << endl;
									}
									else if (strcmp(ptr, "*MESH_NORMALS") == 0)
									{
										ptr = strtok(NULL, " ");
										if (strcmp(ptr, "{\n") == 0)
										{
											while (1)
											{
												fgets(szTemp, 1024, fp);
												ptr = strtok(szTemp, " ");
												EliminateChar(ptr, '\t');

												if (strcmp(ptr, "*MESH_FACENORMAL") == 0)
												{
													float index, x, y, z;

													ptr = strtok(NULL, "\t");
													index = stof(ptr);
													ptr = strtok(NULL, "\t");
													x = stof(ptr);
													ptr = strtok(NULL, "\t");
													z = stof(ptr);
													ptr = strtok(NULL, "\t");
													y = stof(ptr);
													cout << "MESH_FACENORMAL : " << x << y << z << endl;
												}
												else if (strcmp(ptr, "*MESH_VERTEXNORMAL") == 0)
												{
													float index, x, y, z;

													ptr = strtok(NULL, "\t");
													index = stof(ptr);
													ptr = strtok(NULL, "\t");
													x = stof(ptr);
													ptr = strtok(NULL, "\t");
													z = stof(ptr);
													ptr = strtok(NULL, "\t");
													y = stof(ptr);
													cout << "MESH_VERTEXNORMAL : " << index << x << y << z << endl;
												}
												else if (strcmp(ptr, "}\n") == 0)	break;
											}
										}
									}
									else if (strcmp(ptr, "}\n") == 0)	break;
								}
								close++;
							}
						}
						else if (strcmp(ptr, "}\n") == 0)	break;
					}
					close++;
				}
			}
			open = 1, close = 0;
		}
		else
			continue;
	}
	fclose(fp);

	for each(auto it in m_mapMtlTex)
	{
		SafeRelease(it.second);
	}
	m_mapMtlTex.clear();
}

void cObjLoader::EliminateChar(char* str, char c)
{
	for (; *str != '\0'; str++)	//종료 문자를 만날 때까지 반복
	{
		if (*str == c)			//ch와 같은 문자일 때
		{
			strcpy(str, str + 1);
			str--;
		}
	}
}