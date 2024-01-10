#pragma once
#include "../Library/GameObject.h"

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
	VECTOR position;
	VECTOR rotation;
	VECTOR jumpVelocity; // �W�����v�x�N�g��
	bool landing;

	bool CheckJumpKey();
};