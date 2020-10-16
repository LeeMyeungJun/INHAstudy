#include "stdafx.h"
#include "cAseLoader.h"


#include "stdafx.h"
#include "cAseLoader.h"
#include "Asciitok.h"
#include "cMtlTex.h"
#include "cFrame.h"

cAseLoader::cAseLoader()
	: m_fp(nullptr)
	, MtlIndex(0)
{
}


cAseLoader::~cAseLoader()
{
}

cFrame* cAseLoader::Load(char* szFullPath)
{
	cFrame* pRoot = nullptr;

	fopen_s(&m_fp, szFullPath, "r");

	while (char* szToken = GetToken())
	{
		if (IsEqual(szToken, ID_SCENE))
		{
			ProcessScene();
		}
		else if (IsEqual(szToken, ID_MATERIAL_LIST))
		{
			ProcessMATERIAL_LIST();
		}
		else if (IsEqual(szToken, ID_GEOMETRY))
		{
			cFrame* pFrame = ProcessGEOBJECT();
			if (pRoot == nullptr)
			{
				pRoot = pFrame;
				Set_SceneFrame(pRoot);
			}
		}
	} //<<:while()
	fclose(m_fp);

	for each (auto p in m_vecMtlTex)
	{
		SafeRelease(p);
	}

	pRoot->CalcOriginLocalTM(nullptr);

	return pRoot;
}

char* cAseLoader::GetToken()
{
	int nReadCnt = 0; //���� ����
	bool isQuote = false;

	while (true)
	{
		char c = fgetc(m_fp);
		if (feof(m_fp))break;

		if (c == '\"')
		{
			if (isQuote) break;
			isQuote = true;
			continue;
		}

		if (!isQuote && IsWhite(c))
		{
			if (nReadCnt == 0)
				continue;
			break;
		}
		//�׻��̿� �ִ³������ ��ٿ�
		m_szToken[nReadCnt++] = c;
	} //<<:while()
	if (nReadCnt == 0)
		return nullptr;
	//�ǵڿ��ٰ� �ι��ڸ� �־��ְ�
	m_szToken[nReadCnt] = '\0';
	//�ָ� �Ѱ��ش� .
	return m_szToken;
}

int cAseLoader::GetInteger()
{
	return atoi(GetToken());
}

float cAseLoader::GetFloat()
{
	return static_cast<float>(atof(GetToken()));
}

bool cAseLoader::IsWhite(char c)
{
	return c < 33; //33���ΰ��� ��Եǳ� ? ���߿� �˾Ƽ� Ȯ���ع�
}

bool cAseLoader::IsEqual(char* str1, char* str2)
{
	return strcmp(str1, str2) == 0; //���ٰ��ϸ� �������ݾ�
}

void cAseLoader::SkipBlock()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL_LIST()
{
	int nLevel = 0;
	int nCnt = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MATERIAL_COUNT))
		{
			for each (auto p in m_vecMtlTex)
			{
				SafeRelease(p);
			}
			m_vecMtlTex.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MATERIAL))
		{
			MtlIndex = GetInteger();
			m_vecMtlTex[MtlIndex] = new cMtlTex;
			ProcessMATERIAL(m_vecMtlTex[MtlIndex]);
			////�����߰�
			m_vecMtlTex[MtlIndex]->SetAttrID(nCnt++);
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMATERIAL(cMtlTex* pMtltex)
{
	D3DMATERIAL9 stMtl;
	ZeroMemory(&stMtl, sizeof(D3DMATERIAL9));

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_AMBIENT))
		{
			stMtl.Ambient.r = GetFloat();
			stMtl.Ambient.g = GetFloat();
			stMtl.Ambient.b = GetFloat();
			stMtl.Ambient.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_DIFFUSE))
		{
			stMtl.Diffuse.r = GetFloat();
			stMtl.Diffuse.g = GetFloat();
			stMtl.Diffuse.b = GetFloat();
			stMtl.Diffuse.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_SPECULAR))
		{
			stMtl.Specular.r = GetFloat();
			stMtl.Specular.g = GetFloat();
			stMtl.Specular.b = GetFloat();
			stMtl.Specular.a = 1.0f;
		}
		else if (IsEqual(szToken, ID_MAP_DIFFUSE))
		{
			ProcessMAP_DIFFUSE(pMtltex);
		}
	}
	while (nLevel > 0);

	pMtltex->SetMaterial(stMtl);
}

void cAseLoader::ProcessMAP_DIFFUSE(cMtlTex* pMtltex)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_BITMAP))
		{
			szToken = GetToken();
			pMtltex->SetTexture(g_pTextureManager->GetTexture(szToken));
		}
	}
	while (nLevel > 0);
}

cFrame* cAseLoader::ProcessGEOBJECT()
{
	cFrame* pFrame = new cFrame;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_NODE_NAME))
		{
			m_mapFrame[GetToken()] = pFrame;
		}
		else if (IsEqual(szToken, ID_NODE_PARENT))
		{
			m_mapFrame[GetToken()]->AddChild(pFrame);
		}
		else if (IsEqual(szToken, ID_NODE_TM))
		{
			ProcessNODE_TM(pFrame);
		}
		else if (IsEqual(szToken, ID_MESH))
		{
			ProcessMESH(pFrame);
		}
		else if (IsEqual(szToken, ID_TM_ANIMATION))
		{
			//>>:Animation
			ProcessTM_ANIMATION(pFrame);

			//<<:
		}
		else if (IsEqual(szToken, ID_MATERIAL_REF))
		{
			int nMtlIndex = GetInteger();
			pFrame->SetMtlTex(m_vecMtlTex[nMtlIndex]);
		}
	}
	while (nLevel > 0);

	return pFrame;
}

void cAseLoader::ProcessMESH(OUT cFrame* pFrame)
{
	vector<D3DXVECTOR3> vecV;
	vector<D3DXVECTOR2> vecVT;
	vector<ST_PNT_VERTEX> vecVertex;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_NUMVERTEX))
		{
			vecV.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_NUMFACES))
		{
			vecVertex.resize(GetInteger() * 3);
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX_LIST))
		{
			ProcessMESH_VERTEX_LIST(vecV);
		}
		else if (IsEqual(szToken, ID_MESH_FACE_LIST))
		{
			ProcessMESH_FACE_LIST(vecVertex, vecV);
		}
		else if (IsEqual(szToken, ID_MESH_NUMTVERTEX))
		{
			vecVT.resize(GetInteger());
		}
		else if (IsEqual(szToken, ID_MESH_TVERTLIST))
		{
			ProcessMESH_TVERTLIST(vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_TFACELIST))
		{
			ProcessMESH_TFACELIST(vecVertex, vecVT);
		}
		else if (IsEqual(szToken, ID_MESH_NORMALS))
		{
			ProcessMESH_NOMRALS(vecVertex);
		}
	}
	while (nLevel > 0);

	D3DXMATRIXA16 matInvWorld;
	D3DXMatrixInverse(&matInvWorld, nullptr, &pFrame->GetWorldTM());
	for (int i = 0; i < vecVertex.size(); i++)
	{
		D3DXVec3TransformCoord(&vecVertex[i].p, &vecVertex[i].p, &matInvWorld);

		D3DXVec3TransformNormal(&vecVertex[i].n, &vecVertex[i].n, &matInvWorld);
		
	}
	pFrame->SetVertex(vecVertex); //�̰͵γְ� cFrame Render�Ҷ� �ΰ��� �����غ� �׷��� �ӵ��� üũ�غ� FPS �� üũ�ع�
	pFrame->BuildVB(vecVertex);//���ؽ����۷� �����


	
}
//�ʴ� ����� ������.
void cAseLoader::ProcessMESH_VERTEX_LIST(vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	do
	{
		char * szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nIndex = GetInteger();
			vecV[nIndex].x = GetFloat();
			vecV[nIndex].z = GetFloat();
			vecV[nIndex].y = GetFloat();
		}
	} while (nLevel > 0); }

void cAseLoader::ProcessMESH_FACE_LIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR3>& vecV)
{
	int nLevel = 0;
	bool bFlag = false;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEX))
		{
			int nFaceIndex = GetInteger();
		}
		else if (IsEqual(szToken, ID_MESH_FACE))
		{
			bFlag = true;
			int nFaceIndex = GetInteger();
			GetToken();
			vecVertex[nFaceIndex * 3 + 0].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nFaceIndex * 3 + 2].p = vecV[GetInteger()];
			GetToken();
			vecVertex[nFaceIndex * 3 + 1].p = vecV[GetInteger()];
		}
	}
	while (nLevel > 0);

	if(bFlag)
		vecAttrBuf.push_back(m_vecMtlTex[MtlIndex]->GetAttrID());
}

void cAseLoader::ProcessMESH_TVERTLIST(vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TVERT))
		{
			int nIndex = GetInteger();
			vecVT[nIndex].x = GetFloat();
			vecVT[nIndex].y = 1.0f - GetFloat();
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMESH_TFACELIST(vector<ST_PNT_VERTEX>& vecVertex, vector<D3DXVECTOR2>& vecVT)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_TFACE))
		{
			int nFaceIndex = GetInteger();
			vecVertex[nFaceIndex * 3 + 0].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 2].t = vecVT[GetInteger()];
			vecVertex[nFaceIndex * 3 + 1].t = vecVT[GetInteger()];
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessMESH_NOMRALS(vector<ST_PNT_VERTEX>& vecVertex)
{
	int nFaceIndex = 0;
	int aModIndex[3] = {0, 2, 1};
	int nModCount = 0;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_MESH_FACENORMAL))
		{
			nFaceIndex = GetInteger();
			nModCount = 0;
		}
		else if (IsEqual(szToken, ID_MESH_VERTEXNORMAL))
		{
			GetToken();
			D3DXVECTOR3 n;
			n.x = GetFloat();
			n.z = GetFloat();
			n.y = GetFloat();
			vecVertex[nFaceIndex * 3 + aModIndex[nModCount++]].n = n;
		}
	}
	while (nLevel > 0);
}

void cAseLoader::ProcessNODE_TM(cFrame* pFrame)
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_TM_ROW0))
		{
			matWorld._11 = GetFloat();
			matWorld._13 = GetFloat();
			matWorld._12 = GetFloat();
			matWorld._14 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW1))
		{
			matWorld._31 = GetFloat();
			matWorld._33 = GetFloat();
			matWorld._32 = GetFloat();
			matWorld._34 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW2))
		{
			matWorld._21 = GetFloat();
			matWorld._23 = GetFloat();
			matWorld._22 = GetFloat();
			matWorld._24 = 0.0f;
		}
		else if (IsEqual(szToken, ID_TM_ROW3))
		{
			matWorld._41 = GetFloat();
			matWorld._43 = GetFloat();
			matWorld._42 = GetFloat();
			matWorld._44 = 1.0f;
		}
	}
	while (nLevel > 0);

	pFrame->SetWorldTM(matWorld);
}

void cAseLoader::ProcessScene()
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if(IsEqual(szToken,ID_FIRSTFRAME))
		{
			m_dwFirstFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_LASTFRAME))
		{
			m_dwLastFrame = GetInteger();
		}
		else if (IsEqual(szToken, ID_FRAMESPEED))
		{
			m_dwFrameSpeed = GetInteger();
		}
		else if (IsEqual(szToken, ID_TICKSPERFRAME))
		{
			m_dwTicksPerFrame = GetInteger();
		}
		
	} while (nLevel > 0);
	
}

void cAseLoader::Set_SceneFrame(cFrame* pRoot)
{
	pRoot->m_dwFirstFrame	 = m_dwFirstFrame;
	pRoot->m_dwLastFrame	 = m_dwLastFrame;
	pRoot->m_dwFrameSpeed	 = m_dwFrameSpeed;
	pRoot->m_dwTicksPerFrame = m_dwTicksPerFrame;
	
}

void cAseLoader::ProcessTM_ANIMATION(cFrame* pFrame)
{
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken,ID_POS_TRACK))
		{
			ProcessCONTROL_POS_TRACK(pFrame);
		}
		else if (IsEqual(szToken, ID_ROT_TRACK))
		{
			ProcessCONTROL_ROT_TRACK(pFrame);
		}

	} while (nLevel > 0);
}

void cAseLoader::ProcessCONTROL_POS_TRACK(cFrame* pFrame)
{
	vector<ST_POS_SAMPLE> vecPosTrack;
	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_POS_SAMPLE))
		{
			ST_POS_SAMPLE s;
			s.n = GetInteger();
			s.v.x = GetFloat();
			s.v.z = GetFloat();
			s.v.y = GetFloat();
			//x z y ��
			vecPosTrack.push_back(s);
		}
	} while (nLevel > 0);
	//�ٳ�������������

	pFrame->SetPosTrack(vecPosTrack);
	
}

void cAseLoader::ProcessCONTROL_ROT_TRACK(cFrame* pFrame)
{
	vector<ST_ROT_SAMPLE> vecRotTrack;

	int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
		else if (IsEqual(szToken, ID_ROT_SAMPLE))
		{
			ST_ROT_SAMPLE s;
			s.n = GetInteger();
			s.q.x = GetFloat();
			s.q.z = GetFloat();
			s.q.y = GetFloat();
			s.q.w = GetFloat();
			//���ʹϾ������ �ٲ������ �װſ����� ��ȯ����
			
			//�����ϱⰡ ����ؼ� �̷����ϸ� �ȴٱ��常 �˾ƶ�
			//>>: ��
			s.q.x *= sinf(s.q.w / 2.f);
			s.q.y *= sinf(s.q.w / 2.f);
			s.q.z *= sinf(s.q.w / 2.f);
			s.q.w  = cosf(s.q.w / 2.f);
			//<<:

			if(!vecRotTrack.empty())
			{
				s.q = vecRotTrack.back().q * s.q; //�������� �����Ƚ�Ű�µ� ȸ������ ��������������� 
			}
			//�ǵڿ��ִ°� ȸ�������ְ� �־��ִ±��� .. 
			vecRotTrack.push_back(s);
		}
	} while (nLevel > 0);

	pFrame->SetRotTrack(vecRotTrack);

	//640 3200 �߰����̿��ִ°͵��� �������ִ� ���鰫�ٰ� �������ѰŰ� 
}

LPD3DXMESH cAseLoader::LoadMesh(vector<cMtlTex*>& vecMtlTex, char* szFullPath)
{
	//cFrame* pRoot = nullptr;
	//

	//fopen_s(&m_fp, szFullPath, "r");

	//while (char* szToken = GetToken())
	//{
	//	if (IsEqual(szToken, ID_SCENE))
	//	{
	//		ProcessScene();
	//	}
	//	else if (IsEqual(szToken, ID_MATERIAL_LIST))
	//	{
	//		ProcessMATERIAL_LIST();
	//	}
	//	else if (IsEqual(szToken, ID_GEOMETRY))
	//	{
	//		cFrame* pFrame = ProcessGEOBJECT();
	//		if (pRoot == nullptr)
	//		{
	//			pRoot = pFrame;
	//			Set_SceneFrame(pRoot);
	//		}
	//	}
	//} //<<:while()
	//fclose(m_fp);

	//for each (auto p in m_vecMtlTex)
	//{
	//	SafeRelease(p);
	//}

	//pRoot->CalcOriginLocalTM(nullptr);

	//

	//vecMtlTex.resize(m_vecMtlTex.size());
	//for each(auto it in m_vecMtlTex)
	//{
	//	vecMtlTex[it->GetAttrID()] = it;
	//}
	//LPD3DXMESH pMesh = NULL;
	//D3DXCreateMeshFVF(vecAttrBuf.size(), vecVertex.size(), D3DXMESH_MANAGED, ST_PNT_VERTEX::FVF, g_pD3DDvice, &pMesh);


	////���ؽ����� ����
	//ST_PNT_VERTEX* pV = NULL;
	//pMesh->LockVertexBuffer(0, (LPVOID*)&pV);
	//memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));

	//pMesh->UnlockVertexBuffer();


	////�ε������� ����
	//WORD* pI = NULL;
	//pMesh->LockIndexBuffer(0, (LPVOID*)& pI);
	//for (int i = 0; i < vecVertex.size(); i++)
	//{
	//	pI[i] = i;

	//}
	//pMesh->UnlockIndexBuffer();


	////�Ӽ����� ����
	//DWORD* pA = NULL;
	//pMesh->LockAttributeBuffer(0, &pA);
	//memcpy(pA, &vecAttrBuf[0], vecAttrBuf.size() * sizeof(DWORD));
	//pMesh->UnlockAttributeBuffer();
	////����������ص� �Ž��׸��µ� ���������� ������ ����ȭ�� ����߰���? �׺κ��� �ؿ�
	//vector<DWORD> vecAdj(vecVertex.size());
	//pMesh->GenerateAdjacency(0.0f, &vecAdj[0]); //0.0000000000001 ������ ���������� �ϰڴ� ù�������ڼ���
	//pMesh->OptimizeInplace(D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE, &vecAdj[0], 0, 0, 0); //D3DXMESHOPT_ATTRSORT ����ȭ�� ���� D3DXMESHOPT_COMPACT�������°� ����� 

	//m_mapMtlTex.clear();

	return 0;
}


/*
 *
   int nLevel = 0;
	do
	{
		char* szToken = GetToken();
		if (IsEqual(szToken, "{"))
		{
			++nLevel;
		}
		else if (IsEqual(szToken, "}"))
		{
			--nLevel;
		}
	} while (nLevel > 0);
 */