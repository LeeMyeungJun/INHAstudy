#pragma once
class GameCenter;

class UI
{
public:
	enum FONT_SIZE : size_t
	{
		FONT_GAME_SIZE = 150,
		FONT_TITLE_SIZE = 130,
		FONT_COMMON_SIZE = 30,
		FONT_END_SIZE = 35,
		FONT_MANUAL_SIZE = 40
	};
private:
	HFONT TitleFont;
	HFONT CommonFont;
	HFONT EndFont;
	HFONT GameFont;
	HFONT ManualFont;

	HBRUSH LineBrush;
	HBRUSH BlockBrush;
	HBRUSH BasicBrush;
public:
	//로그인
	const std::wstring m_Title = L"T E T R I S";
	const std::wstring m_LocalBtn = L"1인용";
	const std::wstring m_OnlineBtn = L"온라인";
	//로컬 게임 
	const std::wstring m_Keymanual = L"↑ ← ↓→ SPACEBAR";
	//온라인 게임





	const std::wstring m_Exit = L"나가기";

private:
	RECT m_rcclient;
private:
	/*LOGIN*/
	RECT m_rcLogin_Title;
	RECT m_rcLogin_LocalBtn;
	RECT m_rcLogin_OnlineBtn;
	RECT m_rcLogin_ExitBtn;
	/*LOCALGAME*/
	RECT m_rcLocal_GameBoard;
	RECT m_rcLocal_ExitBtn;
	RECT m_rcLocal_Manual;
	/*ONLINEGAME*/
	RECT m_rcGame_GameBoard;
	RECT m_rcGame_GameBoardPlayer1;
	RECT m_rcGame_GameBoardPlayer2;
	RECT m_rcGame_GameBoardPlayer3;
	RECT m_rcGame_GameBoardPlayer4;




public:
	/*LOGIN*/
	RECT getRcLogin_LocalBtn() { return m_rcLogin_LocalBtn; }
	RECT getRcLogin_OnlineBtn() { return m_rcLogin_OnlineBtn; }
	RECT getRCLogin_ExitBtn() { return m_rcLogin_ExitBtn; }
	/*LOCALGAME*/
	RECT getRCLocal_ExitBtn() { return m_rcLocal_ExitBtn; }
	/*ONLINEGAME*/


private:
	GameCenter* m_gameCenter;
public:
	UI(GameCenter* wrapped);
	~UI();

	void Init();
	void UIRender(HDC hdc);


private:
	void LoginRender(HDC hdc);
	void LocalRender(HDC hdc);
};

