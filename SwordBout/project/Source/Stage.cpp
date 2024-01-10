#include "Stage.h"

Stage::Stage()
{
	hModel = MV1LoadModel("data/Stage/Stage00.mv1");
}

Stage::~Stage()
{
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
	//ü•ª‚Æƒ‚ƒfƒ‹“–‚½‚è”»’è‚Ì—á
	MV1_COLL_RESULT_POLY result;
	result = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (result.HitFlag) { // “–‚½‚Á‚½
		if (hitPos != nullptr)
		*hitPos = result.HitPosition;
		// ‚±‚ê‚ª“–‚½‚Á‚½À•W
	}
	return result.HitFlag;
}
