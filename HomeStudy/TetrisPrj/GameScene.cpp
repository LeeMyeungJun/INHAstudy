#include "stdafx.h"



GameScene::GameScene():m_Lose(false)
{
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	ZeroMemory(mMap, HEIGHT * WIDTH);

}

void GameScene::Update(UINT message, WPARAM wParam, LPARAM lParam)
{
	InputProcess();

	if (m_Lose) //�й�������
		return;

	switch (message)
	{
	case WM_LBUTTONDOWN:
		ClickEvent(lParam);
		break;
	case WM_KEYDOWN:
		Input();
		break;
	default:
		break;
	}

	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:

		break;
	}

	

}

void GameScene::Render(HWND hWnd, HDC hdc)
{
	GameCenter::GetInstance()->getUI()->UIRender(hdc);
	UI(hdc);
}

void GameScene::Free(void)
{
}

void GameScene::UI(HDC hdc)
{

	switch (GameCenter::GetInstance()->getScene())
	{
	case GameCenter::Scene_enum::GAME_SCENE:

		break;
	case GameCenter::Scene_enum::LOCALGAME_SCENE:

		break;
	}

}

void GameScene::ClickEvent(LPARAM lParam)
{
	int Clickx = LOWORD(lParam);
	int Clicky = HIWORD(lParam);

	if (GameCenter::GetInstance()->getScene() == GameCenter::Scene_enum::LOCALGAME_SCENE)
	{
		if (Clickx >= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().left &&Clickx <= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().right
			&& Clicky >= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().top && Clicky <= GameCenter::GetInstance()->getUI()->getRCLocal_ExitBtn().bottom)
		{
			GameCenter::GetInstance()->SceneChange(GameCenter::Scene_enum::LOGIN_SCENE);
		}
	}
	else if (GameCenter::GetInstance()->getScene() == GameCenter::Scene_enum::GAME_SCENE)
	{

	}
}

void GameScene::Input()
{
	// �¿� �̵�
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		inputType = eInputType::LEFT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		inputType = eInputType::RIGHT;
	}

	// ��� �ٲٱ�
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		inputType = eInputType::UP;
	}

	// �Ʒ��� ������
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		inputType = eInputType::DOWN;
	}

	// ������ �� ������
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		inputType = eInputType::SPACE;
	}

}

void GameScene::InputProcess()
{
	switch (inputType)
	{
	case eInputType::LEFT: // �������� �̵�
		break;

	case eInputType::RIGHT: // ���������� �̵�
		break;

	case eInputType::UP: // ���ٲٴ°�

		break;

	case eInputType::DOWN: // �Ʒ��� ��ĭ ����

		break;

	case eInputType::SPACE: // ������ �� ����

		break;
	default:
		break;
	}
}

