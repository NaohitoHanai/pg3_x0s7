#pragma once

/// <summary>
/// AppまではCで書かれています
/// mainループの処理からは、下記の４関数が呼び出されるので、
/// この先の流れはここで書いておくこと
/// </summary>
/// <author>N.Hanai</author>

/// <summary>
/// 最初の１回だけ呼ばれます
/// </summary>
void AppInit();

/// <summary>
/// 毎フレーム呼ばれます
/// ここで描画しても表示されません
/// </summary>
void AppUpdate();

/// <summary>
/// 毎フレーム呼ばれます。
/// ここで描画したものだけが表示されます
/// </summary>
void AppDraw();

/// <summary>
/// 終了前に１回呼ばれます
/// </summary>
void AppRelease();

/// <summary>
/// アプリを終了します
/// </summary>
void AppExit();

/// <summary>
/// アプリ終了の要求があったかを返します
/// </summary>
bool AppIsExit();