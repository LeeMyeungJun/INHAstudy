#pragma once

class BitMap;
class PlayerManager;
class Monster;

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 800

using namespace std;
class GameScene : public Scene
{
public:
	enum CHECKLINE
	{
		START_LINE,
		END_LINE
	};

	enum STAGE
	{
		STAGE_ONE,
		STAGE_TWO
	};
private:
	POINT ptPotion; //±¸¸Û¶Õ±â¿ëµµ.
public:
	GameScene();
	~GameScene();

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);

	void PlayerMove(UINT message);
	void PlayerFirstDirection(UINT message);
	void PlayerDirectionCheck(UINT message);
	bool LandBorderCheck(int,int);
	bool LandEmptyCheck(int, int);
	void PlayerLineCheck();
	void RebuildLand();
	void DrawBitmapDoubleBuffering(HWND hwnd, HDC hdc);
	void PolygonArea();

	bool PolygonInsideCheck(POINT);


	bool Polygon_Line_Collision(POINT);
	bool Player_Collsion(POINT);
	bool Tail_Collsion(POINT);


	size_t stage;
	bool bOutMoveFlag;
	bool bWin; 
	int arrStartEndCheck[2];
	PlayerManager * m_Player;
	BitMap * m_Bitmap;
	Monster * m_Monster;
	FontManager font;




	std::vector<POINT> vecPolygon;
	std::vector<POINT> vecPoint;
	float fArea;
	int GamePercent;

	HBITMAP hDoubleBufferImage;
	RECT rectView;

	BitMap MapSetting;
	HBITMAP tempImage;
	BITMAP tempBack;

	char arrLand[SCREEN_HEIGHT][SCREEN_WIDTH];//a.Å×µÎ¸® b.³»ºÎ c.¾È¸ÔÀº¶¥ d.²¿¸®

	void nonStaticMonsterUpdate();
	
};

void CALLBACK MonsterUpdate(HWND, UINT, UINT_PTR, DWORD);