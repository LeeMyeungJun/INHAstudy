#pragma once
#include "Scene.h"
class LobbyScene :
	public Scene
{
public:
	LobbyScene();
	~LobbyScene();

	virtual void Init() override;
	virtual void Render() override;
	virtual void Update() override;
};

