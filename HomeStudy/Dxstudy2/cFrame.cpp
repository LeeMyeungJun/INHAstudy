#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame()
	: m_pMtlTex(nullptr)
	, m_pVB(NULL) //이거랑
	, m_nNumTri(0) //이거랑
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cFrame::~cFrame()
{
	SafeRelease(m_pMtlTex);
	SafeRelease(m_pVB); //이거 
}

void cFrame::Update(int nKeyFrame, D3DXMATRIXA16* pmatParent)
{
//>>:Animation
	
	D3DXMATRIXA16 matR, matT;
	CalcLocalR(nKeyFrame, matR);
	CalcLocalT(nKeyFrame, matT);
	m_matLocalTM = matR *matT;
	
//>>: Animation
	m_matWorldTM = m_matLocalTM;
	if (pmatParent)
	{
		m_matWorldTM *= (*pmatParent);
	}
	for each (auto c in m_vecChild)
		c->Update(nKeyFrame, &m_matWorldTM);
}

void cFrame::Render()
{

	
	if (m_pMtlTex)
	{
		RenderFPS();
		g_pD3DDvice->SetTransform(D3DTS_WORLD, &m_matWorldTM);
		g_pD3DDvice->SetTexture(0, m_pMtlTex->GetTexture());
		g_pD3DDvice->SetMaterial(&m_pMtlTex->GetMaterial());

		g_pD3DDvice->SetFVF(ST_PNT_VERTEX::FVF);
		//그려주기함수를 정점으로하는 그리기.
		/* 이부분
		g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		                              m_vecVertex.size() / 3,
		                              &m_vecVertex[0], sizeof(ST_PNT_VERTEX));
		                                */

		                        
		/*버텍스 버퍼로 그리기 
		g_pD3DDvice->SetStreamSource(0,
			m_pVB,
			0,
			sizeof(ST_PNT_VERTEX));

		g_pD3DDvice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,m_nNumTri );// List로불를거고 , 스타트인덱스값 내가정할수있지만 왠만하면 0으로부터 시작할거야 , 삼각형 갯수
		*/

		/*인덱스 버퍼로 그리기*/
		g_pD3DDvice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PNT_VERTEX));
		g_pD3DDvice->SetIndices(m_pIB);
		g_pD3DDvice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,0,0, m_vecVertex.size(),0, m_vecVertex.size()/3);
	
		
	}
	for each (auto c in m_vecChild)
		c->Render();
}

void cFrame::AddChild(cFrame* pChild)
{
	m_vecChild.push_back(pChild);
}

void cFrame::Destroy()
{
	for each (auto c in m_vecChild)
		c->Destroy();

	this->Release();
}

void cFrame::CalcOriginLocalTM(D3DXMATRIXA16* pmatParent)
{
	m_matLocalTM = m_matWorldTM;
	if (pmatParent)
	{
		D3DXMATRIXA16 matInvParent;
		D3DXMatrixInverse(&matInvParent, nullptr, pmatParent);
		m_matLocalTM = m_matWorldTM * matInvParent;
	}
	for each (auto c in m_vecChild)
		c->CalcOriginLocalTM(&m_matWorldTM);
}

void cFrame::CalcLocalT(int nKeyFrame, D3DXMATRIXA16& matT)
{
	D3DXMatrixIdentity(&matT);
	if(m_vecPosTrack.empty())
	{
		matT._41 = m_matLocalTM._41;//4행에있는것들이 위치값이잖아?
		matT._42 = m_matLocalTM._42;
		matT._43 = m_matLocalTM._43;
		return;
	}
	
	if(nKeyFrame <= m_vecPosTrack.front().n)
	{
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;//범위벗어나면 양끝단애있는애들로 배치해버린다는 이야기야 . 
	}

	if(nKeyFrame >= m_vecPosTrack.back().n)
	{
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return; //범위벗어나면 양끝단애있는애들로 배치해버린다는 이야기야 . 두개
	}

	int nNextIndex = 0;
	//그사이에 있는경우 .
	for(size_t i = 0 ; i < m_vecPosTrack.size(); i++)
	{
		
		if(nKeyFrame < m_vecPosTrack[i].n)
		{
			/*작으면 앞에거까 현재고 그다음거가 되잖아 사진찎듯이 되있는거거든 만화애니메이션이 다그려져있는게 아니잖아 . 안그려져있는부분을
			 *100 일때 /   150일때\   130 부분 계산을 하는거야  지금이 130이란말이지  그사이에서 비율적으로 계산해서 100이나 150을 불러오는거야
			 *포지션은 어때 그냥 위치가 이동되니까 선형으로 이동하면되는거야 . 한쪽발만 표현해보자 ./ \(100 , 200)  애가 이렇게걸어가는데 딱
			 *150에 걸쳤어 회전에관해서 이렇게하면안되  왜? 다리가짧아져 포지션을 선형으로 갔다가 되 근데 회전은 구형으로 계산해야해 . 그에 관련된 공식을찾아서
			 *지금 애니메이션은 위아래로 이동이 발생할거야 .
			 *애니메이션은 선형을 갔다가 포지션을 이동시키고 다리회전은 구형을갔다가 계산하는거야. 
			 */

			
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;
	float t = (nKeyFrame - m_vecPosTrack[nPrevIndex].n) / (float)(m_vecPosTrack[nNextIndex].n - m_vecPosTrack[nPrevIndex].n);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].v, &m_vecPosTrack[nNextIndex].v, t);//얘는 선형보간

	matT._41 = v.x;
	matT._42 = v.y;
	matT._43 = v.z;
}

void cFrame::CalcLocalR(int nKeyFrame, D3DXMATRIXA16& matR)
{
	D3DXMatrixIdentity(&matR);
	if(m_vecRotTrack.empty())
	{
		matR = m_matLocalTM;
		matR._41 = 0.0f;
		matR._42 = 0.0f;
		matR._43 = 0.0f;
		return;
	}
	//우리가 기록하고있는
	if(nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}
	//만약에 크다구하면 back보다
	if (nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nNextIndex = 0;
	//그사이에 있는경우 .
	for (size_t i = 0; i < m_vecRotTrack.size(); i++)
	{

		if (nKeyFrame < m_vecRotTrack[i].n)
		{
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;
	float t = (nKeyFrame - m_vecRotTrack[nPrevIndex].n) / (float)(m_vecRotTrack[nNextIndex].n - m_vecRotTrack[nPrevIndex].n);
	//여긴 n이맞구나 데이터는 q고
	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrevIndex].q , &m_vecRotTrack[nNextIndex].q , t);//얘는 구형보간
	D3DXMatrixRotationQuaternion(&matR, &q); 
	
}

int cFrame::GetKeyFrame()
{
	//지금은내가 계속움직이게할거거든 특정프레임만쓰고싶다하면은 그때 해당하는 위치의 값들마다 지정을 따로해줘야해

	int first = m_dwFirstFrame * m_dwTicksPerFrame;
	int last = m_dwLastFrame * m_dwTicksPerFrame;

	return GetTickCount() % (last - first) + first; //first가 0부터 시작이아니잖아 
}

void cFrame::RenderFPS()
{
	static DWORD frameCount = 0;            //프레임 카운트수
	static float timeElapsed = 0.0f;            //흐른 시간
	static DWORD lastTime = GetTickCount();   //마지막 시간(temp변수)

	DWORD curTime = GetTickCount();      //현재 시간
	float timeDelta = (curTime - lastTime)*0.001f;        //timeDelta(1번생성후 흐른 시간) 1초단위로 바꿔준다.

	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)         //흐른시간이 1초이상이면 내가 하고싶은것 처리
	{
		float fps = (float)frameCount / timeElapsed;
		cout <<"버텍스 초당 버퍼:" <<fps << endl;

		frameCount = 0;
		timeElapsed = 0.0f;
	}


	lastTime = curTime;
}

void cFrame::BuildVB(vector<ST_PNT_VERTEX>& vecVertex)
{

	/* 버텍스버퍼*/
	m_nNumTri = vecVertex.size() / 3;
	//버텍스를 순서대로 락하고 넣어주는거 까지 여기서할거야
	g_pD3DDvice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	//이제 메모리를 잠가보자

	ST_PNT_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0); //락을걸고
	//데이터를 옮겨줘
	//memecpy가 위험한게 연속적인 데이터라는 증거가 있어야해
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();
	//이제됬으 그려주는부분만해주면되


	
	/*인덱스버퍼*/
	
	WORD* pI = NULL;
	vector<WORD> vecWordIndex;
	for (int i = 0; i < vecVertex.size(); i++)
		vecWordIndex.push_back(i);

	g_pD3DDvice->CreateIndexBuffer(vecWordIndex.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB,NULL);
	
	m_pIB->Lock(0,0, (LPVOID*)& pI,0);
	memcpy(pI, &vecWordIndex[0], vecWordIndex.size() * sizeof(WORD));
	m_pIB->Unlock();



	
	
}
