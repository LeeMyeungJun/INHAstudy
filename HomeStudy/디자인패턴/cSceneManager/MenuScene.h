#pragma once
#include "Scene.h"
class MenuScene :
	public Scene
{
public:
	MenuScene();
	~MenuScene();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

