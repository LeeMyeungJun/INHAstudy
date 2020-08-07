#include "stdafx.h"

extern GameManager * g_GameManager;

BitMap::BitMap()
{
	init();
	CreateBitmap();
	
	//tempImage = hBackImage1;

}


BitMap::~BitMap()
{

}

void BitMap::CreateBitmap()
{
	//1 ���� ���̹�������
	{
		hBackImage1 = (HBITMAP)LoadImage(NULL, TEXT("images/����.bmp"),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage1, sizeof(BITMAP), &bitBack1);

		hBackImage2 = (HBITMAP)LoadImage(NULL, TEXT("images/fom.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage2, sizeof(BITMAP), &bitBack2);
	}

	//�¸� �й� 
	{
		 WinImage = (HBITMAP)LoadImage(NULL, TEXT("images/win.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		 GetObject(WinImage, sizeof(BITMAP), &WinBack);

		 LoseImage = (HBITMAP)LoadImage(NULL, TEXT("images/Lose.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		 GetObject(LoseImage, sizeof(BITMAP), &LoseBack);
	}

}

void BitMap::DeleteBitmap()
{
	DeleteObject(hBackImage1);
}

void BitMap::init()
{
	CreateBitmap();
}
