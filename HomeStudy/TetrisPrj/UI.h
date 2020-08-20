#pragma once
class GameCenter;

class UI
{
public:
	enum FONT_SIZE : size_t
	{
		FONT_GAME_SIZE = 150,
		FONT_TITLE_SIZE = 130,
		FONT_COMMON_SIZE = 100,
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
	//�α���
	const std::wstring m_Title = L"T E T R I S";
	const std::wstring m_LocalBtn = L"1�ο�";
	const std::wstring m_OnlineBtn = L"�¶���";
	const std::wstring m_Exit = L"Exit";

	////������
	//const std::wstring m_NextStage = L"���� ��������";
	//const std::wstring m_EndTitle = L"�й�";

	////����
	//const std::wstring m_reStart = L"�ٽ��ϱ�";
	//const std::wstring m_reMenu = L"�޴��ΰ���";


private:
	RECT m_rcclient;

	RECT m_rcLogin_Title;
	RECT m_rcLogin_LocalBtn;
	RECT m_rcLogin_OnlineBtn;
	RECT m_rcLogin_ExitBtn;

public:
	RECT getRcLocalBtn() { return m_rcLogin_LocalBtn; }
	RECT getRcOnlineBtn() { return m_rcLogin_OnlineBtn; }
	RECT getRCExitBtn() { return m_rcLogin_ExitBtn; }




private:
	GameCenter* m_gameCenter;
public:
	UI(GameCenter* wrapped);
	~UI();

	void Init();
	void UIRender(HDC hdc);


private:
	void LoginRender(HDC hdc);
};

