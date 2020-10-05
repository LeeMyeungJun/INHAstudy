#pragma once
#define g_pDeveceManager cDeviceManager::GetInstance()
#define g_pD3DDvice cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
	//public: 1단계 다지운다 .
	//	cDeviceManager();
	//	~cDeviceManager();

	//2단계
	Singletone(cDeviceManager);
	//3단계 메인게임꺼 가져온다 .
private:
	LPDIRECT3D9		m_pD3D;//얘 정보를 설정해야 인터페이스 
	LPDIRECT3DDEVICE9 m_pDevice;//이친구를 설정할수있음 Divece

public:
	LPDIRECT3DDEVICE9	GetDevice();
	void Destroy();

};

