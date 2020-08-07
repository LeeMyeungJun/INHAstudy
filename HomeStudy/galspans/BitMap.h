#pragma once
class BitMap 
{
public:
	BitMap();
	~BitMap();


	
	void CreateBitmap();
	void DeleteBitmap();

	void init();


	HBITMAP hBackImage1;
	BITMAP bitBack1;

	HBITMAP hBackImage2;
	BITMAP bitBack2;

	HBITMAP WinImage;
	BITMAP WinBack;

	HBITMAP LoseImage;
	BITMAP LoseBack;
};

