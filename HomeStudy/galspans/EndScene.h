#pragma once


class EndScene : public Scene
{
public:
	EndScene();
	~EndScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);

	//RECT n_rc_reStart_btn;
	//RECT m_rc_menu_btn;

};

