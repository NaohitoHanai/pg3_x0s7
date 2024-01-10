#include "Time.h"
#include <Windows.h>
#include <assert.h>

namespace {
	LARGE_INTEGER freq;
	LARGE_INTEGER current;
	float deltaTime;
	static const int REC_SIZE = 60;
	float record[REC_SIZE]; // 60回分のリングバッファ
	int recCount = 0;
};

void Time::Init()
{
	bool ret = QueryPerformanceFrequency(&freq);
	assert(ret);
	QueryPerformanceCounter(&current);
}

void Time::Refresh()
{
	LARGE_INTEGER last = current;
	QueryPerformanceCounter(&current);
	float t = static_cast<float>(current.QuadPart - last.QuadPart) / freq.QuadPart;

	// deltaTimeは、平均フレームレートの2倍を超えないようにする
	if (recCount >= REC_SIZE) {
		float sum = 0;
		for (int i = 0; i < REC_SIZE; i++)
			sum += record[i];
		sum /= REC_SIZE;
		if (t > sum * 2.0f)
			t = sum * 2.0f;
	}
	record[recCount % REC_SIZE] = t;
	recCount++;
	deltaTime = t;
}

float Time::DeltaTime()
{
	return deltaTime;
}
