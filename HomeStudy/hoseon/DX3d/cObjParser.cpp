#include "stdafx.h"
#include "cObjParser.h"
#include "cBox.h"
#include <iostream>

cObjParser::cObjParser()
{
}

cObjParser::~cObjParser()
{
}

void cObjParser::ReadFile(char* _filename, cBox *_box)
{
	char line[256];
	vector<D3DXVECTOR3> m_vVertex;
	vector<D3DXVECTOR2> m_vTexture;
	vector<D3DXVECTOR3> m_vNormal;
	
	FILE *fp = fopen(_filename, "r");

	while(fgets(line, sizeof(line), fp))	//파일 끝까지 읽는다
	{
		char *ptr = strtok(line, " ");

		if (strcmp(ptr, "#") == 0)
		{
			continue;
		}
		else if (strcmp(ptr, "mtllib") == 0)
		{
			ptr = strtok(NULL, " ");
			strcpy(m_mtlPath, ptr);
			cout << m_mtlPath << endl;
			m_mtlPath[strlen(m_mtlPath) - 1] = '\0';
		}
		else if(strcmp(ptr, "v") == 0)
		{
			D3DXVECTOR3 v;
			ptr = strtok(NULL, " ");
			v.x = stof(ptr);
			ptr = strtok(NULL, " ");
			v.y = stof(ptr);
			ptr = strtok(NULL, " ");
			v.z = stof(ptr);
			m_vVertex.push_back(v);
		}
		else if(strcmp(ptr, "vt") == 0)
		{
			D3DXVECTOR2 v;
			ptr = strtok(NULL, " ");
			v.x = stof(ptr);
			ptr = strtok(NULL, " ");
			v.y = stof(ptr);
			m_vTexture.push_back(v);
		}
		else if (strcmp(ptr, "vn") == 0)
		{
			D3DXVECTOR3 v;
			ptr = strtok(NULL, " ");
			v.x = stof(ptr);
			ptr = strtok(NULL, " ");
			v.y = stof(ptr);
			ptr = strtok(NULL, " ");
			v.z = stof(ptr);
			m_vNormal.push_back(v);
		}
		else if(strcmp(ptr, "f") == 0)
		{
			ST_PNT_VERTEX v;
			ptr = strtok(NULL, "/");
			v.p = m_vVertex[stoi(ptr) - 1];
			ptr = strtok(NULL, "/");
			v.t = m_vTexture[stoi(ptr) - 1];
			ptr = strtok(NULL, " ");
			v.n = m_vNormal[stoi(ptr) - 1];
			_box->m_vecVertex.push_back(v);

			ptr = strtok(NULL, "/");
			v.p = m_vVertex[stoi(ptr) - 1];
			ptr = strtok(NULL, "/");
			v.t = m_vTexture[stoi(ptr) - 1];
			ptr = strtok(NULL, " ");
			v.n = m_vNormal[stoi(ptr) - 1];
			_box->m_vecVertex.push_back(v);

			ptr = strtok(NULL, "/");
			v.p = m_vVertex[stoi(ptr) - 1];
			ptr = strtok(NULL, "/");
			v.t = m_vTexture[stoi(ptr) - 1];
			ptr = strtok(NULL, "\n");
			v.n = m_vNormal[stoi(ptr) - 1];
			_box->m_vecVertex.push_back(v);
		}
	}
	fclose(fp);

	fp = fopen(m_mtlPath, "r");

	while (fgets(line, sizeof(line), fp))
	{
		char *ptr = strtok(line, " ");

		if (strcmp(ptr, "Ka") == 0)
		{
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Ambient.r = stof(ptr);
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Ambient.g = stof(ptr);
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Ambient.b = stof(ptr);

			_box->m_boxMtl.Ambient.a = 1.0f;
		}
		else if (strcmp(ptr, "Kd") == 0)
		{
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Diffuse.r = stof(ptr);
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Diffuse.g = stof(ptr);
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Diffuse.b = stof(ptr);

			_box->m_boxMtl.Diffuse.a = 1.0f;
		}
		else if (strcmp(ptr, "Ks") == 0)
		{
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Specular.r = stof(ptr);
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Specular.g = stof(ptr);
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Specular.b = stof(ptr);

			_box->m_boxMtl.Specular.a = 1.0f;
		}
		else if (strcmp(ptr, "d") == 0)
		{
			ptr = strtok(NULL, " ");
			_box->m_boxMtl.Power = stof(ptr);
		}
		else if (strcmp(ptr, "map_Kd") == 0)
		{
			ptr = strtok(NULL, " ");
			strcpy(m_texPath, ptr);
			cout << m_texPath << endl;
			m_texPath[strlen(m_texPath) - 1] = '\0';

			WCHAR	wTexturePath[32];
			ZeroMemory(&wTexturePath, sizeof(wTexturePath));
			mbstowcs(wTexturePath, m_texPath, strlen(m_texPath));
			D3DXCreateTextureFromFile(g_pD3DDevice, wTexturePath, &_box->m_boxTexture);
		}
	}
}
