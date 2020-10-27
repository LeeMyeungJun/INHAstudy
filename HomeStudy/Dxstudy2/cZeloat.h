#pragma once
#include "cCharacter.h"

class cSkinnedMesh;
class cOBB;

class cZeloat
{
public:
	cZeloat();
	virtual ~cZeloat(void);
private:
	cSkinnedMesh* m_pSkinnedMesh;
	cOBB*		  m_pOBB;
	Synthesize_Add_Ref(cCharacter*, m_pCharacterController, CharacterController);
public:
	void Setup();
	void Update(iMap* pMap);
	void Render(D3DCOLOR c = D3DCOLOR_XRGB(255, 255, 255));

	cOBB* GetOBB();
	
};

