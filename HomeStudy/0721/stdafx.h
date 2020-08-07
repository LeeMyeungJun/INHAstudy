// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>




//
//
//void DrawBitMapDoubleBuffering(HWND hWnd, HDC hdc)
//{
//	HDC hMemDC;
//	HBITMAP h01Bitmap;
//	int bx, by;
//
//
//
//	HDC hMemDC2;
//	HBITMAP h01Bitmap2;
//
//	hMemDC = CreateCompatibleDC(hdc);
//
//	if (HDoubleBufferImage == NULL)
//	{
//		HDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //ȭ�鿵����ŭ �������
//
//	}
//	h01Bitmap = (HBITMAP)SelectObject(hMemDC, HDoubleBufferImage); //ȭ�鿵��ũ�⸸ŭ �׷���.
//																   //1���� �׸��ֱ�
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC); //�Ȱ��̸����
//		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage); //�׷��ִ°ž�
//		bx = bitBack.bmWidth;
//		by = bitBack.bmHeight;
//
//		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY); //��濡 �̸��׷���.
//
//		SelectObject(hMemDC2, h01Bitmap2);
//		DeleteDC(hMemDC2);
//	}
//	//2��°�� �������
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC); //�Ȱ��̸����
//		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransParentImage); //�׷��ִ°ž�
//		bx = bitTransparent.bmWidth;
//		by = bitTransparent.bmHeight;
//
//		BitBlt(hMemDC, 100, 100, bx, by, hMemDC2, 0, 0, SRCCOPY); // �̰��Ϲݱ׸���
//		TransparentBlt(hMemDC, 200, 100, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));//��ȫ���� �����ϰ� ������Ѵ�.
//		SelectObject(hMemDC2, h01Bitmap2);
//		DeleteDC(hMemDC2);
//	}
//	//3��° �ִϸ��̼�
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC); //�Ȱ��̸����
//		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage); //�׷��ִ°ž�
//
//
//		bx = bitAni.bmWidth / 6; //�̹��� ������ ���η� 6��
//		by = bitAni.bmHeight / 8; //���η� 2��
//
//		int xStart = cur_Frame * bx;
//		int yStart = Position *by;
//
//		TransparentBlt(hMemDC, moveX, moveY, bx * 4, by * 4, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 �� 4���Ѱ�.
//		SelectObject(hMemDC2, h01Bitmap2);
//		DeleteDC(hMemDC2);
//	}
//	BitBlt(hdc, 0, 0, rectView.right, rectView.bottom, hMemDC, 0, 0, SRCCOPY);
//	SelectObject(hMemDC, h01Bitmap);
//
//
//
//}
//
//










// TODO: reference additional headers your program requires here
