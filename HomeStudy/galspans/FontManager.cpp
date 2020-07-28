#include "stdafx.h"



FontManager::FontManager()
{
	TitleFont = CreateFont(FONT_TITLE_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1�ƻ������ R");
	CommonFont = CreateFont(FONT_COMMON_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"���׷�ü");

	LineBrush = CreateSolidBrush(RGB(255, 0, 0)); //������
	BlockBrush = CreateSolidBrush(RGB(192, 192, 192)); //���ȸ��
	BasicBrush = CreateSolidBrush(RGB(0, 0, 0)); //������

}


FontManager::~FontManager()
{
	DeleteObject(LineBrush);
	DeleteObject(BlockBrush);
	DeleteObject(BasicBrush);
}
