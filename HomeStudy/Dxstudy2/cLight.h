#pragma once
class cCubePC;

class cLight
{
private:
	D3DLIGHT9 stLight[3];
	float fspotZ;
	float fRange;
	cCubePC*	m_Spotcube;
	cCubePC*	m_Pointcube;

	
public:
	cLight();
	~cLight();
	void Update();
	void Setup();
	void Render();
	void Set_PointLight();
	void Reset_PointLight();
	void Set_SpotLight();
	void Reset_SpotLight();
	void Set_DirectionLight();
	void KeyInput();
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

