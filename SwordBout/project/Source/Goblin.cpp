#include "Goblin.h"
#include "Stage.h"

Goblin::Goblin()
{
	hModel = MV1LoadModel("data/Character/Goblin/Goblin.mv1");
	position = VGet(100, 0, 0);
	rotation = VGet(0, 0, 0);
}

Goblin::~Goblin()
{
}

void Goblin::Start()
{
}

void Goblin::Update()
{
	VECTOR hitPos;
	Stage* pStage = ObjectManager::FindGameObject <Stage>();
	if (pStage->CollLine(position + VGet(0, 50, 0),
		position + VGet(0, -50, 0),
		&hitPos))
	{
		position = hitPos;
	}
}

void Goblin::Draw()
{
	MV1SetPosition(hModel, position);
	MV1SetRotationXYZ(hModel, rotation);
	MV1DrawModel(hModel);
}

bool Goblin::AttackLine(VECTOR p1, VECTOR p2, VECTOR pPos)
{
	MV1RefreshCollInfo(hModel, -1);
	// Ç±Ç±Ç≈GoblinÇ∆LineÇÃìñÇΩÇËîªíË
	// ìñÇΩÇ¡ÇΩÇÁÅAè¡Ç∑ DestroyMe();
	MV1_COLL_RESULT_POLY result;
	result = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (result.HitFlag) { // ìñÇΩÇ¡ÇΩ
		VECTOR push = position - pPos;
		push.y = 0.0f;
		push = VNorm(push); // í∑Ç≥ÇP
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
