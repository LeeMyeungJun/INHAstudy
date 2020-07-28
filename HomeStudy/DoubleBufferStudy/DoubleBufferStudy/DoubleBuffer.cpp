#include "stdafx.h"
#include "DoubleBuffer.h"


DoubleBuffer::DoubleBuffer()
{
	CreateBitmap();
	hDoubleBufferImage = NULL;
}


DoubleBuffer::~DoubleBuffer()
{
	DeleteBitmap();
}

void DoubleBuffer::DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc)
{
	GetWindowRect(hwnd, &rectView);

	HDC hMemDC;
	HBITMAP hOldBitmap;
	int bx = 0, by = 0;

	HDC hMemDC2;
	HBITMAP hOldBitmap2;

	hMemDC = CreateCompatibleDC(hdc);
	if (hDoubleBufferImage == NULL)
		hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //초기화를해준다 처음들어가면 사이즈만큼

	hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage); //못읽음 

	hMemDC2 = CreateCompatibleDC(hMemDC);	//이미지 찢어짐 방지
	hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage);
	bx = bitBack.bmWidth;
	by = bitBack.bmHeight;

	BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);
	SelectObject(hMemDC2, hOldBitmap2);
	DeleteObject(hMemDC2);


	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom,
		hMemDC, 0, 0, SRCCOPY);
	SelectObject(hMemDC, hOldBitmap);

	DeleteDC(hMemDC);
}

void DoubleBuffer::CreateBitmap()
{
	{
		hBackImage = (HBITMAP)LoadImage(NULL, TEXT("images\\fom.bmp"), IMAGE_BITMAP,
			0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage, sizeof(BITMAP), &bitBack);
	}
}

void DoubleBuffer::DeleteBitmap()
{
	DeleteObject(hBackImage);
	//DeleteObject(hTransparentImage);
	//DeleteObject(hAniImage);
}


