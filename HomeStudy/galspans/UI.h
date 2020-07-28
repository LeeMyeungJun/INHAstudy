#pragma once
class UI
{
public:
	UI();
	virtual~UI();

	virtual void Init(void) = 0;
	virtual void draw(HDC) = 0;

	static FontManager FontSetting;

};

