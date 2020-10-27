#pragma once
class cSkinnedMesh; //질럿을 가져다가 쓸거니까 필요함

class cOBB
{
public:
	cOBB();
	~cOBB();

private:
	D3DXVECTOR3		m_vOricCenterPos;
	D3DXVECTOR3		m_vOriAxisDir[3];

	D3DXVECTOR3		m_vCenterPos;
	D3DXVECTOR3		m_vAxisDir[3];
	float			m_fAxisLen[3]; //박스의 평행한 XX의 길이
	float			m_fAxisHalfLen[3];
	D3DXMATRIXA16	m_matWorldTM;
public:
	void Setup(cSkinnedMesh* pSkinnedMesh);
	void Update(D3DXMATRIXA16* pmatWorld);
	static bool IsCollision(cOBB* pOBB1, cOBB* pOBB2);

	void OBBBOX_Render(D3DCOLOR c);
	
};

