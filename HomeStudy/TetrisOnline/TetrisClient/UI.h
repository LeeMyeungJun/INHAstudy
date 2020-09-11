#pragma once
class GameCenter;

class UI
{
public:
	enum FONT_SIZE : size_t
	{
		FONT_GAME_SIZE = 35,
		FONT_TITLE_SIZE = 80,
		FONT_COMMON_SIZE = 30,
		FONT_END_SIZE = 35,
		FONT_MANUAL_SIZE = 40
	};
public:
	HFONT TitleFont;
	HFONT CommonFont;
	HFONT EndFont;
	HFONT GameFont;
	HFONT ManualFont;

	HBRUSH LineBrush;
	HBRUSH BlockBrush;
	HBRUSH BasicBrush;
private:
	//로그인
	const std::wstring m_Title = L"T E T R I S";
	const std::wstring m_LocalBtn = L"1인용";
	const std::wstring m_OnlineBtn = L"온라인";
	//로컬 게임 
	const std::wstring m_Keymanual = L"↑ ← ↓→ SPACEBAR";
	//온라인 게임

	//로비
	const std::wstring m_Room = L"LOBBY  1/5";
	const std::wstring m_RoomMakeBtn = L"방 만들기";

	//게임 
	const std::wstring m_RoomInfo = L"ROOM  1/5";
	const std::wstring m_Ready = L"Ready";

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
	RECT m_rcLocal_borderLine;
	RECT m_rcLocal_NextBlock;
	RECT m_rcLocal_GameBoard;
	RECT m_rcLocal_ExitBtn;
	RECT m_rcLocal_Manual;
	/*ONLINEGAME*/
	RECT m_rcGame_GameBoard;
	RECT m_rcGame_GameBoardPlayer1;
	RECT m_rcGame_GameBoardPlayer2;
	RECT m_rcGame_GameBoardPlayer3;
	RECT m_rcGame_GameBoardPlayer4;
	/*Lobby*/
	RECT m_rcLobby_RoomMake;
	RECT m_rcLobby_ExitBtn;
	RECT m_rcLobby_Room;
	/*Room*/
	RECT m_rcRoom_Info;
	RECT m_rcRoom_ReadyBtn;
	RECT m_rcRoom_ExitBtn;


public:
	/*LOGIN*/
	RECT getRcLogin_LocalBtn() { return m_rcLogin_LocalBtn; }
	RECT getRcLogin_OnlineBtn() { return m_rcLogin_OnlineBtn; }
	RECT getRCLogin_ExitBtn() { return m_rcLogin_ExitBtn; }
	/*LOCALGAME*/
	RECT getRCLocal_ExitBtn() { return m_rcLocal_ExitBtn; }
	/*ONLINEGAME*/
	/*LOBBY*/
	RECT getLobby_RoomMakeBtn() { return m_rcLobby_RoomMake; }
	RECT getLobby_RoomBtn() { return m_rcLobby_Room; }
	RECT getLobby_ExitBtn() { return m_rcLobby_ExitBtn; }
	/*ROOM*/
	RECT getRoom_ReadyBtn() { return m_rcRoom_ReadyBtn; }
	RECT getRoom_ExitBtn() { return m_rcRoom_ExitBtn; }


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
	void LobbyRender(HDC hdc);
	void GameRender(HDC hdc);
	void RoomRender(HDC hdc);
};

