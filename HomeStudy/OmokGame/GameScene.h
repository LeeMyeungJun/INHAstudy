#pragma once
class GameScene :public Scene
{
private:
	std::vector<POINT> boardPoint;
public:
	GameScene();
	~GameScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void BlackStone(HDC hdc,POINT);
	void WhiteStone(HDC hdc,POINT);


	int Clickx;
	int Clicky;
	TCHAR tcharx[30];
	TCHAR tchary[30];
};

