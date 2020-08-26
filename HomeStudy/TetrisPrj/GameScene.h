#pragma once
#define WIDTH 17
#define HEIGHT 26
class GameScene :public Scene
{
private:
	int		 m_iLevel;	
	bool	 m_GameStart;		
	bool	 m_GamePause;		
	bool	 m_bHold ;
	int		 m_iBlockWidth;		
	int		 m_iCurBlocksType;		
	int		 m_iCurBlocksState;	
	int		 m_iCurBlocksX, m_iCurBlocksY;
	int		 m_iGostType;
	int		 m_iGostState;
	int		 m_iGostY;
	int		 m_iNextBlocksType;	
	int		 m_iHoldBlocksType;	
	int		 m_iGameBoard[HEIGHT][WIDTH];
	int		 m_iSpeed;			
	int		 m_iScore;				
	int		 m_iTotalClearBlocks;	
	int		 m_iStartClearBlocks;	
	int		 m_iStepClearBlocks;	

public:
	GameScene();
	~GameScene();
	HDC hBlocksDc;
	HDC BackBuffer;
	HDC FrontBuffer;
	HBITMAP HDoubleBuffer;
	HBITMAP hBlocks;

	POINT BoardPoint[HEIGHT-1][WIDTH-2];
	POINT Position[4];
	POINT NextBlockPosition[4][4];
	BITMAP bitBlcok;
	RECT client;

public:
	void Init(void);
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void Free(void);
	void UI(HDC hdc);
	void ClickEvent(LPARAM lParam);
public:
	void PrintScore(HDC hdc);
	void PrintLevel(HDC hdc);
	void DrawBlock(HDC hdc);
	int  DrawCurBlock();
	void PreviewBlocks(HDC hdc);
	void PositionSave();
	void SetBlockToGameBoard();
	bool CheckCollision();
	bool TurnCheckCollision();
	void CreateRandomBlocks();
	void GameOver();
	void BlockMove();
	void ClearCurBlocks(int x, int y);
	void RotateBlocks();
	void Input();
	void LineFullCheck();
	void DoubleBufferRender(HDC hdc);
public:
	/* 테트리스 블록 모양 및 색상 설정*/
	int m_BlockList[7][4][4][4] = 	// 블록 종류의 개수: -7, 회전상태(0°, 90°, -180°, -270°),
	{		 				        //...[-4][-4]: 블록의 모양구현
		{
			{
				{ 0,0,1,0 },		//     #		 for문 -2개를 이용하여 간단히 블록의 모양을
				{ 1,1,1,0 },		// # # # 	    구현할 수 있다. 0값은 흰색으로, 0이 아닌값은
				{ 0,0,0,0 },		//		         각 블록의 해당 색깔로 출력
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


