#pragma once
class BitMap 
{
private:
	HBITMAP hDoubleBufferImage;
	RECT rectView;

	HBITMAP hBackImage;
	BITMAP bitBack;


public:
	BitMap();
	~BitMap();


	void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc);
	void CreateBitmap();
	void DeleteBitmap();

	void init();

};

