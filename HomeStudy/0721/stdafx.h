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
//		HDoubleBufferImage = CreateCompatibleBitmap(hdc, rectView.right, rectView.bottom); //화면영역만큼 만들엇음
//
//	}
//	h01Bitmap = (HBITMAP)SelectObject(hMemDC, HDoubleBufferImage); //화면영역크기만큼 그려둠.
//																   //1번쨰 그림넣기
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC); //똑같이만들어
//		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hBackImage); //그려주는거야
//		bx = bitBack.bmWidth;
//		by = bitBack.bmHeight;
//
//		BitBlt(hMemDC, 0, 0, bx, by, hMemDC2, 0, 0, SRCCOPY); //배경에 미리그려줌.
//
//		SelectObject(hMemDC2, h01Bitmap2);
//		DeleteDC(hMemDC2);
//	}
//	//2번째꺼 색지우기
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC); //똑같이만들어
//		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hTransParentImage); //그려주는거야
//		bx = bitTransparent.bmWidth;
//		by = bitTransparent.bmHeight;
//
//		BitBlt(hMemDC, 100, 100, bx, by, hMemDC2, 0, 0, SRCCOPY); // 이게일반그리기
//		TransparentBlt(hMemDC, 200, 100, bx, by, hMemDC2, 0, 0, bx, by, RGB(255, 0, 255));//분홍색을 제외하고 출력을한다.
//		SelectObject(hMemDC2, h01Bitmap2);
//		DeleteDC(hMemDC2);
//	}
//	//3번째 애니메이션
//	{
//		hMemDC2 = CreateCompatibleDC(hMemDC); //똑같이만들어
//		h01Bitmap2 = (HBITMAP)SelectObject(hMemDC2, hAniImage); //그려주는거야
//
//
//		bx = bitAni.bmWidth / 6; //이미지 프레임 가로로 6장
//		by = bitAni.bmHeight / 8; //세로로 2장
//
//		int xStart = cur_Frame * bx;
//		int yStart = Position *by;
//
//		TransparentBlt(hMemDC, moveX, moveY, bx * 4, by * 4, hMemDC2, xStart, yStart, bx, by, RGB(255, 0, 255));// bx*4 ,by*4 는 4배한것.
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
