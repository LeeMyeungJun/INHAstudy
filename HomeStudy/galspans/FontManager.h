#pragma once
class FontManager
{
	enum FONT_SIZE : size_t
	{
		FONT_TITLE_SIZE = 72,
		FONT_COMMON_SIZE = 48,
		FONT_END_SIZE = 35
	};


public:
	FontManager();
	~FontManager();

	HFONT TitleFont;
	HFONT CommonFont;
	HFONT EndFont;

	HBRUSH LineBrush;
	HBRUSH BlockBrush;
	HBRUSH BasicBrush;

	//메뉴
	const std::wstring m_Title = L"땅따먹기";
	const std::wstring m_StartButton = L"시작";
	const std::wstring m_ExitButton = L"종료";

	//게임중
	const std::wstring m_NextStage = L"다음 스테이지";
	const std::wstring m_EndTitle = L"패배";


	//종료
	const std::wstring m_reStart = L"다시하기";
	const std::wstring m_reMenu = L"메뉴로가기";






};

