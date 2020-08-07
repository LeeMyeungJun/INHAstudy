#pragma once
class GameUI :public UI
{
public:
	GameUI();
	~GameUI();

	void Init(void);
	void draw(HDC);

	RECT n_rc_reStart;
	RECT m_rc_menu;
};

