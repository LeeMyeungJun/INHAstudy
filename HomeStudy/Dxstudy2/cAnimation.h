#pragma once
class cAnimation
{
	enum { BODY = 0 ,LEFT_LEG = 1 , RIGHT_LEG = 2 ,LEFT_HAND = 3,RIGHT_HAND = 4,HEAD = 5 };
private:
	D3DXVECTOR3* m_PlayerBody;
	vector<D3DXVECTOR3*>* parts_;
	//translation 얼마만큼 위아래로 관절위치 숫자를 정할 주솟값변수가 필요함 why: 머리같은경우는 머리 목부분이지만 팔은 윗부분
	
public:
	cAnimation();
	~cAnimation();
public:
	void Setup(D3DXVECTOR3* PlayerBody);
	void Setup(vector<D3DXVECTOR3*>& parts);
	void Update();
	

	void AnimaitionWalk();

};

