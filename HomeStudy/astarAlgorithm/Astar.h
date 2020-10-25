#pragma once
class Player;

class Astar
{
public:
	Astar();
	~Astar();

	void Init(void);
	void Update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	bool Distance(const POINT & p1, const POINT & p2);

	static Astar* GetInstance()
	{
		static Astar instance;
		return &instance;
	}


	TCHAR tchText[30];
	
};

