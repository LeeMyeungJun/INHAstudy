#pragma once
class Scene;
class LoginScene;
class LobbyScene;
class RoomScene;
class GameScene;
class LocalGameScene;
class SoundCenter;
class UI;

class GameCenter
{
public:
	enum class Scene_enum :size_t
	{
		NONE,
		LOGIN_SCENE,
		LOBBY_SCENE,
		ROOM_SCENE,
		GAME_SCENE,
		LOCALGAME_SCENE,
		EXIT,
		DEFAULT
	};

private:
	HWND hWnd;
	HINSTANCE hInstance;
	int		 m_MoveTime;
	int		 m_LocalLevel;
	int		 m_LocalScoreCheck;
	int		 m_LocalScore;



private:
	Scene		 * m_Scene;
	LoginScene	 *m_LoginScene;
	LobbyScene	 *m_LobbyScene;
	RoomScene	 *m_RoomScene;
	GameScene	 *m_GameScene;

	static SoundCenter *m_SoundCeneter;
	static UI *m_UI;
private:
	Scene_enum  m_Scene_enum;
public:
	GameCenter();
	~GameCenter();

	Scene_enum getScene() { return m_Scene_enum; }
	void setScene(Scene_enum SceneEnum) {m_Scene_enum = SceneEnum;}

	HWND getHwnd() { return hWnd; }
	void setHwnd(HWND hwnd) { this->hWnd = hwnd; }

	HINSTANCE getHInstance() { return hInstance; }
	void setHInstance(HINSTANCE hInstance) { this->hInstance = hInstance; }

	UI* getUI() { return m_UI; }


	GameScene * getGameScene()
	{
		return m_GameScene;
	}

	void InitMoveTime() { m_MoveTime = 0; }
	inline int getMoveTime() { return m_MoveTime; }
	void setMoveTime(int time) { m_MoveTime = time; }

	void InitLocalLevel() { m_LocalLevel = 1; }
	int  getLocalLevel() { return m_LocalLevel; }
	void setLocalLevel(int level) { m_LocalLevel = level; }

	void InitLocalScore()
	{
		m_LocalScore = 0;
		m_LocalScoreCheck = 0;
	}
	inline int  getLocalScore() { return m_LocalScore; }
	inline void setLocalScore(int score)
	{ 
		m_LocalScore = score; 
		m_LocalScoreCheck += score;

		if (m_LocalScoreCheck >= 2000)
		{
			m_LocalScoreCheck = 0;
			m_LocalLevel++;
		}
	
	}



	static GameCenter* GetInstance()
	{
		static GameCenter instance;
 		return &instance;
	}

public:
	void Init();
	void Update(UINT message, WPARAM wParam, LPARAM lParam);
	void Render(HWND hWnd, HDC hdc);
	void SceneChange(Scene_enum nextScene);


	
};

