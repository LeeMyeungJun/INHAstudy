#include "stdafx.h"
#include "cSkinnedMeshManager.h"
#include "cSkinnedMesh.h"

cSkinnedMeshManager::cSkinnedMeshManager()
{
}


cSkinnedMeshManager::~cSkinnedMeshManager()
{
}

cSkinnedMesh* cSkinnedMeshManager::GetSkinnedMesh(char* szFolder, char* szFileName)
{
	string sFullpath(szFolder);
	sFullpath += (string("/") + string(szFileName));

	if(m_mapSkinnedMesh.find(sFullpath) == m_mapSkinnedMesh.end())
	{
		cSkinnedMesh* pSkinnedMesh = new cSkinnedMesh();
		pSkinnedMesh->Load(szFolder, szFileName);
		m_mapSkinnedMesh[sFullpath] = pSkinnedMesh;
	}
	return m_mapSkinnedMesh[sFullpath];
}

void cSkinnedMeshManager::Destroy()
{
	for each(auto it in m_mapSkinnedMesh)
	{
		it.second->Destroy();
		SafeDelete(it.second);
	}
}
