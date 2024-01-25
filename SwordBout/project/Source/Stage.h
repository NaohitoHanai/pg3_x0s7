#pragma once
#include "../Library/GameObject.h"

class Stage : public GameObject
{
public:
	Stage();
	~Stage();
	void Start() override;
	void Update() override;
	void Draw() override;
	bool CollLine(VECTOR p1, VECTOR p2, VECTOR* hitPos=nullptr);
private:
	int hModel;
	VECTOR position;
	VECTOR rotation;
};