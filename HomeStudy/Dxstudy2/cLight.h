#pragma once
class cLight
{
public:
	cLight();
	~cLight();
private:
	float fRange;

public:
	void Update();
	void Setup();
	void Render();
	void Set_PointLight();
	void Set_SpotLight();
	void Set_DirectionLight();
	
	void LightUpdate_PointLight(float x = 0.1f);
	void LightUpdate_SpotLight(float x = 0.1f);
	void LightUpdate_DirectionLight();
};

