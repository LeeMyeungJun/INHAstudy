#pragma once

class BitMap;
class PlayerManager;

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
	POINT ptPotion; //구멍뚫기용도.
public:
	GameScene();
	~GameScene();










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


	size_t stage;
	bool bOutMoveFlag;
	bool bWin; //지울것 테스트용이였음
	int arrStartEndCheck[2];
	PlayerManager * m_Player;

	BitMap * m_Bitmap;


	std::vector<POINT> vecPolygon;
	std::vector<POINT> vecPoint;
	float fArea;
	int GamePercent;

	HBITMAP hDoubleBufferImage;
	RECT rectView;

	BitMap MapSetting;
	HBITMAP tempImage;
	BITMAP tempBack;

	char arrLand[SCREEN_HEIGHT][SCREEN_WIDTH];//a.테두리 b.내부 c.안먹은땅 d.꼬리
	
};

