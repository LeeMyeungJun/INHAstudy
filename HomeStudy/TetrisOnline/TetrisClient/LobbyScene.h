#pragma once


class LobbyScene :public Scene
{
private:


private:
	HBITMAP hBackGround;
	BITMAP bitBackground;
	HDC hBackDC;
	

	RECT ExitBtn;
	RECT RoomMakeBtn;
	RECT UnderChatRect;
	RECT UserChatRect;
	RECT CrateRoomBtn;
	RECT RoomMakeExitBtn;


	bool m_ExitBtn_size;
	bool m_RoomBtn_size;

	bool m_CreateRoom;


public:
	LobbyScene();
	~LobbyScene();

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);

private:
	void BtnAnimaition(LPARAM lParam);
	void LobbyUserCall();



	void BackGroundDraw(HDC hdc);
	void ChattingDraw(HDC hdc);
	void LobbyRoomDraw(HDC hdc);
	void LobbyUserBoardDraw(HDC hdc);
	void ExitBtnDraw(HDC hdc);
	void RoomCreateBtnDraw(HDC hdc);
	void RoomCreateDraw(HDC hdc);
	void ChatDraw(HDC hdc);
	void InputProcess(WPARAM wParam);


};

