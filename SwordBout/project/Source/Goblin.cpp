#include "Goblin.h"
#include "Stage.h"
#include "Player.h"
#include "../ImGui/imgui.h"
#include "../Library/Time.h"

Goblin::Goblin()
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root,
		MGetRotY(DX_PI_F));

	position = VGet(100, 0, 0);
	rotation = VGet(0, 0, 0);

	action.emplace(eIdle, new ActionIdle(this));
	action.emplace(eApproach, new ActionApproach(this));
	action.emplace(eAttack, new ActionAttack(this));
	ChangeState(eIdle);
}

Goblin::~Goblin()
{
}

void Goblin::Start()
{
}

void Goblin::Update()
{
	// 共通前処理

	// State別の処理
	action.at(state)->Update();

	// 共通後処理
	VECTOR hitPos;
	Stage* pStage = ObjectManager::FindGameObject <Stage>();
	if (pStage->CollLine(position + VGet(0, 50, 0),
		position + VGet(0, -50, 0),
		&hitPos))
	{
		position = hitPos;
	}
}

//
//
//	Player* pPlayer = ObjectManager::FindGameObject<Player>();
//	if (pPlayer != nullptr) {
//		VECTOR pPos = pPlayer->Position();
//		VECTOR diff = pPos - position; // GoblinからPlayerへのベクトル
//		diff.y = 0.0f; // 高さの差を無視する
//		if (VSquareSize(diff) < 1000.0f*1000.0f) {
//			static const float ang = DegToRad(5.0f);
//			static const float cosAng = cosf(ang);
//
//			// VNorm(diff)と自分の正面の内積
//			VECTOR diffNorm = VNorm(diff);
//			VECTOR forward = VGet(0, 0, 1)* MGetRotY(rotation.y);
//			if (VDot(diffNorm, forward) >= cos(DegToRad(5.0f))) {
//				// ±5度以内なので
////				rotation.y = atan2(diff.x, diff.z);
//			} else if (VDot(VGet(1,0,0)*MGetRotY(rotation.y), diffNorm)>0) {
//				rotation.y += DegToRad(5.0f);
//			} else {
//				rotation.y -= DegToRad(5.0f);
//			}
//			// プレイヤーに向かって速度2.5で進む
//			// VSize：長さを求める
//			// VNorm：長さを１にする　VNormとは、v/VSize(v)
////			VECTOR move = diff / (VSize(diff) * 2.5f);
//			VECTOR move = forward * 2.5f;//	VGet(0, 0, 2.5f)* MGetRotY(rotation.y);
//			position += move;
//		}
//	}

	//VECTOR hitPos;
	//Stage* pStage = ObjectManager::FindGameObject <Stage>();
	//if (pStage->CollLine(position + VGet(0, 50, 0),
	//	position + VGet(0, -50, 0),
	//	&hitPos))
	//{
	//	position = hitPos;
	//}
//}

void Goblin::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

bool Goblin::AttackLine(VECTOR p1, VECTOR p2, VECTOR pPos)
{
	MV1RefreshCollInfo(hModel, -1);
	// ここでGoblinとLineの当たり判定
	// 当たったら、消す DestroyMe();
	MV1_COLL_RESULT_POLY result;
	result = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (result.HitFlag) { // 当たった
		VECTOR push = position - pPos;
		push.y = 0.0f;
		push = VNorm(push); // 長さ１
		position += push * 50.0f;
//		DestroyMe();
	}
	return result.HitFlag;
}

void Goblin::SetPositionAngle(VECTOR pos, float yrot)
{
	position = pos;
	rotation = VGet(0, yrot, 0);
}

void Goblin::ChangeState(State st)
{
	state = st;
	action[state]->Start();
}

void Goblin::ActionIdle::Update()
{
	pParent->rotation.y += DegToRad(1.0f);
	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	if (pPlayer != nullptr) {
		VECTOR pPos = pPlayer->Position();
		VECTOR diff = pPos - pParent->position; // GoblinからPlayerへのベクトル
		diff.y = 0.0f; // 高さの差を無視する
		if (VSquareSize(diff) < 1000.0f * 1000.0f) {
			pParent->ChangeState(Goblin::State::eApproach);
		}
	}
}

void Goblin::ActionApproach::Update()
{
	pParent->rotation.y += DegToRad(1.0f);
	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	if (pPlayer != nullptr) {
		VECTOR pPos = pPlayer->Position();
		VECTOR diff = pPos - pParent->position; // GoblinからPlayerへのベクトル
		diff.y = 0.0f; // 高さの差を無視する
		if (VSquareSize(diff) > 1000.0f * 1000.0f) {
			pParent->ChangeState(Goblin::State::eIdle);
			return;
		}
		else if (VSquareSize(diff) < 100.0f * 100.0f) {
			pParent->ChangeState(Goblin::State::eAttack);
			return;
		}
		static const float ang = DegToRad(5.0f);
		static const float cosAng = cosf(ang);

		// VNorm(diff)と自分の正面の内積
		VECTOR diffNorm = VNorm(diff);
		VECTOR forward = VGet(0, 0, 1)* MGetRotY(pParent->rotation.y);
		if (VDot(diffNorm, forward) >= cos(DegToRad(5.0f))) {
						// ±5度以内なので
		//	rotation.y = atan2(diff.x, diff.z);
		} else if (VDot(VGet(1,0,0)*MGetRotY(pParent->rotation.y), diffNorm)>0) {
			pParent->rotation.y += DegToRad(5.0f);
		} else {
			pParent->rotation.y -= DegToRad(5.0f);
		}
		// プレイヤーに向かって速度2.5で進む
		// VSize：長さを求める
		// VNorm：長さを１にする　VNormとは、v/VSize(v)
		//			VECTOR move = diff / (VSize(diff) * 2.5f);
		VECTOR move = forward * 2.5f;//	VGet(0, 0, 2.5f)* MGetRotY(rotation.y);
		pParent->position += move;
	}
}

void Goblin::ActionAttack::Start()
{
	timer = 2.0f;
}

void Goblin::ActionAttack::Update()
{
	timer -= Time::DeltaTime();
	if (timer <= 0.0f)
		pParent->ChangeState(Goblin::State::eIdle);
}