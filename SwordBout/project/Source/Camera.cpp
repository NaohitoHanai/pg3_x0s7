#include "Camera.h"
#include "../Library/Time.h"

Camera::Camera()
{
	position = VGet(0, 300, -500);
	target = VGet(0, 0, 0);
	SetDrawOrder(-100); // Å‰‚É‚â‚é
	shake = VGet(0, 0, 0);
}

Camera::~Camera()
{
}

void Camera::Update()
{
	if (time > 0) {
		shake = VGet(0, -sinf(time * DX_PI *4) * range * time, 0);
		time -= Time::DeltaTime();
	}
}

void Camera::Draw()
{
	SetCameraPositionAndTarget_UpVecY(position+shake, target+shake);
}

void Camera::SetPosition(const VECTOR& pos)
{
	position = pos;
}

void Camera::SetTarget(const VECTOR& pos)
{
	target = pos;
}

void Camera::ShakeVertical(float mag)
{
	time = 0.5f;
	range = mag*2.0f;
}
