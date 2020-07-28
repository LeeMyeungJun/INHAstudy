#pragma once
class DoubleBuffer
{
public:
	DoubleBuffer();
	~DoubleBuffer();

	void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc);
	void CreateBitmap();
	void DeleteBitmap();


public:
	HBITMAP hDoubleBufferImage;
	RECT rectView;


	HBITMAP hBackImage;
	BITMAP bitBack;



};

