#pragma once

class Astar
{
private:
	vector<vector<ST_BOARD_STATE>>	m_vecBoard;
	int						m_BLOCK_COUNT;
	ST_BOARD_MANAGER		m_Boardmanager;
	vector<POINT>			m_OpenList;
	vector<POINT>			m_CloseList;


	HBRUSH					myBrush, oldBrush;
	TCHAR					tchText[30];
public:
	Astar();
	~Astar();

	void Init(void);
	void Update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);



public:
	bool Distance(const POINT & p1, const POINT & p2);
	void Render_Board(HDC hdc,RECT rc);
	void Adjustment_Board();
	void Render_State_Board(HDC hdc, RECT rc);
	void LClick_Board(LPARAM lParam,RECT rc);
	void MouseState();
	void BoardManagerInit();
	void AstartAlgorithms();
	void WallCheck(POINT Currentpt ,POINT Neighborpt);
	void CrossWallCheck(POINT Currentpt, POINT Neighborpt);







	static Astar* GetInstance()
	{
		static Astar instance;
		return &instance;
	}


	
};

