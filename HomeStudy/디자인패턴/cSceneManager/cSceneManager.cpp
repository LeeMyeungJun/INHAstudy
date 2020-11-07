// cSceneManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"




int main()
{
	
	Scene* gameS = new GameScene;
	Scene* gameL = new LobbyScene;
	Scene* gameM = new MenuScene;

	g_SceneManager->AddScene("GAMESCENE", gameS);
	g_SceneManager->AddScene("LOBBYSCENE", gameL);
	g_SceneManager->AddScene("MENUSCENE", gameM);

	g_SceneManager->EraseScene("LOBBYsSCENE");
	g_SceneManager->EraseScene("LOBBYSCENE");

	g_SceneManager->SceneChange("GAMESCENE");

	Scene* CurrentScene;

	CurrentScene = g_SceneManager->GetCurrentScene();
	
	CurrentScene->Update();

	g_SceneManager->SceneChange("LOBBYSCENE");
	
	CurrentScene = g_SceneManager->GetCurrentScene();
	if(CurrentScene == nullptr)
	{
		cout << "ÇØ´ç¾À¾øÀ½" << endl;
	}
	else
	{
		CurrentScene->Update();
	}
	


	
    return 0;
}

	