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

	

private:
	POINT ptPotion; //구멍뚫기용도.
public:
	GameScene();
	~GameScene();


	PlayerManager * m_Player;
	BitMap * m_Bitmap;

	std::vector<POINT> vecPolygon;
	std::vector<POINT> vecPoint;







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



	bool bOutMoveFlag;

	bool bDrawFlag; //지울것 테스트용이였음



	int arrStartEndCheck[2];



	
	HBITMAP hOldBitmap;
	HBITMAP hNewBitmap;
	

	char arrLand[SCREEN_WIDTH][SCREEN_HEIGHT];//a.테두리 b.내부 c.안먹은땅 d.꼬리
	
};

