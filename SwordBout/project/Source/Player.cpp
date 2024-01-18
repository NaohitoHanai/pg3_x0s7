#include "Player.h"
#include "Camera.h"
#include "Stage.h"
#include "../Library/Time.h"
#include "Goblin.h"

Player::Player()
{
	hModel = MV1LoadModel("data/Character/Player/PC.mv1");
	hSabel = MV1LoadModel("data/Character/Player/Sabel.mv1");

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root,
		MGetRotY(DX_PI_F));
	position = VGet(0, 0, 0);
	rotation = VGet(0, 0, 0);
	jumpVelocity = VGet(0, 0, 0);
	landing = true;

	animation = new Animation();
	animation->SetModel(hModel);

	std::string folder = "data/Character/Player/"; // C++の文字列
	const std::string FileName[] = {
		"Anim_Neutral.mv1",
		"Anim_Run.mv1",
		"Anim_Attack1.mv1",
		"Anim_Attack2.mv1",
		"Anim_Attack3.mv1",
	};
	for (int i = 0; i < MAX; i++) {
		hAnim[i] = MV1LoadModel((folder + FileName[i]).c_str());
	}

	animation->Play(hAnim[0], true);
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
	animation->Update();

	if (attacking == 0) {
		if (CheckHitKey(KEY_INPUT_D)) {
			// 右旋回
			rotation.y += 6.0 * DX_PI / 180.0f;
		}
		if (CheckHitKey(KEY_INPUT_A)) {
			// 左旋回
			rotation.y -= 6.0 * DX_PI / 180.0f;
		}
		if (CheckHitKey(KEY_INPUT_W)) {
			animation->Play(hAnim[RUN], true);
			// 向いてるほうへ進む
			MATRIX rotY = MGetRotY(rotation.y);
			position += VGet(0, 0, 5.0f) * rotY;
		}
		else {
			animation->Play(hAnim[STAND], true);
		}
	}
	if (CheckAttackKey()) {
		bool adjust = false;
		if (attacking == 0) {
			animation->Play(hAnim[ATTACK1], false);
			attacking = 1;
			adjust = true;
		} else if (attacking == 1 && animation->GetCurrentFrame() >= 8.5f) {
			animation->Play(hAnim[ATTACK2], false);
			attacking = 2;
			adjust = true;
		} else if (attacking == 2 && animation->GetCurrentFrame() >= 9.5f) {
			animation->Play(hAnim[ATTACK3], false);
			attacking = 3;
			adjust = true;
		}
		if (adjust) {
			Goblin* goblin = ObjectManager::FindGameObject<Goblin>();
			// 1.5m以内にいる
			VECTOR d = goblin->Position() - position;
			d.y = 0.0f;
			if (VSize(d) < 300.0f) {
				VECTOR a_v = VNorm(d);
				VECTOR b_v = VGet(0, 0, 1) * MGetRotY(rotation.y);
				float ip = VDot(a_v, b_v);
				if (ip > cos(DegToRad(30.0f))) { // 視野内
					if (VSize(d) > 50.0f) {
						position += VNorm(d) * 50.0f;
					}
					rotation.y = atan2(d.x, d.z);
				}
			}
		}
	}
	if (attacking > 0) {
		if (animation->IsEnd()) { // 今のアニメーションが終わったらtrue
			attacking = 0; // 攻撃停止
			animation->Play(hAnim[STAND], true);
		}
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

	// 攻撃の当たり判定
	if (attacking>0) {
		Goblin* goblin = ObjectManager::FindGameObject<Goblin>();
		if (goblin != nullptr) {
			if (!goblin->AttackLine(attackLine[0], attackLine[1], position)) {
				VECTOR a = (attackLine[0] + beforeLine[0]) / 2;
				VECTOR b = (attackLine[1] + beforeLine[1]) / 2;
				// 中間の線でも当たり判定
				goblin->AttackLine(a, b, position);
			}
		}
		beforeLine[0] = attackLine[0];
		beforeLine[1] = attackLine[1];
	}
}

void Player::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);

	int wp = MV1SearchFrame(hModel, "wp");
	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, wp);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	VECTOR p1 = VGet(0, 0, 0) * m; // サーベルの根本
	VECTOR p2 = VGet(0, -300, 0) * m; // サーベルの剣先
	DrawLine3D(p1, p2, GetColor(255, 0,0));
	attackLine[0] = p1;
	attackLine[1] = p2;
}

bool Player::CheckJumpKey()
{
	static bool lastKey;

	bool current = (CheckHitKey(KEY_INPUT_SPACE) != 0);
	bool ret = current && !lastKey;
	lastKey = current;
	return ret;
}

bool Player::CheckAttackKey()
{
	static bool lastKey;

	bool current = (CheckHitKey(KEY_INPUT_M) != 0);
	bool ret = current && !lastKey;
	lastKey = current;
	return ret;
}
