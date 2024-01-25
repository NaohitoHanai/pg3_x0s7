#include "Stage.h"
#include <fstream>
#include <assert.h>
#include "Player.h"
#include "Goblin.h"

Stage::Stage()
{
	hModel = MV1LoadModel("data/Stage/Stage00.mv1");
}

Stage::~Stage()
{
}

void Stage::Start()
{
	std::ifstream ifs("data/Stage/Stage00.dat", std::ios::binary);
	assert(ifs); // �J���Ȃ�������~�܂�

	struct HEADER {
		char magic[4];
		int charaNum;
		int objectNum;
		int eventNum;
		VECTOR playerPosition;
		float playerAngle;
		int renderType;
		int clearCondition;
		int killNum;
		int killTarget;
	};
	HEADER header;
	ifs.read((char*)&header, sizeof(header));
	Player* pPlayer = ObjectManager::FindGameObject<Player>();
	pPlayer->SetPosition(header.playerPosition, header.playerAngle);

	// ���ɃL�����N�^�[�f�[�^
	struct CHARA {
		int type; // �G�̎��
		VECTOR position; // ���W
		float angle; // ����
	};
	for (int i = 0; i < header.charaNum; i++) {
		CHARA c;
		ifs.read((char*)&c, sizeof(c));
		Goblin* gob = Instantiate<Goblin>(); // ����
		gob->SetPositionAngle(c.position, c.angle);
	}
	ifs.close();
}

void Stage::Update()
{
}

void Stage::Draw()
{
	MV1DrawModel(hModel);
}

bool Stage::CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos)
{
	//�����ƃ��f�������蔻��̗�
	MV1_COLL_RESULT_POLY result;
	result = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (result.HitFlag) { // ��������
		if (hitPos != nullptr)
		*hitPos = result.HitPosition;
		// ���ꂪ�����������W
	}
	return result.HitFlag;
}
