#pragma once

/// <summary>
/// App�܂ł�C�ŏ�����Ă��܂�
/// main���[�v�̏�������́A���L�̂S�֐����Ăяo�����̂ŁA
/// ���̐�̗���͂����ŏ����Ă�������
/// </summary>
/// <author>N.Hanai</author>

/// <summary>
/// �ŏ��̂P�񂾂��Ă΂�܂�
/// </summary>
void AppInit();

/// <summary>
/// ���t���[���Ă΂�܂�
/// �����ŕ`�悵�Ă��\������܂���
/// </summary>
void AppUpdate();

/// <summary>
/// ���t���[���Ă΂�܂��B
/// �����ŕ`�悵�����̂������\������܂�
/// </summary>
void AppDraw();

/// <summary>
/// �I���O�ɂP��Ă΂�܂�
/// </summary>
void AppRelease();

/// <summary>
/// �A�v�����I�����܂�
/// </summary>
void AppExit();

/// <summary>
/// �A�v���I���̗v��������������Ԃ��܂�
/// </summary>
bool AppIsExit();