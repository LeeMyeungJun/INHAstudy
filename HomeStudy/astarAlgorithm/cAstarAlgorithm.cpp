#include "stdafx.h"



cAstarAlgorithm::cAstarAlgorithm()
{
}


cAstarAlgorithm::~cAstarAlgorithm()
{
}

void cAstarAlgorithm::Setup()
{
}

void cAstarAlgorithm::Update()
{
}

void cAstarAlgorithm::Render()
{
	Rectangle(g_hdc, SUBWIDTH, SUBWIDTH, BLOCKSIZE*(OMOKLINE - 1) + SUBWIDTH, SUBWIDTH + BLOCKSIZE*(OMOKLINE - 1));
}

void cAstarAlgorithm::wndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
}
