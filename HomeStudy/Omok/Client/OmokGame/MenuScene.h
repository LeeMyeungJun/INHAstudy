#pragma once
class MenuScene :public Scene
{
private:
	RECT m_rc_Title;
	RECT m_rc_Start;
	RECT m_rc_Exit;

	HFONT TitleFont;
	HFONT CommonFont;
	HFONT EndFont;
	HFONT GameFont;

public:
	MenuScene();
	~MenuScene();


	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	
	const std::wstring m_Title = L"Omok2";
	const std::wstring m_StartButton = L"Start";
	const std::wstring m_ExitButton = L"End";





};

