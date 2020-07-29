#pragma once

class BitMap;
class PlayerManager;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 800

class GameScene : public Scene
{
private:
	POINT ptPotion; //±∏∏€∂’±‚øÎµµ.
public:
	GameScene();
	~GameScene();


	PlayerManager * m_Player;
	BitMap * m_Bitmap;

	std::vector<POINT> vecPolygon;
	std::vector<POINT> vecTemp;


	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);

	void PlayerMove(UINT message);
	bool PlayerInsideCheck();
	
	HBITMAP hOldBitmap;
	HBITMAP hNewBitmap;
	

	bool bLand[SCREEN_WIDTH][SCREEN_HEIGHT]; //∏‘¿∫∂•¿∫ true∑Œ «ÿ¡›Ω√¥Ÿ.
	
};

