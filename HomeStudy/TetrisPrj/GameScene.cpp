#include "stdafx.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

GameScene::GameScene():m_Lose(false)
{
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");
	tetromino[0].append(L"..X.");

	tetromino[1].append(L"..X.");
	tetromino[1].append(L".XX.");
	tetromino[1].append(L".X..");
	tetromino[1].append(L"....");

	tetromino[2].append(L".X..");
	tetromino[2].append(L".XX.");
	tetromino[2].append(L"..X.");
	tetromino[2].append(L"....");

	tetromino[3].append(L"....");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L".XX.");
	tetromino[3].append(L"....");

	tetromino[4].append(L"....");
	tetromino[4].append(L".XX.");
	tetromino[4].append(L"..X.");
	tetromino[4].append(L"..X.");

	tetromino[5].append(L"....");
	tetromino[5].append(L".XX.");
	tetromino[5].append(L"..X.");
	tetromino[5].append(L"..X.");

	tetromino[6].append(L"..X.");
	tetromino[6].append(L".XX.");
	tetromino[6].append(L"..X.");
	tetromino[6].append(L"....");
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	ZeroMemory(mMap, HEIGHT * WIDTH); //memset 0으로 매크로


	//벽처리 
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j <WIDTH; j++)
		{
			mMap[i][j] = ( i == 0||j==0 || i==HEIGHT-1 || j==WIDTH-1) ? '#' : '0'; 
		}
	}


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
	//	m_rcLocal_borderLine = { m_rcclient.left + 200,m_rcclient.top + 20,m_rcclient.left + 1100,m_rcclient.top + 1000 };

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

int GameScene::Rotate(int px, int py, int r)
{
	switch (r % 4)
	{
	case 0: return py * 4 + px; //0 degrees
	case 1: return 12 + py - (px * 4); //0 degrees
	case 2: return 15 - (py * 4) - px; //0 degrees
	case 3: return 3 - py  + (4* px); //0 degrees

	
	}
	return 0;
}


