#pragma once
#include "../Library/GameObject.h"
#include "animation.h"

class Player : public GameObject
{
public:
	Player();
	~Player();
	void Start() override;
	void Update() override;
	void Draw() override;
private:
	int hModel;
	int hSabel; // サーベルのモデル

	VECTOR position;
	VECTOR rotation;
	VECTOR jumpVelocity; // ジャンプベクトル
	bool landing;

	bool CheckJumpKey();
	bool CheckAttackKey();

	Animation* animation;
	enum ANIM_ID{
		STAND = 0,
		RUN,
		ATTACK1,
		ATTACK2,
		ATTACK3,
		// 追加するならここで
		MAX
	};
	int hAnim[MAX];

	int attacking; // 0:攻撃してない、1～3:攻撃中
	VECTOR attackLine[2]; // 攻撃座標
	VECTOR beforeLine[2]; // 前回の座標
};