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
	vecAni[0]; //�����ϴ¸��
	vecAni[4]; //������ ���ִ¸�� 
	m_pAnimController->SetTrackAnimationSet(0, vecAni[4]);
	m_pAnimController->SetTrackSpeed(0, 10);
	//�ִϸ��̼��� �����ϱ����� ��Ʈ�ѷ��� �д� .
}

void cSkinnedMesh::Update()
{
	
	m_pAnimController->AdvanceTime(g_pTimeManager->GetElapsedTime(), NULL);//�������� ���ٰ� ���������� ���� ASE���Ͽ��� 320���� �����ߴ���?

	//640�̴� 3600�ΰ� �׷��� �ֵ� �ð��� �����ϸ鼭 �˾Ƽ� ©�� �˾Ƽ�����
		Update(m_pRoot, NULL);
	UpdateSkinnedMesh(m_pRoot);

	


}

void cSkinnedMesh::Update(LPD3DXFRAME pFrame, LPD3DXFRAME pParent)
{
	if (pFrame == NULL)
		pFrame = m_pRoot;

	ST_BONE* pBone = (ST_BONE*)pFrame;

	pBone->CombinedTransformationMatrix = pBone->TransformationMatrix;
	//�̰� ȸ���� ������? 
	
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

		pBoneMesh->pOrigMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&src); //���ؽ����ִ°Ÿ� �о������°ž� ������Ű����
		pBoneMesh->MeshData.pMesh->LockVertexBuffer(0, (void**)&dest);

		pBoneMesh->pSkinInfo->UpdateSkinnedMesh(pBoneMesh->pCurrentBoneMatrices, NULL, src, dest); 
		//���߿� ���������� �۾��� �ϵ�  ���⼭ ������ ������ �������ָ��  �츮�������� �Ž÷� ������ݾ� .
		//�������������� ������ �ϰ�;� �����Ѱ�  �ٽùݿ���Ű��;� ���⼭ �̷������� �̿��ϸ�ȴٱ�
		pBoneMesh->MeshData.pMesh->UnlockVertexBuffer();
		pBoneMesh->pOrigMesh->UnlockVertexBuffer();
	}//<<: if pFrame


	if (pFrame->pFrameFirstChild)
		UpdateSkinnedMesh(pFrame->pFrameFirstChild);

	if (pFrame->pFrameSibling)
		UpdateSkinnedMesh(pFrame->pFrameSibling);


	
	
}
