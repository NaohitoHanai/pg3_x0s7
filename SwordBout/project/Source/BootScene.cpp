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
	SceneManager::ChangeScene("TitleScene"); // �N�����I�������Title��\��
}

void BootScene::Draw()
{
}
