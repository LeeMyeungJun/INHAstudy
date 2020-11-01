#pragma once
struct ST_BONE;

class cSkinnedMesh
{
public:
	cSkinnedMesh();
	~cSkinnedMesh();
	enum ANIMSTATE	animState;
	

protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController;
	
	float			m_fBlend;			//애니메이션 시간보다 짧아야 함
	float			m_fPassedBlendTime;
	bool			m_isAnimBlend;
	
	float				m_fPassedTime;
	DOUBLE				m_dAnimPeriod;
	LPD3DXANIMATIONSET	m_pAnimSet;
	
public:
	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int index);
	void SetAnimationIndexBlend(int nIndex);

	//OBB
private:
	Synthesize(D3DXVECTOR3, m_vMin, Min);
	Synthesize(D3DXVECTOR3, m_vMax, Max);

public:
	cSkinnedMesh(char* szFolder, char* szFileName);
	void Load(char* szFolder, char* szFileName);
	void Destroy();
	void UpdateAndRender();
	void Update(ST_BONE* pCurrent, D3DXMATRIXA16* pmatParent);
	void SetRandomTrackPosition();

	D3DXMATRIXA16 m_matWorldTM;
	void SetTransform(D3DXMATRIXA16* pmat);
	//
};