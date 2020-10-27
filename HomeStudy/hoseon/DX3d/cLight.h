#pragma once
class cLight
{
private:
	D3DLIGHT9	m_stLight[3];

	D3DXVECTOR3 m_vDir;
	D3DXVECTOR3 m_vSpotDir;
	
public:
	cLight();
	~cLight();

	void Init();
	void Update();
};

