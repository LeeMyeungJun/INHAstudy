#pragma once
class cAnimation
{
	enum { BODY = 0 ,LEFT_LEG = 1 , RIGHT_LEG = 2 ,LEFT_HAND = 3,RIGHT_HAND = 4,HEAD =5 };
private:
	D3DXVECTOR3* m_PlayerBody;
	vector<D3DXVECTOR3*>* parts_;
public:
	cAnimation();
	~cAnimation();
public:
	void Setup(D3DXVECTOR3* PlayerBody);
	void Setup(vector<D3DXVECTOR3*>& parts);
	void Update();
	

	void AnimaitionWalk();

};

