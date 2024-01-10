#include "sceneManager.h"
#include "sceneBase.h"
#include "../Source/sceneFactory.h"
#include <DxLib.h>
#include "Time.h"
#include "App.h"

namespace {
	std::string m_currentName; // ���݂̃V�[���̖���
	std::string m_nextName;    // ���̃V�[���̖���
	SceneBase* m_currentScene; // ���̃V�[���̃C���X�^���X��ێ�
	SceneBase* m_commonScene;  // ���ʃV�[��
	SceneFactory* m_factory;   // �V�[���؂�ւ��p��Factory�̃|�C���^�[
};

void SceneManager::Start()
{
	Time::Init();

	m_nextName = "";
	m_currentName = "";
	m_commonScene = new SceneBase();

	m_factory = new SceneFactory();
	// �ŏ��ɓ����V�[�����ASceneFactory�ɍ���Ă��炤
	m_currentScene = m_factory->CreateFirst();
}

void SceneManager::Update()
{
	if (m_nextName != m_currentName) { // �V�[���؂�ւ��̎w�肪�������̂�
		if (m_currentScene != nullptr) { // ���܂ł̃V�[�������
			delete m_currentScene;
			m_currentScene = nullptr;
		}
		m_currentName = m_nextName;
		m_currentScene = m_factory->Create(m_nextName); // ���̃V�[�����쐬
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
