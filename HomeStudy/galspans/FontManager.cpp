#include "stdafx.h"



FontManager::FontManager()
{
	TitleFont = CreateFont(FONT_TITLE_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1훈새마을운동 R");
	CommonFont = CreateFont(FONT_COMMON_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"빙그레체");
	EndFont = CreateFont(FONT_END_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"빙그레체");
	GameFont = CreateFont(FONT_GAME_SIZE, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, L"1훈새마을운동 R");

	LineBrush = CreateSolidBrush(RGB(255, 0, 0)); //빨간색
	BlockBrush = CreateSolidBrush(RGB(192, 192, 192)); //살잒회색
	BasicBrush = CreateSolidBrush(RGB(0, 0, 0)); //검정색

}


FontManager::~FontManager()
{
	DeleteObject(LineBrush);
	DeleteObject(BlockBrush);
	DeleteObject(BasicBrush);
}
