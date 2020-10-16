#pragma once
#include "cObject.h"
#include "cMtlTex.h"

class cFrame :
	public cObject
{
public:
	cFrame();
	~cFrame();
private:
Synthesize_Pass_by_Ref(vector<ST_PNT_VERTEX>, m_vecVertex, Vertex);
Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matLocalTM, LocalTM);
Synthesize_Pass_by_Ref(D3DXMATRIXA16, m_matWorldTM, WorldTM);
Synthesize_Add_Ref(cMtlTex*, m_pMtlTex, MtlTex);
	vector<cFrame*> m_vecChild;
	//>>:Anim
	Synthesize_Pass_by_Ref(vector<ST_POS_SAMPLE>, m_vecPosTrack, PosTrack);
	Synthesize_Pass_by_Ref(vector<ST_ROT_SAMPLE>, m_vecRotTrack, RotTrack );//회전에 관련된 데이타중에보게되면 
	//<<:
public:
	void Update(int KeyFrame, D3DXMATRIXA16* pmatParent);
	void Render();
	void AddChild(cFrame* pChild);
	void Destroy();
	void CalcOriginLocalTM(D3DXMATRIXA16* pmatParent);
	//>>:Animation
	void CalcLocalT(IN int nKeyFrame, OUT D3DXMATRIXA16& matT);
	void CalcLocalR(IN int nKeyFrame, OUT D3DXMATRIXA16& matR);

	DWORD		m_dwFirstFrame;
	DWORD		m_dwLastFrame;
	DWORD		m_dwFrameSpeed;
	DWORD		m_dwTicksPerFrame;

	int GetKeyFrame();
	//<<:


	//>>:FPS
	void RenderFPS();

	//>>:버텍스값으로 버텍스 버퍼를 만들거야
private:
	int		m_nNumTri;
	LPDIRECT3DVERTEXBUFFER9		m_pVB; //버텍스버퍼구
	LPDIRECT3DINDEXBUFFER9		m_pIB; //인덱스버퍼
public:
	void BuildVB(vector<ST_PNT_VERTEX>& vecVertex); //그거 버텍스버퍼 넣어줄함수
	//<<:

	
};
