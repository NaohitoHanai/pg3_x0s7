#pragma once
#include "../Library/GameObject.h"

class Goblin : public GameObject
{
public:
	Goblin();
	~Goblin();
	void Start() override;
	void Update() override;
	void Draw() override;

	bool AttackLine(VECTOR p1, VECTOR p2, VECTOR pPos);

	VECTOR Position() {
		return position;
	}
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};