#include "PlayScene.h"
#include "../Library/SceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Screen.h"
#include "../Library/Time.h"
#include "Player.h"
#include "Camera.h"
#include "Axis.h"
#include "Stage.h"

PlayScene::PlayScene()
{
	Instantiate<Axis>();
	Instantiate<Player>();
	Instantiate<Camera>();
	Instantiate<Stage>();
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
	DrawFormatString(Screen::WIDTH - 200, 0, GetColor(255, 255, 255), "DeltaTime=%2.2fms", (Time::DeltaTime() * 1000.0f));
}
