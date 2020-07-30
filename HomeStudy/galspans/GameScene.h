#pragma once

class BitMap;
class PlayerManager;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 800

class GameScene : public Scene
{
public:
	

	

private:
	POINT ptPotion; //±¸¸Û¶Õ±â¿ëµµ.
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
	void PlayerFirstDirection(UINT message);
	bool LandBorderCheck(int,int);
	bool LandEmptyCheck(int, int);
	void PlayerLineCheck();


	bool bMoveFlag;
	bool bDrawFlag;
	
	HBITMAP hOldBitmap;
	HBITMAP hNewBitmap;
	

	char arrLand[SCREEN_WIDTH][SCREEN_HEIGHT];//a.Å×µÎ¸® b.³»ºÎ c.¾È¸ÔÀº¶¥ d.²¿¸®
	
};

