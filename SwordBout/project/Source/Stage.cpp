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
	assert(ifs); // 開けなかったら止まる

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

	// 次にキャラクターデータ
	struct CHARA {
		int type; // 敵の種類
		VECTOR position; // 座標
		float angle; // 向き
	};
	for (int i = 0; i < header.charaNum; i++) {
		CHARA c;
		ifs.read((char*)&c, sizeof(c));
		Goblin* gob = Instantiate<Goblin>(); // 生成
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
	//線分とモデル当たり判定の例
	MV1_COLL_RESULT_POLY result;
	result = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (result.HitFlag) { // 当たった
		if (hitPos != nullptr)
		*hitPos = result.HitPosition;
		// これが当たった座標
	}
	return result.HitFlag;
}
