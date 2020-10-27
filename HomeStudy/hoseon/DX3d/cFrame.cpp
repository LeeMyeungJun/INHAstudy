#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame() :m_pMtlTex(NULL), m_pVB(NULL), m_pIB(NULL), m_nNumTri(0)
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}

cFrame::~cFrame()
{
	SafeRelease(m_pMtlTex);
	SafeRelease(m_pVB);
	SafeRelease(m_pIB);
}

void cFrame::Update(int nkeyFrame, D3DXMATRIXA16* pmatParent)
{
	D3DXMATRIXA16		matR, matT;
	
	CalcLocalR(nkeyFrame, matR);
	CalcLocalT(nkeyFrame, matT);
	m_matLocalTM = matR * matT;
	
	m_matWorldTM = m_matLocalTM;

	if(pmatParent)
	{
		m_matWorldTM *= (*pmatParent);
	}

	for each(auto c in m_vecChild)
		c->Update(nkeyFrame, &m_matWorldTM);
}

void cFrame::Render()
{
	if (m_pMtlTex)
	{
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDevice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDevice->SetMaterial(&m_pMtlTex->GetMaterial());
		g_pD3DDevice->SetFVF(ST_PNT_VERTEX::FVF);

		//정점 정보
		/*g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
			m_vecVertex.size() / 3, &m_vecVertex[0], sizeof(ST_PNT_VERTEX));*/

		//버텍스 버퍼
		/*g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_nNumTri);*/

		//인덱스 버퍼
		g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDevice->SetIndices(m_pIB);
		g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vecVertex.size(), 0, m_nNumTri);


	}

	for each(auto c in m_vecChild)
		c->Render();
}

void cFrame::Addchild(cFrame* pChild)
{
	m_vecChild.push_back(pChild);
}

void cFrame::Destroy()
{
	for each(auto c in m_vecChild)
		c->Destroy();

	this->Release();
}

void cFrame::CalcOriginLocalTM(D3DXMATRIXA16* pmatParent)
{
	// : WTM = LTM * PWTM
	// : LTM = WTM * InvPWTM
	m_matLocalTM = m_matWorldTM;
	if(pmatParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, 0, pmatParent);
		m_matLocalTM = m_matWorldTM * matInvParent;
	}

	for each(auto c in m_vecChild)
		c->CalcOriginLocalTM(&m_matWorldTM);
}

void cFrame::CalcLocalT(int nKeyFrame, D3DXMATRIXA16& matT)
{
	D3DXMatrixIdentity(&matT);
	if(m_vecPosTrack.empty())
	{
		matT._41 = m_matLocalTM._41;
		matT._42 = m_matLocalTM._42;
		matT._43 = m_matLocalTM._43;
		return;
	}

	if(nKeyFrame <= m_vecPosTrack.front().n)
	{
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;
	}

	if(nKeyFrame >= m_vecPosTrack.back().n)
	{
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return;
	}

	int nNextIndex = 0;
	for (size_t i = 0; i < m_vecPosTrack.size(); i++)
	{
		if(nKeyFrame < m_vecPosTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}
	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecPosTrack[nPrevIndex].n) / (float)(m_vecPosTrack[nNextIndex].n - m_vecPosTrack[nPrevIndex].n);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].v, &m_vecPosTrack[nNextIndex].v, t);

	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

void cFrame::CalcLocalR(int nKeyFrame, D3DXMATRIXA16& matR)
{
	D3DXMatrixIdentity(&matR);
	if (m_vecRotTrack.empty())
	{
		matR = m_matLocalTM;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}

	if(nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}
	if (nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nNextIndex = 0;
	for (size_t i = 0; i < m_vecRotTrack.size(); i++)
	{
		if (nKeyFrame < m_vecRotTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}
	int nPrevIndex = nNextIndex - 1;

	float t = (nKeyFrame - m_vecRotTrack[nPrevIndex].n) / 
		(float)(m_vecRotTrack[nNextIndex].n - m_vecRotTrack[nPrevIndex].n);

	D3DXQUATERNION	q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrevIndex].q, &m_vecRotTrack[nNextIndex].q, t);
	D3DXMatrixRotationQuaternion(&matR, &q);
}

int cFrame::GetKeyFrame()	//현재 키프레임 리턴
{
	int first = m_dwFirstFrame * m_dwTicksPerFrame;
	int last = m_dwLastFrame * m_dwTicksPerFrame;

	return GetTickCount() % (last - first) + first;
}

void cFrame::BuildVB(vector<ST_PNT_VERTEX>& vecVertex)
{
	m_nNumTri = vecVertex.size() / 3;
	g_pD3DDevice->CreateVertexBuffer(vecVertex.size() * sizeof(ST_PNT_VERTEX), 0,
		ST_PNT_VERTEX::FVF, D3DPOOL_MANAGED, &m_pVB, NULL);
	ST_PNT_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0);
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();
}

void cFrame::BuildIB(vector<ST_PNT_VERTEX>& vecVertex)
{
	vector<WORD> vecIndex;
	for(int i = 0; i < vecVertex.size(); i++)
		vecIndex.push_back(i);
	
	g_pD3DDevice->CreateIndexBuffer(vecVertex.size() * sizeof(ST_PNT_VERTEX), 0,
		D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB, NULL);
	ST_PNT_VERTEX* pI = NULL;
	m_pIB->Lock(0, 0, (LPVOID*)&pI, 0);
	memcpy(pI, &vecIndex[0], vecIndex.size() * sizeof(WORD));
	m_pIB->Unlock();
}

void cFrame::CountFPS()
{
	static DWORD frameCount = 0;						//프레임 카운트수
	static float timeElapsed = 0.0f;					//흐른 시간
	static DWORD lastTime = GetTickCount();				//마지막 시간(temp변수)

	DWORD curTime = GetTickCount();						//현재 시간
	float timeDelta = (curTime - lastTime)*0.001f;      //timeDelta(1번생성후 흐른 시간) 1초단위로 바꿔준다.

	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)							//흐른시간이 1초이상이면 내가 하고싶은것 처리
	{
		float fps = (float)frameCount / timeElapsed;
		cout << "FPS : " << fps << endl;

		frameCount = 0;
		timeElapsed = 0.0f;
	}
	lastTime = curTime;
}
