#include "stdafx.h"



Astar::Astar()
	: myBrush(NULL)
	, oldBrush(NULL)
	, m_BLOCK_COUNT(4)
{
	m_vecBoard.resize(m_BLOCK_COUNT);
	for (int i = 0; i < m_BLOCK_COUNT; i++)
	{
		m_vecBoard[i].resize(m_BLOCK_COUNT);
	}
}


Astar::~Astar()
{
}

void Astar::Init(void)
{
	
}

void Astar::Update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	

}

void Astar::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	switch (message)
	{
	case WM_KEYDOWN:
		{
		Adjustment_Board();
		MouseState();
		
		}
		break;
	case WM_LBUTTONDOWN:
		{
		LClick_Board(lParam,rc);
		}
		break;
	default:
		break;
	}
}


void Astar::Render(HWND hWnd, HDC hdc)
{
	/*myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

	Rectangle(hdc, j*fSize, i*fSize, (j+1)*fSize, (i+1)*fSize);

	SelectObject(hdc, oldBrush);
	DeleteObject(myBrush);*/
	RECT rc;
	GetClientRect(hWnd, &rc);
	Render_Board(hdc,rc);
	Render_State_Board(hdc, rc);


}

void Astar::Free(void)
{
}

//p1이 클릭한위치 p2가 점위치 
bool Astar::Distance(const POINT & p1, const POINT & p2)
{
	double distance;

	distance = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));

	if (p1.x > p2.x && p1.y > p2.y)
	{
		//if (distance > BLOCKSIZE)
			return false;
		return true;
	}

	return false;
}

void Astar::Render_Board(HDC hdc,RECT rc)
{
	Rectangle(hdc, 0, 0,rc.right, rc.bottom);
	for (int i = 1; i < m_BLOCK_COUNT; i++)
	{
		
		/*가로줄*/
		MoveToEx(hdc, 0, (rc.bottom / m_BLOCK_COUNT)*i, NULL);
		LineTo(hdc, rc.right, (rc.bottom / m_BLOCK_COUNT)*i);

		/*세로줄*/
		MoveToEx(hdc, (rc.right / m_BLOCK_COUNT)*i, 0, NULL);
		LineTo(hdc, (rc.right / m_BLOCK_COUNT)*i, rc.bottom);
		
	}
}

void Astar::Adjustment_Board()
{
	bool bInCheck =false;
	if (GetAsyncKeyState('W') & 0x8000)
	{
		m_BLOCK_COUNT++;
		if (m_BLOCK_COUNT > BOARDMAX)
			m_BLOCK_COUNT = BOARDMAX;
		bInCheck = true;
	}
	else if (GetAsyncKeyState('Q') & 0x8000)
	{
		m_BLOCK_COUNT--;
		if (m_BLOCK_COUNT < BOARDMIN )
			m_BLOCK_COUNT = BOARDMIN;
		bInCheck = true;
	}

	if (!bInCheck)
		return;
	else
	{
		BoardManagerInit();
	}

	m_vecBoard.clear();

	m_vecBoard.resize(m_BLOCK_COUNT + 1 );
	for (int i = 0; i < m_BLOCK_COUNT; i++)
	{
		m_vecBoard[i].resize(m_BLOCK_COUNT + 1);
	}
}

void Astar::Render_State_Board(HDC hdc, RECT rc)
{
	for (int i = 0;i < m_BLOCK_COUNT; i++)
	{
		for (int j = 0; j < m_BLOCK_COUNT; j++)
		{
			switch (m_vecBoard[i][j].st)
			{
			case START:
				myBrush = (HBRUSH)CreateSolidBrush(RGB(0, 0, 255));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

				Rectangle(hdc, (rc.right / m_BLOCK_COUNT)*(j), (rc.bottom / m_BLOCK_COUNT)*(i), (rc.right / m_BLOCK_COUNT)*(j+1), (rc.bottom / m_BLOCK_COUNT)*(i+1));
				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
				break;
			case END:
				myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

				Rectangle(hdc, (rc.right / m_BLOCK_COUNT)*(j), (rc.bottom / m_BLOCK_COUNT)*(i), (rc.right / m_BLOCK_COUNT)*(j + 1), (rc.bottom / m_BLOCK_COUNT)*(i + 1));

				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
				break;
			case WALL:
				myBrush = (HBRUSH)CreateSolidBrush(RGB(127, 127, 127));
				oldBrush = (HBRUSH)SelectObject(hdc, myBrush);

				Rectangle(hdc, (rc.right / m_BLOCK_COUNT)*(j), (rc.bottom / m_BLOCK_COUNT)*(i), (rc.right / m_BLOCK_COUNT)*(j + 1), (rc.bottom / m_BLOCK_COUNT)*(i + 1));

				SelectObject(hdc, oldBrush);
				DeleteObject(myBrush);
				break;
			}
		}//>>: for 1
	}//>>:for 2

	
}

void Astar::LClick_Board(LPARAM lParam,RECT rc)
{
	POINT pt;
	pt.x = LOWORD(lParam);
	pt.y = HIWORD(lParam);
	LONG x1, x2;
	LONG y1, y2;

	for (int i = 0; i < m_BLOCK_COUNT; i++)
	{
		for (int j = 0; j < m_BLOCK_COUNT; j++)
		{
			
			x1 = (rc.right / m_BLOCK_COUNT)*(j);
			y1 = (rc.bottom / m_BLOCK_COUNT)*(i);
			x2 = (rc.right / m_BLOCK_COUNT)*(j + 1);
			y2 = (rc.bottom / m_BLOCK_COUNT)*(i + 1);
			if (x1 <= pt.x && y1 <= pt.y && x2 >= pt.x && y2 >= pt.y)
			{
				m_vecBoard[i][j].st = m_Boardmanager.st_enMouseState;
				if (m_Boardmanager.st_enMouseState == START)
				{
					if (m_Boardmanager.st_bStart)
					{
						if (j == m_Boardmanager.st_ptStart.x && i == m_Boardmanager.st_ptStart.y)
							return;
						m_vecBoard[m_Boardmanager.st_ptStart.y][m_Boardmanager.st_ptStart.x].st = NONE;
						m_Boardmanager.st_ptStart = { j,i };
					}
					else
					{
						m_Boardmanager.st_bStart = true;
						m_Boardmanager.st_ptStart = { j,i };
					}

				}
				else if (m_Boardmanager.st_enMouseState == END)
				{
					if (m_Boardmanager.st_bStart)
					{
						if (j == m_Boardmanager.st_ptEnd.x && i == m_Boardmanager.st_ptEnd.y)
							return;
						m_vecBoard[m_Boardmanager.st_ptEnd.y][m_Boardmanager.st_ptEnd.x].st = NONE;
						m_Boardmanager.st_ptEnd = { j,i };
					}
					else
					{
						m_Boardmanager.st_bEnd = true;
						m_Boardmanager.st_ptEnd = { j,i };
					}

				}
			}
		}//>>: for 1
	}//>>:for 2

}

void Astar::MouseState()
{
	if (GetAsyncKeyState('Z') & 0x8000)
	{
		m_Boardmanager.st_enMouseState = WALL;
	}
	else if (GetAsyncKeyState('X') & 0x8000)
	{
		m_Boardmanager.st_enMouseState = START;
	}
	else if (GetAsyncKeyState('C') & 0x8000)
	{
		m_Boardmanager.st_enMouseState = END;
	}
	else if (GetAsyncKeyState('V') & 0x8000)
	{
		m_Boardmanager.st_enMouseState = NONE;
	}
	
	if (GetAsyncKeyState(VK_SPACE) & 0x8000)
	{
		AstartAlgorithms();
	}
}

void Astar::BoardManagerInit()
{
	m_Boardmanager.st_bStart = false;
	m_Boardmanager.st_bEnd = false;
	m_Boardmanager.st_ptEnd = { 0,0 };
	m_Boardmanager.st_ptStart = { 0,0 };
}

void Astar::AstartAlgorithms()
{
	m_OpenList.push_back(m_Boardmanager.st_ptStart);
	m_vecBoard[m_Boardmanager.st_ptStart.y][m_Boardmanager.st_ptStart.x].fgh.st_iG = 0;
	int hX, hY;
	hX = abs(m_Boardmanager.st_ptEnd.x - m_Boardmanager.st_ptStart.x) * 10;//이동비용 가로세로 10 대각 14이라서 10곱함
	hY = abs(m_Boardmanager.st_ptEnd.y - m_Boardmanager.st_ptStart.y) * 10;

	m_vecBoard[m_Boardmanager.st_ptStart.y][m_Boardmanager.st_ptStart.x].fgh.st_iH = hX + hY;
	m_vecBoard[m_Boardmanager.st_ptStart.y][m_Boardmanager.st_ptStart.x].fgh.st_iF = 
		m_vecBoard[m_Boardmanager.st_ptStart.y][m_Boardmanager.st_ptStart.x].fgh.st_iG
		+ m_vecBoard[m_Boardmanager.st_ptStart.y][m_Boardmanager.st_ptStart.x].fgh.st_iH;


	while (true)
	{
		POINT pt;
		int f = 999;
		int temp = 0;
		//오픈리스트에서 가장작은값을찾는다 .
		for (int i = 0; i < m_OpenList.size(); i++)
		{
			if (m_vecBoard[m_OpenList[i].y][m_OpenList[i].x].fgh.st_iF <= f)
			{
				if (m_vecBoard[m_OpenList[i].y][m_OpenList[i].x].fgh.st_iF == f)
				{
					if (m_vecBoard[m_OpenList[i].y][m_OpenList[i].x].fgh.st_iH >= m_vecBoard[pt.y][pt.x].fgh.st_iH)
						continue;
				}
				f = m_vecBoard[m_OpenList[i].y][m_OpenList[i].x].fgh.st_iF; 
				pt = { m_OpenList[i].x ,m_OpenList[i].y };
				temp = i;
			}
		}
		//지우고 클로즈리스트에 넣는다 
		m_OpenList.erase(m_OpenList.begin()+temp);
		m_CloseList.push_back(pt);
		m_vecBoard[pt.y][pt.x].st = CLOSED;

		if (m_Boardmanager.st_ptEnd.x == pt.x && m_Boardmanager.st_ptEnd.y == pt.y)
			break;

		//검사
		POINT ptTemp;
		//위
		ptTemp = pt; ptTemp.y -= 1;
		WallCheck(pt, ptTemp);
		//오른쪽
		ptTemp = pt; ptTemp.x += 1;
		WallCheck(pt, ptTemp);
		//아래
		ptTemp = pt; ptTemp.y += 1;
		WallCheck(pt, ptTemp);
		//왼쪽
		ptTemp = pt; ptTemp.x -= 1;
		WallCheck(pt, ptTemp);
		//대각선들
		
		
	}


}

void Astar::WallCheck(POINT Currentpt, POINT Neighborpt)
{
	//범위안체크
	if (Neighborpt.x < 0 || Neighborpt.y < 0)
		return;

	//클로즈리스트에있느지 체크
	for (int i = 0; i < m_CloseList.size(); i++)
	{
		if (m_CloseList[i].x == Neighborpt.x && m_CloseList[i].y == Neighborpt.y)
			return;
	}

	//벽인지 체크
	if (m_vecBoard[Neighborpt.y][Neighborpt.x].st == WALL)
		return;


	bool bCheck = false;
	//오픈에 이웃노드가 있는지 
	for (int i = 0; i < m_OpenList.size(); i++)
	{
		//없다면
		if (!(m_OpenList[i].x == Neighborpt.x && m_OpenList[i].y == Neighborpt.y))
			bCheck = true;
	}


	if (m_vecBoard[Currentpt.y][Currentpt.x].fgh.st_iG < 10 || bCheck)
	{
		m_OpenList.push_back(Neighborpt);
		m_vecBoard[Neighborpt.y][Neighborpt.x].st = OPEN;
		m_vecBoard[Neighborpt.y][Neighborpt.x].fgh.st_iG = 10;
		int hX, hY;
		hX = abs(m_Boardmanager.st_ptEnd.x - Neighborpt.x) * 10;//이동비용 가로세로 10 대각 14이라서 10곱함
		hY = abs(m_Boardmanager.st_ptEnd.y - Neighborpt.y) * 10;

		m_vecBoard[Neighborpt.y][Neighborpt.x].fgh.st_iH = hX + hY;
		m_vecBoard[Neighborpt.y][Neighborpt.x].fgh.st_iF =
			m_vecBoard[Neighborpt.y][Neighborpt.x].fgh.st_iH
			+ m_vecBoard[Neighborpt.y][Neighborpt.x].fgh.st_iG;
		m_vecBoard[Neighborpt.y][Neighborpt.x].parent = Currentpt;

	}


}

void Astar::CrossWallCheck(POINT Currentpt, POINT Neighborpt)
{
}

