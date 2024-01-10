#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "../Library/Time.h"

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root,
		MGetRotY(DX_PI_F));
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	jumpVelocity = VGet(0, 0, 0);
	landing = true;
}

Player::~Player()
{
}

void Player::Start()
{
	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	VECTOR hitPos;
	if (pStage->CollLine(position + VGet(0, 500, 0), position + VGet(0, -500, 0),
		&hitPos))
	{
		position = hitPos;
		jumpVelocity = VGet(0, 0, 0);
		landing = true;
	}
}

void Player::Update()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		// 右旋回
		rotation.y += 6.0 * DX_PI / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		// 左旋回
		rotation.y -= 6.0 * DX_PI / 180.0f;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		// 向いてるほうへ進む
		MATRIX rotY = MGetRotY(rotation.y);
		position += VGet(0, 0, 5.0f) * rotY;
	}
	if (CheckJumpKey()) {
		if (landing) {
			jumpVelocity = VGet(0, 50.0f, 0);
			landing = false;
		}
	}
	jumpVelocity.y -= 100.0f * Time::DeltaTime();
	position += jumpVelocity;

	Camera* pCam = ObjectManager::FindGameObject<Camera>();
	if (CheckHitKey(KEY_INPUT_V)) {
		pCam->ShakeVertical(5.0f);
	}
	pCam->SetTarget(position + VGet(0, 200, 0));
	pCam->SetPosition(
		VGet(0, 250, -300) * MGetRotY(rotation.y) + position);
	Stage* pStage = ObjectManager::FindGameObject<Stage>();
	VECTOR hitPos;
	if (landing) {
		if (pStage->CollLine(position + VGet(0, 50, 0), position + VGet(0, -50, 0),
			&hitPos))
		{
			position = hitPos;
			jumpVelocity = VGet(0, 0, 0);
			landing = true;
		}
		else {
			landing = false;
		}
	}
	else {
		if (pStage->CollLine(position - jumpVelocity, position,
			&hitPos))
		{
			position = hitPos;
			jumpVelocity = VGet(0, 0, 0);
			landing = true;
		}
	}
	//int legL = MV1SearchFrame(hModel, "legL");
	//MATRIX m = MV1GetFrameLocalMatrix(hModel, legL);
	//VECTOR trans = VGet(0, 0, 0) * m;/* mの中の移動部分だけ取り出す */
	//MV1SetFrameUserLocalMatrix(hModel, legL,
	//	MGetRotX(DX_PI / 2.0f)*MGetTranslate(trans));
	//int kneeL = MV1SearchFrame(hModel, "kneeL");
	//m = MV1GetFrameLocalMatrix(hModel, kneeL);
	//trans = VGet(0, 0, 0) * m;/* mの中の移動部分だけ取り出す */
	//MV1SetFrameUserLocalMatrix(hModel, kneeL,
	//	MGetRotX(-DX_PI / 2.0f)* MGetTranslate(trans));
}

void Player::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

bool Player::CheckJumpKey()
{
	static bool lastKey;

	bool current = (CheckHitKey(KEY_INPUT_SPACE) != 0);
	bool ret = current && !lastKey;
	lastKey = current;
	return ret;
}
