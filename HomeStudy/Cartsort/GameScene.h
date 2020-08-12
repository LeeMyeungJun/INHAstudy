#pragma once
class GameScene :public Scene
{
private:
	Scene &wrapped_;
public:
	GameScene(Scene &wrapped) :wrapped_(wrapped) {}
	~GameScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
};

