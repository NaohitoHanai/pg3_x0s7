#pragma once
// animation.h

class Animation
{
public:
	Animation();
	~Animation();
	void Update();
	void SetModel(int model);
	void Play(int animModel, bool loop=true);
	float GetCurrentFrame() {return frame;}

	/// <summary>
	/// 再生速度を設定する
	/// </summary>
	/// <param name="speed">通常速度が1.0</param>
	void SetFrameSpeed(float speed) {
		frameSpeed = speed / 2.0f;
	}
	bool IsEnd() {
		return !loopMode && frame >= maxFrame;
	}

private:
	int baseModel;
	int attachIndex;
	float frame; // フレームを数える
	float maxFrame;
	float frameSpeed; // 再生速度
	bool loopMode; // ループするか
	int curAnim; // 今のアニメーション
};
