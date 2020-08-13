#pragma once
class MenuUI :public UI
{
public:
	MenuUI();
	~MenuUI();

	void Init(void);
	void draw(HDC);

	RECT m_rc_Title;
	RECT m_rc_Start;
	RECT m_rc_Exit;
	RECT m_rc_Manual;



};

