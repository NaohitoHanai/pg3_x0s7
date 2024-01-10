#include "Axis.h"

Axis::Axis()
{
}

Axis::~Axis()
{
}

void Axis::Update()
{
}

void Axis::Draw()
{
	DrawLine3D(VGet(-1000, 0, 0), VGet(1000, 0, 0), GetColor(255, 0, 0));
	DrawLine3D(VGet(0, -1000, 0), VGet(0, 1000, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -1000), VGet(0, 0, 1000), GetColor(0, 0, 255));
}
