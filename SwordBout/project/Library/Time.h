#pragma once

/// <summary>
/// 時間計測のクラス
/// DeltaTimeを取得するためのものです
/// DeltaTimeは、描画更新レートの２倍を超えることはありません
/// </summary>
/// <author>N.Hanai</author>

namespace Time {
	void Init();
	void Refresh();
	float DeltaTime();
};
