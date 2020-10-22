#include "stdafx.h"
#include "cSkinnedMesh.h"
#include "cAllocateHierarchy.h"


cSkinnedMesh::cSkinnedMesh()
	:m_pRoot(NULL)
	,m_pAnimController(NULL)
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

	vector<ID3DXAnimationSet*> vecAni;
	ID3DXAnimationSet* a;
	UINT numAS = m_pAnimController->GetNumAnimationSets();
	for (UINT i = 0; i <numAS; i++)
	{
		m_pAnimController->GetAnimationSet(i, &a);
		vecAni.push_back(a);
	}
	vecAni[0]; //공격하는모션
	vecAni[4]; //가만히 서있는모션 
	m_pAnimController->SetTrackAnimationSet(0, vecAni[4]);
	m_pAnimController->SetTrackSpeed(0, 10);
	//애니메이션을 제어하기위해 컨트롤러를 둔다 .
}

void cSkinnedMesh::Update()
{
	
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
	//이게 회전과 움직임? 
	
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
