#pragma once
class cSkinnedMesh
{
	enum STATE
	{
		Attack = 0, Attack2 = 1, Attack3 = 2 , Walk = 3, Stand =4 , NONE =4
	};
	
public:
	cSkinnedMesh();
	~cSkinnedMesh();
protected:
	LPD3DXFRAME		m_pRoot;
	LPD3DXANIMATIONCONTROLLER	m_pAnimController; //局聪皋捞记 包府且模备

	STATE			m_enState;
	//>>:Blend 捞侩
	float			m_fBlendTime;
	float			m_fPassedBlendTime;
	bool			m_isAnimBlend;
	//<<:Blend
	
public:
	void Setup(char* szFolder, char* szFile);
	void Update();
	void Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent);
	void Render(LPD3DXFRAME pFrame);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	
	void SetupBoneMatrixPtrs(LPD3DXFRAME pFrame);
	void UpdateSkinnedMesh(LPD3DXFRAME pFrame);

	void SetAnimationIndex(int nIndex);

	//>>:Blend
	void SetAnimationIndexBlend(int nIndex);
	void SetAnimation(int state);
	//<:


	float AnimCheck;
	float passed;
	bool Anibool;

};