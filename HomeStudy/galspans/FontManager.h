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

	//�޴�
	const std::wstring m_Title = L"�����Ա�";
	const std::wstring m_StartButton = L"����";
	const std::wstring m_ExitButton = L"����";

	//������
	const std::wstring m_NextStage = L"���� ��������";
	const std::wstring m_EndTitle = L"�й�";


	//����
	const std::wstring m_reStart = L"�ٽ��ϱ�";
	const std::wstring m_reMenu = L"�޴��ΰ���";






};

