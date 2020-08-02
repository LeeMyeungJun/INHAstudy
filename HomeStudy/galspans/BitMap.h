#pragma once
class BitMap 
{
public:
	BitMap();
	~BitMap();


	void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc);
	void CreateBitmap();
	void DeleteBitmap();

	void init();


	HBITMAP hBackImage1;
	BITMAP bitBack1;

	HBITMAP hBackImage2;
	BITMAP bitBack2;
};

