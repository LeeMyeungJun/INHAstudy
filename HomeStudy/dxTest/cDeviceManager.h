#pragma once
#define g_pDeveceManager cDeviceManager::GetInstance()
#define g_pD3DDvice cDeviceManager::GetInstance()->GetDevice()

class cDeviceManager
{
	//public: 1�ܰ� ������� .
	//	cDeviceManager();
	//	~cDeviceManager();

	//2�ܰ�
	Singletone(cDeviceManager);
	//3�ܰ� ���ΰ��Ӳ� �����´� .
private:
	LPDIRECT3D9		m_pD3D;//�� ������ �����ؾ� �������̽� 
	LPDIRECT3DDEVICE9 m_pDevice;//��ģ���� �����Ҽ����� Divece

public:
	LPDIRECT3DDEVICE9	GetDevice();
	void Destroy();

};

