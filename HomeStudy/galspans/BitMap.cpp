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

void BitMap::DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc)
{
	//GetClientRect(hwnd, &rectView);
	//HDC hMemDC;
	//HBITMAP hOldBitmap;
	//int bx = 0, by = 0;
	//HDC hMemDC2;
	//HBITMAP hOldBitmap2;
	//hMemDC = CreateCompatibleDC(hdc);
	//if (hDoubleBufferImage == NULL)
	//	hDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //�ʱ�ȭ�����ش� ó������ �����ŭ
	//hOldBitmap = (HBITMAP)SelectObject(hMemDC, hDoubleBufferImage);
	//hMemDC2 = CreateCompatibleDC(hMemDC);	//�̹��� ������ ����
	//hOldBitmap2 = (HBITMAP)SelectObject(hMemDC2, tempImage); //���� �����ֱ�

	//bx = bitBack1.bmWidth;
	//by = bitBack1.bmHeight;

	//BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY);

	////�������ۺκ� 
	//HBRUSH myBrush, oldBrush;
	//myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 255, 0));
	//oldBrush = (HBRUSH)SelectObject(hMemDC2, myBrush);

	//Rectangle(hMemDC2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	//myBrush = (HBRUSH)CreateSolidBrush(RGB(255, 50, 255));
	//oldBrush = (HBRUSH)SelectObject(hMemDC2, myBrush);

	////Polygon(hMemDC2, &AdapterGameScene->vecPolygon[0], AdapterGameScene->vecPolygon.size());

	////������

	//SelectObject(hMemDC2, hOldBitmap2);
	//StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC2, 0, 0, rectView.right, rectView.bottom, SRCCOPY);
	//DeleteObject(hMemDC2);



	//BitBlt(hdc, 0, 0, rectView.right, rectView.bottom,
	//	hMemDC, 0, 0, SRCCOPY);

	//SelectObject(hMemDC, hOldBitmap);
	//StretchBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, rectView.right, rectView.bottom, SRCCOPY);
	//DeleteDC(hMemDC);



}

void BitMap::CreateBitmap()
{
	//1 �̹�������
	{
		hBackImage1 = (HBITMAP)LoadImage(NULL, TEXT("images/����.bmp"),IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage1, sizeof(BITMAP), &bitBack1);

		hBackImage2 = (HBITMAP)LoadImage(NULL, TEXT("images/fom.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);
		GetObject(hBackImage1, sizeof(BITMAP), &bitBack2);
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
