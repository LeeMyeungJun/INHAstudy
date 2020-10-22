#include "stdafx.h"
#include "cHeightMap.h"


cHeightMap::cHeightMap()
	: m_pTexture(NULL)
	, m_pMesh(NULL)
{
}


cHeightMap::~cHeightMap()
{
	Destroy();
}

void cHeightMap::Setup(char* szFolder, char* szRaw, char* szTex, DWORD dwBytesPerPixel)
{
	string sFolder(szFolder);
	string sRaw = sFolder + string(szRaw);
	string sTex = sFolder + string(szTex);

	m_pTexture = g_pTextureManager->GetTexture(sTex);

	//>>:raw
	FILE* fp = NULL;
	fopen_s(&fp, sRaw.c_str(), "rb");

	fseek(fp, 0, SEEK_END);
	int nFileSize = ftell(fp);
	int nNumVertex = nFileSize / dwBytesPerPixel;

	int nRow = (int)(sqrt((float)nNumVertex) + 0.0001f);//오차가 발생할수있기떄문에 0.0001f를 더해준다. float들어가면은 정확히 안들어갈수있어서그래
	int nCol = nRow; //정방향이니깐 같을거고
	int nTileN = nRow - 1;
	m_nTileN = nTileN; //타일갯수

	fseek(fp, 0, SEEK_SET);//처음으로 돌려준다 .

	vector<ST_PNT_VERTEX> vecVertex(nNumVertex);
	m_vecVertex.resize(nNumVertex);

	vector<DWORD> vecIndex;
	vecIndex.reserve(nTileN * nTileN * 2 * 3); //resize해도되고 reserve해줘도됨

	for(int i = 0 ; i < nNumVertex ; i++)
	{
		ST_PNT_VERTEX v;
		v.p = D3DXVECTOR3(i % nCol, ((unsigned char)fgetc(fp))/10.0f , i/nCol  );
		v.n = D3DXVECTOR3(0, 1, 0);
		v.t = D3DXVECTOR2((i%nCol) / (float)nCol, (i / nCol) / (float)nCol);

		vecVertex[i] = v;
		m_vecVertex[i] = v.p;

		if(dwBytesPerPixel ==3)//3바이트일경우 
		{
			fgetc(fp), fgetc(fp); //나머지 2개는 버릴거야 버리는이유는 맨앞값이 높이값이라그런건가?
		}
		
	}

	fclose(fp);

	for(int x= 1; x < nTileN; x++)
	{
		for(int z = 1; z < nTileN ; z++)
		{
			int left = (z + 0) * nCol + x - 1;
			int right = (z + 0) * nCol + x + 1;

			int up = (z + 1) * nCol + x;
			int down = (z - 1) * nCol + x;

			//사방향의 점들 구한다 .

			D3DXVECTOR3 leftToRight = m_vecVertex[right] - m_vecVertex[left];
			D3DXVECTOR3 downToUp = m_vecVertex[up] - m_vecVertex[down];

			D3DXVECTOR3 normal;
			D3DXVec3Cross(&normal, &downToUp, &leftToRight);
			D3DXVec3Normalize(&normal, &normal);

			int nIndex = z * nCol + x;
			vecVertex[nIndex].n = normal;
			
		}
	}//<<: for x


	//인덱스 만들어주는곳
	for(int x = 0 ; x < nTileN ; x++)
	{
		for(int z= 0; z< nTileN ; z++)
		{
			int _0 = (z + 0) * nCol + x + 0;
			int _1 = (z + 1) * nCol + x + 0;
			int _2 = (z + 1) * nCol + x + 1;
			int _3 = (z + 0) * nCol + x + 1;

			vecIndex.push_back(_0);
			vecIndex.push_back(_1);
			vecIndex.push_back(_3);

			vecIndex.push_back(_2);
			vecIndex.push_back(_3);
			vecIndex.push_back(_1);


		}//<<: for z
	}//<<:for x

	//:
	D3DXCreateMeshFVF(vecIndex.size() / 3, vecVertex.size(), D3DXMESH_MANAGED | D3DXMESH_32BIT, ST_PNT_VERTEX::FVF, g_pD3DDvice, &m_pMesh);
	//버텍스 버퍼
	ST_PNT_VERTEX* pV = NULL;
	m_pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pMesh->UnlockVertexBuffer();
	//인덱스버퍼
	DWORD* pI = NULL; //WORD로하면 반으로잘려나올거야 좀커서 DWORD로 해야해
	m_pMesh->LockIndexBuffer(0, (LPVOID*)&pI);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(DWORD));
	m_pMesh->UnlockIndexBuffer();
	//속성버퍼
	DWORD* pA = NULL;
	m_pMesh->LockAttributeBuffer(0, &pA);
	//memcpy(pA, ,(vecIndex.size() / 3) * sizeof(DWORD));
	ZeroMemory(pA, (vecIndex.size() / 3) * sizeof(DWORD));//그냥 0으로갔다가 속성들을 다맞춰줘도 되니까
	m_pMesh->UnlockAttributeBuffer();
	
	vector<DWORD> vecAdj(vecIndex.size());
	m_pMesh->GenerateAdjacency(0.0f, &vecAdj[0]);

	m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT |
		D3DXMESHOPT_COMPACT |
		D3DXMESHOPT_VERTEXCACHE,
		&vecAdj[0],
		0, 0, 0);
	//이제 머터리얼
	ZeroMemory(&m_stMtl, sizeof(D3DMATERIAL9));
	m_stMtl.Ambient = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Diffuse = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);
	m_stMtl.Specular = D3DXCOLOR(0.8f, 0.8f, 0.8f, 1.0f);

}

void cHeightMap::Render()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	g_pD3DDvice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDvice->SetMaterial(&m_stMtl);
	g_pD3DDvice->SetTexture(0, m_pTexture);
	m_pMesh->DrawSubset(0);
	g_pD3DDvice->SetTexture(0, NULL);// 이거 왜안넣으시지?
}

bool cHeightMap::GetHeight(float x, float& y, float z)
{
	if(x < 0.f || z <0.f || x>= m_nTileN || z>=m_nTileN)
	{
		y = 0;
		return false;
	}
	int nX = x;
	int nZ = z;

	float fDeltaX = x - nX;
	float fDeltaZ = z - nZ;

	//아까 인덱스식있찌

	int _0 = (nZ + 0) * (m_nTileN +1) + nX + 0;
	int _1 = (nZ + 1) * (m_nTileN +1) + nX + 0;
	int _2 = (nZ + 1) * (m_nTileN +1) + nX + 1;
	int _3 = (nZ + 0) * (m_nTileN +1) + nX + 1;

	//왼쪽삼각형먼저 계산해줄게 
	if(fDeltaX + fDeltaZ < 1.0f)
	{
		D3DXVECTOR3 v01 = m_vecVertex[_1] - m_vecVertex[_0];
		D3DXVECTOR3 v03 = m_vecVertex[_3] - m_vecVertex[_0];
		y = m_vecVertex[_0].y + (v01 * fDeltaZ + v03 *fDeltaX).y;
	}
	else//오른쪽삼각형
	{
		fDeltaX = 1.0f - fDeltaX;
		fDeltaZ = 1.0f - fDeltaZ;
		D3DXVECTOR3 v21 = m_vecVertex[_1] - m_vecVertex[_2];
		D3DXVECTOR3 v23 = m_vecVertex[_3] - m_vecVertex[_2];
		y = m_vecVertex[_2].y + (v21 * fDeltaX + v23*fDeltaZ).y;

	}

	return true;
}

void cHeightMap::Destroy()
{
	SafeRelease(m_pTexture);
	SafeRelease(m_pMesh);
}
