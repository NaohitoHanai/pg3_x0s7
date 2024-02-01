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
	// ���ʑO����

	// State�ʂ̏���
	action.at(state)->Update();

	// ���ʌ㏈��
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
//		VECTOR diff = pPos - position; // Goblin����Player�ւ̃x�N�g��
//		diff.y = 0.0f; // �����̍��𖳎�����
//		if (VSquareSize(diff) < 1000.0f*1000.0f) {
//			static const float ang = DegToRad(5.0f);
//			static const float cosAng = cosf(ang);
//
//			// VNorm(diff)�Ǝ����̐��ʂ̓���
//			VECTOR diffNorm = VNorm(diff);
//			VECTOR forward = VGet(0, 0, 1)* MGetRotY(rotation.y);
//			if (VDot(diffNorm, forward) >= cos(DegToRad(5.0f))) {
//				// �}5�x�ȓ��Ȃ̂�
////				rotation.y = atan2(diff.x, diff.z);
//			} else if (VDot(VGet(1,0,0)*MGetRotY(rotation.y), diffNorm)>0) {
//				rotation.y += DegToRad(5.0f);
//			} else {
//				rotation.y -= DegToRad(5.0f);
//			}
//			// �v���C���[�Ɍ������đ��x2.5�Ői��
//			// VSize�F���������߂�
//			// VNorm�F�������P�ɂ���@VNorm�Ƃ́Av/VSize(v)
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
	// ������Goblin��Line�̓����蔻��
	// ����������A���� DestroyMe();
	MV1_COLL_RESULT_POLY result;
	result = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (result.HitFlag) { // ��������
		VECTOR push = position - pPos;
		push.y = 0.0f;
		push = VNorm(push); // �����P
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
		VECTOR diff = pPos - pParent->position; // Goblin����Player�ւ̃x�N�g��
		diff.y = 0.0f; // �����̍��𖳎�����
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
		VECTOR diff = pPos - pParent->position; // Goblin����Player�ւ̃x�N�g��
		diff.y = 0.0f; // �����̍��𖳎�����
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

		// VNorm(diff)�Ǝ����̐��ʂ̓���
		VECTOR diffNorm = VNorm(diff);
		VECTOR forward = VGet(0, 0, 1)* MGetRotY(pParent->rotation.y);
		if (VDot(diffNorm, forward) >= cos(DegToRad(5.0f))) {
						// �}5�x�ȓ��Ȃ̂�
		//	rotation.y = atan2(diff.x, diff.z);
		} else if (VDot(VGet(1,0,0)*MGetRotY(pParent->rotation.y), diffNorm)>0) {
			pParent->rotation.y += DegToRad(5.0f);
		} else {
			pParent->rotation.y -= DegToRad(5.0f);
		}
		// �v���C���[�Ɍ������đ��x2.5�Ői��
		// VSize�F���������߂�
		// VNorm�F�������P�ɂ���@VNorm�Ƃ́Av/VSize(v)
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