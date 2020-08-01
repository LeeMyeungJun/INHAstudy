#pragma once
class BitMap 
{
private:
	HBITMAP hDoubleBufferImage;
	RECT rectView;

	HBITMAP hBackImage1;
	BITMAP bitBack1;

	HBITMAP hBackImage2;
	BITMAP bitBack2;

	HBITMAP tempImage;


public:
	BitMap();
	~BitMap();


	void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc);
	void CreateBitmap();
	void DeleteBitmap();

	void init();

};

