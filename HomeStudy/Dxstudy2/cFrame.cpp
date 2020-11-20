#include "stdafx.h"
#include "cFrame.h"


cFrame::cFrame()
	: m_pMtlTex(nullptr)
	, m_pVB(NULL) //�̰Ŷ�
	, m_nNumTri(0) //�̰Ŷ�
{
	D3DXMatrixIdentity(&m_matLocalTM);
	D3DXMatrixIdentity(&m_matWorldTM);
}


cFrame::~cFrame()
{
	SafeRelease(m_pMtlTex);
	SafeRelease(m_pVB); //�̰� 
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
		//�׷��ֱ��Լ��� ���������ϴ� �׸���.
		/* �̺κ�
		g_pD3DDvice->DrawPrimitiveUP(D3DPT_TRIANGLELIST,
		                              m_vecVertex.size() / 3,
		                              &m_vecVertex[0], sizeof(ST_PNT_VERTEX));
		                                */

		                        
		/*���ؽ� ���۷� �׸��� 
		g_pD3DDvice->SetStreamSource(0,
			m_pVB,
			0,
			sizeof(ST_PNT_VERTEX));

		g_pD3DDvice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,m_nNumTri );// List�κҸ��Ű� , ��ŸƮ�ε����� �������Ҽ������� �ظ��ϸ� 0���κ��� �����Ұž� , �ﰢ�� ����
		*/

		/*�ε��� ���۷� �׸���*/
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
		matT._41 = m_matLocalTM._41;//4�࿡�ִ°͵��� ��ġ�����ݾ�?
		matT._42 = m_matLocalTM._42;
		matT._43 = m_matLocalTM._43;
		return;
	}
	
	if(nKeyFrame <= m_vecPosTrack.front().n)
	{
		matT._41 = m_vecPosTrack.front().v.x;
		matT._42 = m_vecPosTrack.front().v.y;
		matT._43 = m_vecPosTrack.front().v.z;
		return;//��������� �糡�ܾ��ִ¾ֵ�� ��ġ�ع����ٴ� �̾߱�� . 
	}

	if(nKeyFrame >= m_vecPosTrack.back().n)
	{
		matT._41 = m_vecPosTrack.back().v.x;
		matT._42 = m_vecPosTrack.back().v.y;
		matT._43 = m_vecPosTrack.back().v.z;
		return; //��������� �糡�ܾ��ִ¾ֵ�� ��ġ�ع����ٴ� �̾߱�� . �ΰ�
	}

	int nNextIndex = 0;
	//�׻��̿� �ִ°�� .
	for(size_t i = 0 ; i < m_vecPosTrack.size(); i++)
	{
		
		if(nKeyFrame < m_vecPosTrack[i].n)
		{
			/*������ �տ��ű� ����� �״����Ű� ���ݾ� ���������� ���ִ°Űŵ� ��ȭ�ִϸ��̼��� �ٱ׷����ִ°� �ƴ��ݾ� . �ȱ׷����ִºκ���
			 *100 �϶� /   150�϶�\   130 �κ� ����� �ϴ°ž�  ������ 130�̶�������  �׻��̿��� ���������� ����ؼ� 100�̳� 150�� �ҷ����°ž�
			 *�������� � �׳� ��ġ�� �̵��Ǵϱ� �������� �̵��ϸ�Ǵ°ž� . ���ʹ߸� ǥ���غ��� ./ \(100 , 200)  �ְ� �̷��԰ɾ�µ� ��
			 *150�� ���ƾ� ȸ�������ؼ� �̷����ϸ�ȵ�  ��? �ٸ���ª���� �������� �������� ���ٰ� �� �ٵ� ȸ���� �������� ����ؾ��� . �׿� ���õ� ������ã�Ƽ�
			 *���� �ִϸ��̼��� ���Ʒ��� �̵��� �߻��Ұž� .
			 *�ִϸ��̼��� ������ ���ٰ� �������� �̵���Ű�� �ٸ�ȸ���� ���������ٰ� ����ϴ°ž�. 
			 */

			
			nNextIndex = i;
			break;
		}
	}

	int nPrevIndex = nNextIndex - 1;
	float t = (nKeyFrame - m_vecPosTrack[nPrevIndex].n) / (float)(m_vecPosTrack[nNextIndex].n - m_vecPosTrack[nPrevIndex].n);

	D3DXVECTOR3 v;
	D3DXVec3Lerp(&v, &m_vecPosTrack[nPrevIndex].v, &m_vecPosTrack[nNextIndex].v, t);//��� ��������

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
	//�츮�� ����ϰ��ִ�
	if(nKeyFrame <= m_vecRotTrack.front().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.front().q);
		return;
	}
	//���࿡ ũ�ٱ��ϸ� back����
	if (nKeyFrame >= m_vecRotTrack.back().n)
	{
		D3DXMatrixRotationQuaternion(&matR, &m_vecRotTrack.back().q);
		return;
	}

	int nNextIndex = 0;
	//�׻��̿� �ִ°�� .
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
	//���� n�̸±��� �����ʹ� q��
	D3DXQUATERNION q;
	D3DXQuaternionSlerp(&q, &m_vecRotTrack[nPrevIndex].q , &m_vecRotTrack[nNextIndex].q , t);//��� ��������
	D3DXMatrixRotationQuaternion(&matR, &q); 
	
}

int cFrame::GetKeyFrame()
{
	//���������� ��ӿ����̰��ҰŰŵ� Ư�������Ӹ�����ʹ��ϸ��� �׶� �ش��ϴ� ��ġ�� ���鸶�� ������ �����������

	int first = m_dwFirstFrame * m_dwTicksPerFrame;
	int last = m_dwLastFrame * m_dwTicksPerFrame;

	return GetTickCount() % (last - first) + first; //first�� 0���� �����̾ƴ��ݾ� 
}

void cFrame::RenderFPS()
{
	static DWORD frameCount = 0;            //������ ī��Ʈ��
	static float timeElapsed = 0.0f;            //�帥 �ð�
	static DWORD lastTime = GetTickCount();   //������ �ð�(temp����)

	DWORD curTime = GetTickCount();      //���� �ð�
	float timeDelta = (curTime - lastTime)*0.001f;        //timeDelta(1�������� �帥 �ð�) 1�ʴ����� �ٲ��ش�.

	timeElapsed += timeDelta;

	frameCount++;

	if (timeElapsed >= 1.0f)         //�帥�ð��� 1���̻��̸� ���� �ϰ������ ó��
	{
		float fps = (float)frameCount / timeElapsed;
		cout <<"���ؽ� �ʴ� ����:" <<fps << endl;

		frameCount = 0;
		timeElapsed = 0.0f;
	}


	lastTime = curTime;
}

void cFrame::BuildVB(vector<ST_PNT_VERTEX>& vecVertex)
{

	/* ���ؽ�����*/
	m_nNumTri = vecVertex.size() / 3;
	//���ؽ��� ������� ���ϰ� �־��ִ°� ���� ���⼭�Ұž�
	g_pD3DDvice->CreateVertexBuffer(
		vecVertex.size() * sizeof(ST_PNT_VERTEX),
		0,
		ST_PNT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		NULL);

	//���� �޸𸮸� �ᰡ����

	ST_PNT_VERTEX* pV = NULL;
	m_pVB->Lock(0, 0, (LPVOID*)&pV, 0); //�����ɰ�
	//�����͸� �Ű���
	//memecpy�� �����Ѱ� �������� �����Ͷ�� ���Ű� �־����
	memcpy(pV, &vecVertex[0], vecVertex.size() * sizeof(ST_PNT_VERTEX));
	m_pVB->Unlock();
	//�������� �׷��ִºκи����ָ��


	
	/*�ε�������*/
	
	WORD* pI = NULL;
	vector<WORD> vecWordIndex;
	for (int i = 0; i < vecVertex.size(); i++)
		vecWordIndex.push_back(i);

	g_pD3DDvice->CreateIndexBuffer(vecWordIndex.size() * sizeof(WORD), 0, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pIB,NULL);
	
	m_pIB->Lock(0,0, (LPVOID*)& pI,0);
	memcpy(pI, &vecWordIndex[0], vecWordIndex.size() * sizeof(WORD));
	m_pIB->Unlock();



	
	
}
