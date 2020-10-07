#include "stdafx.h"
#include "ObjLoader.h"

ObjLoader::ObjLoader()
{
}

ObjLoader::~ObjLoader()
{
}

void ObjLoader::FileLoad(char* FileName)
{
	
}

void ObjLoader::ProcessMtl(char* FileName)
{
	
}

void ObjLoader::Setup()
{
	FileLoad("box.obj");
	ProcessMtl("box.mtl");
}

void ObjLoader::Render()
{
}