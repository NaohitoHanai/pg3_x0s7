#pragma once
/// <summary>
/// シーンの切り替えを管理するクラス
/// 実際のシーンの作成部分は、SceneFactoryに書いてください
/// </summary>
/// <author>N.Hanai</author>
#include <string>
#include <list>

class SceneFactory;
class SceneBase;

/// <summary>
/// 現在のシーンを呼び出している。
/// Sceneを切り替える時は、ChangeScene()を呼び出せばよく、
/// 呼んだ時に切り替えるのではなく、次回のUpdate()で切り替えるようにしている。
/// </summary>
namespace SceneManager {
	void Start();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// 共通シーンを取得する
	/// </summary>
	SceneBase* CommonScene();

	/// <summary>
	/// 現在のシーンを取得する
	/// </summary>
	SceneBase* CurrentScene();

	/// <summary>
	/// 現在のシーンとして登録する
	/// </summary>
	/// <param name="scene"></param>
	void SetCurrentScene(SceneBase* scene);

	/// <summary>
	/// シーンを切り替える。
	/// 直接ここでは切り替えず、次回Update()が呼ばれたとき、Scene処理を呼ぶ前に切り替えます。
	/// シーンの名前とクラスの関係は、SceneFactory()に記述してください。
	/// </summary>
	/// <param name="sceneName">シーン名</param>
	void ChangeScene(const std::string& sceneName);

	void Exit();
};
