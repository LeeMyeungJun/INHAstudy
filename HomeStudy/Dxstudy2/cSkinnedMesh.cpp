#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh()
	:m_pRoot(NULL)
	, m_pAnimController(NULL)
	, m_fBlendTime(0.3f)
	, m_fPassedBlendTime(0.0f)
	, m_isAnimBlend(false)
	, m_enState(NONE)
	, AnimCheck(0)
	, passed(0)
	, Anibool(false)
{
}


cSkinnedMesh::~cSkinnedMesh()
{
	cAllocateHierarchy ah;
	D3DXFrameDestroy(m_pRoot, &ah);
	SafeRelease(m_pAnimController);
}

void cSkinnedMesh::Setup(char* szFolder, char* szFile)
{
	string sFullPath(szFolder);
	sFullPath = sFullPath + string("/") + string(szFile);

	cAllocateHierarchy ah;
	ah.SetFolder(szFolder);

	D3DXLoadMeshHierarchyFromXA(sFullPath.c_str(),
							D3DXMESH_MANAGED,
							g_pD3DDvice,
							&ah,
							NULL,
							&m_pRoot,
							&m_pAnimController);

	SetupBoneMatrixPtrs(m_pRoot);
<<<<<<< HEAD
	LPD3DXANIMATIONSET a = NULL;
	
	for(int i = 0 ; i < m_pAnimController->GetNumAnimationSets(); i++)
=======

	
	ID3DXAnimationSet* a;
	UINT numAS = m_pAnimController->GetNumAnimationSets();
	for (UINT i = 0; i <numAS; i++)
>>>>>>> ecd8c9bf5224e477a86746dddecd738cb25871da
	{
		m_pAnimController->GetAnimationSet(i, &a);
		string name = a->GetName();
	}
	//m_pAnimController->SetTrackSpeed(0, 10);
<<<<<<< HEAD

=======
	//애니메이션을 제어하기위해 컨트롤러를 둔다 .
>>>>>>> ecd8c9bf5224e477a86746dddecd738cb25871da
}

void cSkinnedMesh::Update()
{
	if(m_isAnimBlend)
	{
		m_fPassedBlendTime += g_pTimeManager->GetElapsedTime();
		if(m_fPassedBlendTime >= m_fBlendTime)
		{
			m_isAnimBlend = false;
			m_pAnimController->SetTrackWeight(0, 1.0f);
			m_pAnimController->SetTrackEnable(1, false); //1번트랙은 이제안쓸래 라는의미야 .
			
		}
		else
		{
			float fWeight = m_fPassedBlendTime / m_fBlendTime;
			m_pAnimController->SetTrackWeight(0, fWeight);
			m_pAnimController->SetTrackWeight(1, 1.0f - fWeight);
		}
	}

	if (Anibool)
	{
		passed += g_pTimeManager->GetElapsedTime();
		if (passed >AnimCheck)
		{
			passed = 0;
			Anibool = false;
			SetAnimation(Stand);
		}

		
	}
	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);//프레임을 갓다가 증가시켜줘 지난 ASE파일에서 320에서 시작했던가?

	//640이니 3600인가 그랫지 애도 시간이 증가하면서 알아서 짤라서 알아서해줘
		Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);

	


}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	

	ST_BONE* pBone = (ST_BONE*)pFrame;

	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;

	
	if(pParent)
	{
		pBone->CombinedTransformationMatrix *= ((ST_BONE*)pParent)->CombinedTransformationMatrix;
	}

	if(pFrame->pFrameFirstChild)
	{
		Update(pFrame->pFrameFirstChild, pFrame);
	}

	if(pFrame->pFrameSibling)
	{
		Update(pFrame->pFrameSibling, pParent);
	}
}

void cSkinnedMesh::Render(LPD3DXFRAME pFrame)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	if(pBone->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pBone->pMeshContainer;
		if(pBoneMesh->MeshData.pMesh)
		{
			g_pD3DDvice->SetTransform(D3DTS_WORLD, &pBone->CombinedTransformationMatrix);
			for(size_t i = 0 ; i < pBoneMesh->vecMtl.size() ; i++)
			{
				g_pD3DDvice->SetTexture(0, pBoneMesh->vecTexture[i]);
				g_pD3DDvice->SetMaterial(&pBoneMesh->vecMtl[i]);
				pBoneMesh->MeshData.pMesh->DrawSubset(i);
			}
		}
	}//: if

	if (pFrame->pFrameFirstChild)
		Render(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		Render(pFrame->pFrameSibling);
	
}

void cSkinnedMesh::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	static int n = 0;

	switch (message)
	{
	case WM_RBUTTONDOWN:
		SetAnimation(n++);
		break;
	}


}

void cSkinnedMesh::SetupBoneMatrixPtrs(LPD3DXFRAME pFrame)
{
	if(pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if(pBoneMesh -> pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for(DWORD i = 0 ; i < dwNumBones; i++)
			{
				ST_BONE* pBone = (ST_BONE*)D3DXFrameFind(m_pRoot, pSkinInfo->GetBoneName(i));
				pBoneMesh->ppBoneMatrixPtrs[i] = &(pBone->CombinedTransformationMatrix);
			}
		}
	}//<<:if


	if (pFrame->pFrameFirstChild)
		SetupBoneMatrixPtrs(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		SetupBoneMatrixPtrs(pFrame->pFrameSibling);
	
}

void cSkinnedMesh::UpdateSkinnedMesh(LPD3DXFRAME pFrame)
{
	if(pFrame && pFrame->pMeshContainer)
	{
		ST_BONE_MESH* pBoneMesh = (ST_BONE_MESH*)pFrame->pMeshContainer;

		if(pBoneMesh->pSkinInfo)
		{
			LPD3DXSKININFO pSkinInfo = pBoneMesh->pSkinInfo;
			DWORD dwNumBones = pSkinInfo->GetNumBones();
			for(DWORD i = 0 ; i <dwNumBones ; i++)
			{
				pBoneMesh->pCurrentBoneMatrices[i] = pBoneMesh->pBoneOffsetMatrices[i] * *(pBoneMesh->ppBoneMatrixPtrs[i]);
			}
		}
		BYTE* src = NULL;
		BYTE* dest = NULL;

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src); //버텍스에있는거를 읽어가지고오는거야 변형시키려고
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrices, NULL, src, dest); 
		//나중에 지형같은거 작업을 하되  여기서 정보를 얻어가지고서 갱신해주면되  우리지난번에 매시로 만들었잖아 .
		//그지형을가지고 편집을 하고싶어 편집한거  다시반영시키고싶어 여기서 이런식으로 이용하면된다구
		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}//<<: if pFrame


	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);



	
}

void cSkinnedMesh::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		{
			switch (wParam)
			{
			case VK_UP:
			{
				m_pAnimController->SetTrackAnimationSet(0, vecAni[3]);
			}
				break;
			case VK_SPACE :
			{
				m_pAnimController->SetTrackAnimationSet(0, vecAni[1]);
			}
				break;
			default:
				break;
			}
		}
		break;
	}
}

void cSkinnedMesh::SetAnimationIndex(int nIndex)
{
	int num = m_pAnimController->GetNumAnimationSets(); // 현재등록된 애니메이션 갯수
	if (nIndex > num) nIndex = nIndex % num;

	LPD3DXANIMATIONSET pAnimSet = NULL;
	m_pAnimController->GetAnimationSet(nIndex, &pAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pAnimSet); //현재 내자신 캐릭터가 0번트랙임
	//m_pAnimController->ResetTime();//애니메이션이 동작하던 중간이잇을거아니야 중간에 멈추면 그멈춘건 다시 처음으로 돌려놈
	//m_pAnimController->GetPriorityBlend();//애니메이션이 중간에 멈추면 어색해 그걸 자연스럽게해주는게 이친구야 . 이것만있으면 되는게아니라 m_fBlend친구도필요해
	
}

void cSkinnedMesh::SetAnimationIndexBlend(int nIndex)
{
	
	m_isAnimBlend = true; //섞이는 와중에 true가되겠지
	m_fPassedBlendTime = 0.0f;

	int num = m_pAnimController->GetNumAnimationSets();
	if (nIndex > num)nIndex = nIndex % num;

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC	stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);

	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet); //1번트랙으로 옮겨줘 1번동작이 3초정도 30프레임정도 진행됬다 . 이걸 1번트랙으로 옮겨주는거야 . 그다음에 새로운정보를 가지고
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);

	m_pAnimController->GetAnimationSet(nIndex, &pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f); //그냥 처음부터 실행해주면되 . 그리구나서

	//각각의 트랙에대해 가중치를 줄거야
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	SafeRelease(pPrevAnimSet);
	SafeRelease(pNextAnimSet);//썼던 것들을 지워줘

}

void cSkinnedMesh::SetAnimation(int state)
{
	m_isAnimBlend = true; //섞이는 와중에 true가되겠지
	m_fPassedBlendTime = 0.0f;
	Anibool = true;
	int num = m_pAnimController->GetNumAnimationSets();
	if (state > num)state = state % num;

	LPD3DXANIMATIONSET pPrevAnimSet = NULL;
	LPD3DXANIMATIONSET pNextAnimSet = NULL;

	D3DXTRACK_DESC	stTrackDesc;
	m_pAnimController->GetTrackDesc(0, &stTrackDesc);

	m_pAnimController->GetTrackAnimationSet(0, &pPrevAnimSet);
	m_pAnimController->SetTrackAnimationSet(1, pPrevAnimSet); //1번트랙으로 옮겨줘 1번동작이 3초정도 30프레임정도 진행됬다 . 이걸 1번트랙으로 옮겨주는거야 . 그다음에 새로운정보를 가지고
	m_pAnimController->SetTrackDesc(1, &stTrackDesc);
	AnimCheck = pPrevAnimSet->GetPeriod();

	
	m_pAnimController->GetAnimationSet(state, &pNextAnimSet);
	m_pAnimController->SetTrackAnimationSet(0, pNextAnimSet);
	m_pAnimController->SetTrackPosition(0, 0.0f); //그냥 처음부터 실행해주면되 . 그리구나서

												  //각각의 트랙에대해 가중치를 줄거야
	m_pAnimController->SetTrackWeight(0, 0.0f);
	m_pAnimController->SetTrackWeight(1, 1.0f);

	SafeRelease(pPrevAnimSet);
	SafeRelease(pNextAnimSet);//썼던 것들을 지워줘
}