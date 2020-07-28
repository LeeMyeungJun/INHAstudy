#pragma once

class BitMap;
//class Player;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 800

class GameScene : public Scene
{

public:
	GameScene();
	~GameScene();

	
	BitMap * m_Bitmap;
	std::vector<POINT> vecPolygon;
	//Player * player;


	POINT ptPotion;

	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);

	
	HBITMAP hOldBitmap;
	HBITMAP hNewBitmap;
	

	bool bLand[SCREEN_WIDTH][SCREEN_HEIGHT] = {false}; //∏‘¿∫∂•¿∫ true∑Œ «ÿ¡›Ω√¥Ÿ.
	
};

