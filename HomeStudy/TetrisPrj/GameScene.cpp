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

	if (m_Lose) //패배했을때
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
	// 좌우 이동
	if (GetAsyncKeyState(VK_LEFT) & 0x8000)
	{
		inputType = eInputType::LEFT;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
	{
		inputType = eInputType::RIGHT;
	}

	// 모양 바꾸기
	if (GetAsyncKeyState(VK_UP) & 0x8000)
	{
		inputType = eInputType::UP;
	}

	// 아래로 내리기
	if (GetAsyncKeyState(VK_DOWN) & 0x8000)
	{
		inputType = eInputType::DOWN;
	}

	// 밑으로 쭉 내리기
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		inputType = eInputType::SPACE;
	}

}

void GameScene::InputProcess()
{
	switch (inputType)
	{
	case eInputType::LEFT: // 왼쪽으로 이동
		break;

	case eInputType::RIGHT: // 오른쪽으로 이동
		break;

	case eInputType::UP: // 모양바꾸는것

		break;

	case eInputType::DOWN: // 아래로 한칸 내림

		break;

	case eInputType::SPACE: // 밑으로 쭉 내림

		break;
	default:
		break;
	}
}

