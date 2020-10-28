#pragma once
#include "cButton.h"
class cButton;

class cSpriteNode;

class cButtonMenu :
	public cButton
{


public:
	cButtonMenu();
	~cButtonMenu();

	

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

