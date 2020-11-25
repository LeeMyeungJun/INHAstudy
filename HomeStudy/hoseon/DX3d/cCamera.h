#pragma once
class cCamera
{
public:
	cCamera();
	~cCamera();

private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;
	D3DXVECTOR3*	m_pvTarget;

	POINT		m_ptPrevMouse;
	bool		m_isMouseButtonDown;
	float		m_fCameraDistance;
	D3DXVECTOR3	m_vCamRotAngle;
	bool*		m_pCheck;

public:
	void Setup(D3DXVECTOR3*	pvTarget, bool* check);
	void Update();

	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	D3DXVECTOR3& GetPosition() { return m_vEye; }
};

