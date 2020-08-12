#pragma once
class EndScene :public Scene
{

private:
	Scene &wrapped_;
public:
	EndScene(Scene &wrapped) :wrapped_(wrapped) {}
	~EndScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
};

