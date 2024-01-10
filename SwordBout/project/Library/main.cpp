/// <summary>
/// CoG�t���[�����[�N
/// Ver 3.0�ł�
/// WinMain()����n�܂�܂�
/// </summary>
/// <author>N.Hanai</author>
#include <DxLib.h>
#include "App.h"
#include "../Source/Screen.h"
#include "../ImGui/imgui_impl_dxlib.hpp"

#define CoGVersion (3.0)

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(Screen::WIDTH, Screen::HEIGHT, 32);
	SetOutApplicationLogValidFlag(FALSE); // ���O���o���Ȃ�

	SetMainWindowText(Screen::WINDOW_NAME);
	SetWindowSizeExtendRate(Screen::WINDOW_EXTEND);
	ChangeWindowMode(Screen::WINDOW_MODE); // Window���[�h�̏ꍇ

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	SetAlwaysRunFlag(TRUE);
	SetUseZBuffer3D(TRUE);
	SetWriteZBuffer3D(TRUE);

	// ���[�U�[�̓��͂�ImGui��������悤�ɂ���
	SetHookWinProc([](HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) -> LRESULT /*CALLBACK*/
		{
			// DxLib��ImGui�̃E�B���h�E�v���V�[�W���𗼗�������
			SetUseHookWinProcReturnValue(FALSE);
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		});
	// imgui init
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui_ImplDXlib_Init();

	AppInit();

//	int mStartTime = GetNowCount();

	while (true) {
		ImGui_ImplDXlib_NewFrame();
		ImGui::NewFrame();

		AppUpdate();

		if (DxLib::ProcessMessage() == -1 || AppIsExit())
			break;

		ClearDrawScreen();
		AppDraw();
		ImGui::EndFrame();
		ImGui::Render();

		ImGui_ImplDXlib_RenderDrawData();

		if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
		RefreshDxLibDirect3DSetting();

		ScreenFlip();
	}
	AppRelease();

	//Imgui�̏I������
	ImGui_ImplDXlib_Shutdown();
	ImGui::DestroyContext();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}