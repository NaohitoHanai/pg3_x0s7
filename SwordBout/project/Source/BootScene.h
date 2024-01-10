#pragma once

#include "../Library/SceneBase.h"

class BootScene : public SceneBase {
public:
	BootScene();
	~BootScene();
	void Update() override;
	void Draw() override;
};