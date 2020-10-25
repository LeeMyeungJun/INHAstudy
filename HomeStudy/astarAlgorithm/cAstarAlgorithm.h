#pragma once
class cAstarAlgorithm
{
public:
	cAstarAlgorithm();
	~cAstarAlgorithm();

	void Setup();
	void Update();
	void Render();
	void wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};

