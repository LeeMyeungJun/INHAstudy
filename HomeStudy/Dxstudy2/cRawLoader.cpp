#include "stdafx.h"
#include "cRawLoader.h"


cRawLoader::cRawLoader()
	: m_fp(NULL)
{
}


cRawLoader::~cRawLoader()
{
}

void cRawLoader::RawLoader(char* FileName, char* Texture, vector<ST_PNT_VERTEX>& rawVector)
{
	//int width = 257;
	//int height = 257;
	//fopen_s(&m_fp, FileName, "rb");
	//vector<ST_PNT_VERTEX> temp;
	//if (m_fp == NULL)
	//	return;
	//int a = 0;
	//int RawSize = 1;
	//int rowcnt = 0, colcnt = 0;

	//do
	//{
	//	a = fgetc(m_fp);
	//	if (a == EOF)
	//		break;
	//	ST_PNT_VERTEX v;
	//	v.n = D3DXVECTOR3(0, 1, 0);
	//	v.p = D3DXVECTOR3(rowcnt*RawSize, (float)a/10 , colcnt*RawSize);
	//	
	//	v.t.x = (float)rowcnt/256;
	//	v.t.y = (float)colcnt/256;
	////u v
	//	temp.push_back(v);
	//	rowcnt++;
	//	if (rowcnt == width-1)
	//	{
	//		colcnt++;
	//		rowcnt = 0;
	//	}
	//} while (true);
	//fclose(m_fp);


	fopen_s(&m_fp, FileName, "rb");
	vector<ST_PNT_VERTEX> temp;
	int a = 0;
	if (m_fp == NULL)
		return;

	while (true)
	{
		a = fgetc(m_fp);
		if (a == EOF)
			break;
		ST_PNT_VERTEX v;
		v.n = D3DXVECTOR3(0, 1, 0);
		v.p = D3DXVECTOR3(0, (float)a/10, 0);
		temp.push_back(v);
	}
	int width = 257;
	int height = width;
	float range = 1.0f;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			temp[i * height + j].p.x = (float)j*range;
			temp[i * height + j].p.z = (float)i*range;

			temp[i * height + j].t.x = (float)j/(width-1);
			temp[i * height + j].t.y = (float)i/(height-1);
		}
	}

	//1차원 배열로 2차원배열을 표현을할때 사용하는식인데 . 0번쨰부터 끝 256* 256 까지 다표현을할수있어 .
	//256까지다했어 . 그러면 다음줄은 ? 257 부터 표현을하니까 i값이 1일떄 height 는 257이니까 j = 0 257 
	//514 

	CreateIndex(temp, rawVector);
	
	
}

void cRawLoader::CreateIndex(vector<ST_PNT_VERTEX> temp, vector<ST_PNT_VERTEX>& rawVector)
{
	int width  = 257;
	int height = width;
	int a[6];
	for(int j = 0 ; j < height -1 ; j++)
	{
		for (int i = 0; i < width - 1; i++)
		{
			a[0] = j*((width)) + i + width;
			a[1] = j*((width)) + i;
			a[2] = j*((width)) + i + 1;
			a[3] = j*((width)) + i + width;
			a[4] = j*((width)) + i + 1;
			a[5] = j*((width)) + i + 1 + width;
			
		
			rawVector.push_back(temp[a[0]]);
			rawVector.push_back(temp[a[2]]);
			rawVector.push_back(temp[a[1]]);

			rawVector.push_back(temp[a[3]]);
			rawVector.push_back(temp[a[5]]);
			rawVector.push_back(temp[a[4]]);

		}
	}
	

	//for(int i = 0 ; i < height -1; i++)
	//{
	//	for(int j = 0 ; j < width -1 ; j++)
	//	{
	//		a[0] = i * width + j;
	//		a[1] = i * width + j + 1;
	//		a[2] = (i+1) * width + j;
	//		a[3] = (i +1 ) * width + j;
	//		a[4] = i * width + j+1;
	//		a[5] = (i+1)* width+j+1;
	//		rawVector.push_back(temp[a[0]]);
	//		rawVector.push_back(temp[a[1]]);
	//		rawVector.push_back(temp[a[2]]);
	//		rawVector.push_back(temp[a[3]]);
	//		rawVector.push_back(temp[a[4]]);
	//		rawVector.push_back(temp[a[5]]);
	//	}
	//}

	return;
}


