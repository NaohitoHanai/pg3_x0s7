#include "BootScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"

BootScene::BootScene()
{
	DebugScreen* ds = Instantiate<DebugScreen>();
	ObjectManager::SetDrawOrder(ds, 10000);
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TitleScene"); // ‹N“®‚ªI‚í‚Á‚½‚çTitle‚ğ•\¦
}

void BootScene::Draw()
{
}
