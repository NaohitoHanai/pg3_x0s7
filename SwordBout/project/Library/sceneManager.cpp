#include "sceneManager.h"
#include "sceneBase.h"
#include "../Source/sceneFactory.h"
#include <DxLib.h>
#include "Time.h"
#include "App.h"

namespace {
	std::string m_currentName; // 現在のシーンの名称
	std::string m_nextName;    // 次のシーンの名称
	SceneBase* m_currentScene; // 今のシーンのインスタンスを保持
	SceneBase* m_commonScene;  // 共通シーン
	SceneFactory* m_factory;   // シーン切り替え用のFactoryのポインター
};

void SceneManager::Start()
{
	Time::Init();

	m_nextName = "";
	m_currentName = "";
	m_commonScene = new SceneBase();

	m_factory = new SceneFactory();
	// 最初に動くシーンを、SceneFactoryに作ってもらう
	m_currentScene = m_factory->CreateFirst();
}

void SceneManager::Update()
{
	if (m_nextName != m_currentName) { // シーン切り替えの指定があったので
		if (m_currentScene != nullptr) { // 今までのシーンを解放
			delete m_currentScene;
			m_currentScene = nullptr;
		}
		m_currentName = m_nextName;
		m_currentScene = m_factory->Create(m_nextName); // 次のシーンを作成
	}
	if (m_currentScene != nullptr)
		m_currentScene->Update();
	m_commonScene->Update();
}

void SceneManager::Draw()
{
	Time::Refresh();

	if (m_currentScene != nullptr)
		m_currentScene->Draw();
	m_commonScene->Draw();
}

void SceneManager::Release()
{
	if (m_currentScene != nullptr) {
		delete m_currentScene;
		m_currentScene = nullptr;
	}
	if (m_commonScene != nullptr) {
		delete m_commonScene;
		m_commonScene = nullptr;
	}
}

SceneBase* SceneManager::CommonScene()
{
	return m_commonScene;
}

SceneBase* SceneManager::CurrentScene()
{
	return m_currentScene;
}

void SceneManager::SetCurrentScene(SceneBase* scene)
{
	m_currentScene = scene;
}

void SceneManager::ChangeScene(const std::string& sceneName)
{
	m_nextName = sceneName;
}

void SceneManager::Exit()
{
	AppExit();
}
