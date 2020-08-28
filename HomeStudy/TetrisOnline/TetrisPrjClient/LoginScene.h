#pragma once
class LoginScene :public Scene
{
public:
	LoginScene();
	~LoginScene();

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);

	void BackGroundDraw(HDC hdc);
	void StartButtonDraw(HDC hdc);
	void OnlineButtonDraw(HDC hdc);

	void TitleDraw(HDC hdc);


	void BtnAnimaition(LPARAM lParam);
private:
	HBITMAP hBackGround;
	BITMAP bitBackground;
	HDC hBackDC;
	RECT clientRect;

	RECT StartBtnRect;
	RECT LobbyBtnRect;
	float m_startBtn_size;
	float m_LobbyBtn_size;

};

