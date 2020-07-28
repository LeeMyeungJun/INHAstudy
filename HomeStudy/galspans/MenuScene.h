#pragma once



class MenuScene : public Scene
{
public:
	MenuScene();
	virtual ~MenuScene();

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);

	RECT m_rc_Title_Btn;
	RECT m_rc_Start_Btn;
	RECT m_rc_Exit_Btn;


};

