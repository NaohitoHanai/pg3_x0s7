#include "animation.h"
#include "../Library/myDxLib.h"

Animation::Animation()
{
	attachIndex = -1;
	frameSpeed = 0.5f;
}

Animation::~Animation()
{
	if (attachIndex >= 0)
		MV1DetachAnim(baseModel, attachIndex);
}

void Animation::Update()
{
	if (attachIndex < 0)
		return;

	frame += frameSpeed;
	if (loopMode) {
		if (frame>=maxFrame) {
			frame -= maxFrame;
		}
	} else {
		if (frame>maxFrame) {
			frame = maxFrame;
		}
	}
	MV1SetAttachAnimTime(baseModel, attachIndex, frame);
}

void Animation::SetModel(int model)
{
	baseModel = model;
}

void Animation::Play(int animModel, bool loop)
{
	if (animModel == curAnim)
		return;

	curAnim = animModel;
	if (attachIndex>=0) {
		MV1DetachAnim(baseModel, attachIndex);
		attachIndex = -1;
	}
	attachIndex = MV1AttachAnim(baseModel, 0,
									animModel);
	loopMode = loop;
	frame = 0;
	maxFrame = MV1GetAttachAnimTotalTime(
						baseModel, attachIndex);
	MV1SetAttachAnimTime(baseModel, attachIndex, 0);
}
