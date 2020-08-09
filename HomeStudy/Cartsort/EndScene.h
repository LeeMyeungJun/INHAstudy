#pragma once
class EndScene :public Scene
{
public:
	EndScene();
	~EndScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
};

