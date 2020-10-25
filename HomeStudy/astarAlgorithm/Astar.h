#pragma once

class Astar
{
private:
	HBRUSH myBrush, oldBrush;

	TCHAR tchText[30];
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





	static Astar* GetInstance()
	{
		static Astar instance;
		return &instance;
	}


	
};

