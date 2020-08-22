#include "stdafx.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

GameScene::GameScene():m_Lose(false)
{
	/*mBlock[0].append(L"..X.");
	mBlock[0].append(L"..X.");
	mBlock[0].append(L"..X.");
	mBlock[0].append(L"..X.");

	mBlock[1].append(L"..X.");
	mBlock[1].append(L".XX.");
	mBlock[1].append(L".X..");
	mBlock[1].append(L"....");

	mBlock[2].append(L".X..");
	mBlock[2].append(L".XX.");
	mBlock[2].append(L"..X.");
	mBlock[2].append(L"....");

	mBlock[3].append(L"....");
	mBlock[3].append(L".XX.");
	mBlock[3].append(L".XX.");
	mBlock[3].append(L"....");

	mBlock[4].append(L"....");
	mBlock[4].append(L".XX.");
	mBlock[4].append(L"..X.");
	mBlock[4].append(L"..X.");


	mBlock[5].append(L"....");
	mBlock[5].append(L".XX.");
	mBlock[5].append(L"..X.");
	mBlock[5].append(L"..X.");

	mBlock[6].append(L"..X.");
	mBlock[6].append(L".XX.");
	mBlock[6].append(L"..X.");
	mBlock[6].append(L"....");*/

	//m_bitMap_Blocks = LoadBitmap(GameCenter::GetInstance()->getHInstance(), MAKEINTRESOURCE());
	m_block = new Block;
}

GameScene::~GameScene()
{
}

void GameScene::Init(void)
{
	ZeroMemory(mMap, HEIGHT * WIDTH); //memset 0으로 매크로
	m_block->Init();
	//m_rcLocal_borderLine = { m_rcclient.left + 200 - 1,m_rcclient.top + 50,m_rcclient.left + 800 + 1,m_rcclient.top + 950 };

	//벽처리 
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j <WIDTH; j++)
		{
			mMap[i][j] = ( i == 0||j==0 || i==HEIGHT-1 || j==WIDTH-1) ? '#' : '\0'; 
			setPosition({200+(60*j),50+(60*i)}, j, i);
		}
	}
	m_block->CreateBlock();
	for (int i = 0; i < 4; i++)
	{
		mMap[m_block->mPosition[i].y][m_block->mPosition[i].x] = m_block->GetBlockColor();
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
		//MoveBlock();
		break;
	}


	DrawBlcok(hdc);
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

void GameScene::DrawBlcok(HDC hdc)
{
	/*test*/
	//for (int i = 0; i < WIDTH - 2; i++)
	//{
	//	Rectangle(hdc, 200 + (60 * i), 890, 260 + (60 * i), 950);
	//}
	HBITMAP h01Bitmap;
	hBlocks = (HBITMAP)LoadImage(NULL, TEXT("IMG/Block.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	GetObject(hBlocks, sizeof(BITMAP), &bitBlcok);

	hBlocksDc = CreateCompatibleDC(hdc); //똑같이만들어
	h01Bitmap = (HBITMAP)SelectObject(hBlocksDc, hBlocks); //그려주는거야
	//int bx = bitBlcok.bmWidth / 9; //이미지 프레임 가로로 16장
	//int by = bitBlcok.bmHeight / 1; //세로로 2장
	POINT temp;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			switch (mMap[i][j])
			{
			case 'P':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y,0);
				break;
			case 'Y':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y,1);
				break;
			case 'G':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y, 2);
				break;
			case 'S':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y, 3);
				break;
			case 'O':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y, 4);
				break;
			case 'B':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y, 5);
				break;
			case 'R':
				temp = getPosition(j, i);
				TransBlt(hdc, temp.x, temp.y, 6);
				break;
			default:

					break;
			}
		
		}
	}

	SelectObject(hBlocksDc, h01Bitmap);
	DeleteDC(hBlocksDc);
}

void GameScene::TransBlt(HDC hdc ,int x, int y, int Color)
{
	int bx = bitBlcok.bmWidth / 9; //이미지 프레임 가로로 16장
	TransparentBlt(hdc, x, y, bx * 3.7, bitBlcok.bmHeight * 3.7, hBlocksDc, bx * Color, 0, bx, bitBlcok.bmHeight, RGB(255, 0, 255));// 200, 900좌표 bx*1 2번쨰그림

}

void GameScene::MoveBlock()
{
	for (int i = 0; i< 4; i++)
		mMap[m_block->mPosition[i].y][m_block->mPosition[i].x] = '0';

	for (int i = 0; i < 4; i++)
	{
		m_block->mPosition[i].y += 1;
		mMap[m_block->mPosition[i].y][m_block->mPosition[i].x] = m_block->GetBlockColor();
	}
}


