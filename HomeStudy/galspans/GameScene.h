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
	POINT ptPotion; //���۶ձ�뵵.
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

	size_t stage;
	bool bOutMoveFlag;
	bool bDrawFlag; //����� �׽�Ʈ���̿���
	int arrStartEndCheck[2];
	PlayerManager * m_Player;

	BitMap * m_Bitmap;


	std::vector<POINT> vecPolygon;
	std::vector<POINT> vecPoint;
	float fArea;



	HBITMAP hDoubleBufferImage;
	RECT rectView;

	BitMap MapSetting;
	HBITMAP tempImage;
	BITMAP tempBack;

	char arrLand[SCREEN_WIDTH][SCREEN_HEIGHT];//a.�׵θ� b.���� c.�ȸ����� d.����
	
};

