#pragma once
class Player;

class Astar
{
private:
	HFONT CommonFont;
	HFONT TitleFont;
public:

	struct boardPoint
	{
		int x;
		int y;
	};

	struct ST_Set
	{
		int st_f;
		int st_g;
		int st_h;
	};

	struct Player
	{
		POINT st_position;
	};

public:
	Astar();
	~Astar();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ObstacleCreate(LPARAM);
	bool Distance(const POINT & p1, const POINT & p2);
	void ObstacleStartEndRender(HDC hdc);

	void StartEndPointCreate(LPARAM lParam);
	void Algorithm();




	boardPoint board[19][19];
	HBRUSH myBrush, oldBrush;

	static Astar* GetInstance()
	{
		static Astar instance;
		return &instance;
	}


public:
	bool ClickFlag;
	bool StartFlag;
	bool EndFlag;
	POINT StartEnd[2]; //0 start 1 end 
	//Player *player = nullptr;
	Player player;
	ST_Set setting[19][19];
	POINT tempPt;


	TCHAR tchText[30];
	
};

