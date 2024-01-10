#pragma once
#include "../Library/GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
	void SetPosition(const VECTOR& pos);
	void SetTarget(const VECTOR& pos);
	/// <summary>
	/// �c�h�������
	/// </summary>
	/// <param name="mag">�h�ꕝ</param>
	void ShakeVertical(float mag);
private:
	VECTOR position;
	VECTOR target;
	VECTOR shake;
	float time;
	float range;
};