#pragma once
#define WIDTH 16
#define HEIGHT 26

class GameScene :public Scene
{
private:
	int		 m_iLevel;
	bool	 m_GameStart;			
	int		 m_iBlockWidth;		
	int		 m_iCurBlocksType;		
	int		 m_iCurBlocksState;	
	int		 m_iCurBlocksX, m_iCurBlocksY;
	int		 m_iGuideBlocksX, m_iGuideBlocksY;
	int		 m_iGostType;
	int		 m_iGostState;
	int		 m_iGostY;
	int		 m_iNextBlocksType;	
	int		 m_iHoldBlocksType;	
	int		 m_iGameBoard[HEIGHT][WIDTH];			
	int		 m_iTotalClearBlocks;	
	int		 m_iStartClearBlocks;	
	int		 m_iStepClearBlocks;
	int		 m_iAnimation;
	RECT	 m_YesBtn;
	RECT	 m_NoBtn;

	
public:
	GameScene();
	~GameScene();
	HDC hBlocksDc;

	POINT BoardPoint[HEIGHT-1][WIDTH-1];
	POINT NextBlockPosition[4][4];
	POINT GuideBlockPosition[4][4];

	POINT Position[4];
	POINT GuidePosition[4];
	
	HBITMAP hBlocks;
	BITMAP bitBlcok;

	HBITMAP hBackGround;
	BITMAP bitBackground;


public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);
public:
	/*Render*/
	void PrintScore(HDC hdc);
	void PrintLevel(HDC hdc);
	void DrawBlock(HDC hdc);
	void DrawGameOver(HDC hdc);
	void DrawContinue(HDC hdc);
	void DrawContinue2(HDC hdc);
	void DrawContinue3(HDC hdc);
	void DrawBackGround(HDC hdc);

	/*Update*/
	void PositionSave();
	void GuidePositionSave();
	void SetBlockToGameBoard();
	bool CheckCollision();
	bool CheckGuideCollision();
	void GuidBlock();
	void SetGuideBlockToGameBoard();
	void ClearGuideBlocks();
	bool TurnCheckCollision();
	void CreateRandomBlocks();
	bool GameOver();
	void BlockMove();
	void ClearCurBlocks(int x, int y);
	void RotateBlocks();
	void Input();
	void InputProcess(UINT message);
	void LineFullCheck();
	void MoveCollision();
	void BtnAnimaition(LPARAM lParam);

	/*Block Time*/
	void nonStaticUpdate();

public:
	/* ��Ʈ���� ��� ��� �� ���� ����*/
	int m_BlockList[7][4][4][4] = 	// ��� ������ ����: -7, ȸ������(0��, 90��, -180��, -270��),
	{		 				        //...[-4][-4]: ����� ��籸��
		{
			{
				{ 0,0,1,0 },		//     #		 for�� -2���� �̿��Ͽ� ������ ����� �����
				{ 1,1,1,0 },		// # # # 	    ������ �� �ִ�. 0���� �������, 0�� �ƴѰ���
				{ 0,0,0,0 },		//		         �� ����� �ش� ����� ���
				{ 0,0,0,0 }		//
			},
			{
				{ 1,1,0,0 },		//   # #
				{ 0,1,0,0 },		//     #
				{ 0,1,0,0 },		//     #
				{ 0,0,0,0 }
			},
			{
				{ 1,1,1,0 },		//    # # #
				{ 1,0,0,0 },		//    #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 1,0,0,0 },		//    #
				{ 1,0,0,0 },		//    #
				{ 1,1,0,0 },		//    # #
				{ 0,0,0,0 }		//
			}

		},
		{
			{
				{ 2,0,0,0 },		//  #
				{ 2,2,2,0 },		//  # # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,2,0,0 },		//    #
				{ 0,2,0,0 },		//    #
				{ 2,2,0,0 },		//  # #
				{ 0,0,0,0 }		//
			},
			{
				{ 2,2,2,0 },		//# # #
				{ 0,0,2,0 },		//    #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 2,2,0,0 },		//  # #
				{ 2,0,0,0 },		//  #
				{ 2,0,0,0 },		//  #
				{ 0,0,0,0 }		// 
			}
		},
		{
			{
				{ 0,3,0,0 },		//	 #
				{ 3,3,3,0 },		// # # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,3,0,0 },		//	 #
				{ 3,3,0,0 },		// # #
				{ 0,3,0,0 },		//   #
				{ 0,0,0,0 }		//
			}
		,
		{
			{ 0,0,0,0 },		//	 
			{ 3,3,3,0 },		// # # #
			{ 0,3,0,0 },		//	 #
			{ 0,0,0,0 }		//

		},
		{
			{ 0,3,0,0 },		//	 #
			{ 0,3,3,0 },		//   # #
			{ 0,3,0,0 },		//   #
			{ 0,0,0,0 }		//
		}
		},
		{
			{
				{ 0,4,4,0 },		//   # #
				{ 4,4,0,0 },		// # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 4,0,0,0 },		//   #
				{ 4,4,0,0 },		//   # #
				{ 0,4,0,0 },		//     #
				{ 0,0,0,0 }		//
			},
			{
				{ 0,4,4,0 },		//   # #
				{ 4,4,0,0 },		// # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 4,0,0,0 },		//   #
				{ 4,4,0,0 },		//   # #
				{ 0,4,0,0 },		//     #
				{ 0,0,0,0 }		//
			}
		},
		{
			{
				{ 5,5,0,0 },		//   # #
				{ 0,5,5,0 },		//     # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,5,0,0 },		//     #
				{ 5,5,0,0 },		//   # #
				{ 5,0,0,0 },		//   # 
				{ 0,0,0,0 }		//
			},
			{
				{ 5,5,0,0 },		//   # #
				{ 0,5,5,0 },		//     # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,5,0,0 },		//     #
				{ 5,5,0,0 },		//   # #
				{ 5,0,0,0 },		//   #
				{ 0,0,0,0 }		//
			}
		},
		{
			{
				{ 0,6,6,0 },		//   # #
				{ 0,6,6,0 },		//   # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,6,6,0 },		//   # #
				{ 0,6,6,0 },		//   # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,6,6,0 },		//   # #
				{ 0,6,6,0 },		//   # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			},
			{
				{ 0,6,6,0 },		//   # #
				{ 0,6,6,0 },		//   # #
				{ 0,0,0,0 },		//
				{ 0,0,0,0 }		//
			}
		},
		{
			{
				{ 0,7,0,0 },		// # # # #
				{ 0,7,0,0 },		//
				{ 0,7,0,0 },		//
				{ 0,7,0,0 }		//
			},
			{
				{ 7,7,7,7 },		//   #
				{ 0,0,0,0 },		//   #
				{ 0,0,0,0 },		//   #
				{ 0,0,0,0 }		//   #
			},
			{
				{ 0,7,0,0 },		// # # # #
				{ 0,7,0,0 },		//
				{ 0,7,0,0 },		//
				{ 0,7,0,0 }		//
			},
			{
				{ 7,7,7,7 },		//   #
				{ 0,0,0,0 },		//   #
				{ 0,0,0,0 },		//   #
				{ 0,0,0,0 }		//   #
			}
		}
	};



};


