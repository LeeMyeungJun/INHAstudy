#pragma once

class cSkinnedMesh;

class cSkinnedMeshManager
{
private:
	std::map<string, cSkinnedMesh*> m_mapSkinnedMesh;
public:
	Singleton(cSkinnedMeshManager);

	cSkinnedMesh*	GetSkinnedMesh(char* szFolder, char* szFileName);
	void Destroy();
};

#define g_pSkinnedMeshManager	cSkinnedMeshManager::GetInstance()