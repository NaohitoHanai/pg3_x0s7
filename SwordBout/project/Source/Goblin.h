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
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};