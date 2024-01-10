#include "App.h"
#include "SceneManager.h"
#include "ObjectManager.h"

bool exitFlag = false;

void AppInit()
{
	SceneManager::Start();
	ObjectManager::Start();
	exitFlag = false;
}

void AppUpdate()
{
	SceneManager::Update();
	ObjectManager::Update();
}

void AppDraw()
{
	SceneManager::Draw();
	ObjectManager::Draw();
}

void AppRelease()
{
	SceneManager::Release();
	ObjectManager::Release();
}

void AppExit()
{
	exitFlag = true;
}

bool AppIsExit()
{
	return exitFlag;
}