#pragma once
class FontManager
{
	enum FONT_SIZE : size_t
	{
		FONT_GAME_SIZE = 150,
		FONT_TITLE_SIZE = 72,
		FONT_COMMON_SIZE = 48,
		FONT_END_SIZE = 35,
		FONT_MANUAL_SIZE = 18
	};


public:
	FontManager();
	~FontManager();

	HFONT TitleFont;
	HFONT CommonFont;
	HFONT EndFont;
	HFONT GameFont;
	HFONT ManualFont;

	HBRUSH LineBrush;
	HBRUSH BlockBrush;
	HBRUSH BasicBrush;

	//메뉴
	const std::wstring m_Title = L"땅따먹기";
	const std::wstring m_StartButton = L"시작";
	const std::wstring m_ExitButton = L"종료";
	const std::wstring m_Manual = L"조작키: 방향키 스페이스바 50퍼센트 먹기. 2탄까지";

	//게임중
	const std::wstring m_NextStage = L"다음 스테이지";
	const std::wstring m_EndTitle = L"패배";

	//종료
	const std::wstring m_reStart = L"다시하기";
	const std::wstring m_reMenu = L"메뉴로가기";






};

