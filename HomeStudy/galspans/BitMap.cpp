#include "stdafx.h"

extern GameManager * g_GameManager;

BitMap::BitMap()
{
	init();
	CreateBitmap();
	hDoubleBufferImage = NULL;
	
}


BitMap::~BitMap()
{
}

void BitMap::DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc)
{
	GetClientRect(hwnd, &rectView);

	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx = 0, by = 0;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //�ʱ�ȭ�����ش� ó������ �����ŭ

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);

	hMemDC2 = CreateCompatibleDC(hMemDC);	//�̹��� ������ ����
	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
	bx = bitBack.bmWidth;
	by = bitBack.bmHeight;

	BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
	SelectObject(hMemDC2, hOldBitmap2);
	StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, rectView.right, rectView.bottom, SRCCOPY);
	DeleteObject(hMemDC2);


	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom,
		hMemDC, 0, 0, SRCCOPY);

	SelectObject(hMemDC, hOldBitmap);
	StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, SRCCOPY);









	DeleteDC(hMemDC);

}

void BitMap::CreateBitmap()
{
	//1 �̹�������
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images/����.bmp"),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}

}

void BitMap::DeleteBitmap()
{
	DeleteObject(hBackImage);
}

void BitMap::init()
{
	CreateBitmap();
}
