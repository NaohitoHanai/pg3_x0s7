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
	int hSabel; // �T�[�x���̃��f��

	VECTOR position;
	VECTOR rotation;
	VECTOR jumpVelocity; // �W�����v�x�N�g��
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
		// �ǉ�����Ȃ炱����
		MAX
	};
	int hAnim[MAX];

	int attacking; // 0:�U�����ĂȂ��A1�`3:�U����
	VECTOR attackLine[2]; // �U�����W
	VECTOR beforeLine[2]; // �O��̍��W
};