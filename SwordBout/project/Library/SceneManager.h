#pragma once
/// <summary>
/// �V�[���̐؂�ւ����Ǘ�����N���X
/// ���ۂ̃V�[���̍쐬�����́ASceneFactory�ɏ����Ă�������
/// </summary>
/// <author>N.Hanai</author>
#include <string>
#include <list>

class SceneFactory;
class SceneBase;

/// <summary>
/// ���݂̃V�[�����Ăяo���Ă���B
/// Scene��؂�ւ��鎞�́AChangeScene()���Ăяo���΂悭�A
/// �Ă񂾎��ɐ؂�ւ���̂ł͂Ȃ��A�����Update()�Ő؂�ւ���悤�ɂ��Ă���B
/// </summary>
namespace SceneManager {
	void Start();
	void Update();
	void Draw();
	void Release();

	/// <summary>
	/// ���ʃV�[�����擾����
	/// </summary>
	SceneBase* CommonScene();

	/// <summary>
	/// ���݂̃V�[�����擾����
	/// </summary>
	SceneBase* CurrentScene();

	/// <summary>
	/// ���݂̃V�[���Ƃ��ēo�^����
	/// </summary>
	/// <param name="scene"></param>
	void SetCurrentScene(SceneBase* scene);

	/// <summary>
	/// �V�[����؂�ւ���B
	/// ���ڂ����ł͐؂�ւ����A����Update()���Ă΂ꂽ�Ƃ��AScene�������ĂԑO�ɐ؂�ւ��܂��B
	/// �V�[���̖��O�ƃN���X�̊֌W�́ASceneFactory()�ɋL�q���Ă��������B
	/// </summary>
	/// <param name="sceneName">�V�[����</param>
	void ChangeScene(const std::string& sceneName);

	void Exit();
};
