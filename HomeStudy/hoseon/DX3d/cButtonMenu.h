#pragma once
#include "cButton.h"
class cButton;

class cSpriteNode;

class cButtonMenu :
	public cButton
{
	enum
	{
		EN_BODY = 0 ,EN_OK,EN_CANCEL,EN_EXIT
	};
private:
	


public:
	cButtonMenu();
	~cButtonMenu();

	

	virtual void Setup();
	virtual void Update();
	virtual void Render();
	virtual void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

