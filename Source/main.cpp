#include <DxLib.h>
#include "App.h"
#include "Game.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(800, 600, 32);
	SetOutApplicationLogValidFlag(FALSE); // ���O���o���Ȃ�
#if _DEBUG // �f�o�b�O�r���h�̂Ƃ�����
	SetMainWindowText("�f�o�b�O�E�B���h�E");
	SetWindowSizeExtendRate(1.0);
	ChangeWindowMode(TRUE); // Window���[�h�̏ꍇ
#endif
	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	Game game;
	try {
		game.Initialize();
	}
	catch (const std::exception& e) {
		MessageBox(NULL, e.what(), "Initialization Error", MB_OK);
		DxLib_End();
		return -1;
	}
	//AppInit();	//������
	int mStartTime = GetNowCount();
	while (ProcessMessage() >= 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ) {
		int cur = GetNowCount();
		if (cur < mStartTime + 16) //120fps�΍�
			continue;
		mStartTime = cur;
		//AppUpdate();	//����
		ClearDrawScreen();
		game.HandleInput(); // �O�q���p�q�����{�p �r�r���t�p
		game.Update();      // �O�q�~���r�|�u�~�y�u �������������~�y��
		game.Render();      // �O�����y�����r�{�p
		//AppDraw();	//�`��
		ScreenFlip();
	}
	//AppRelease();
	game.Cleanup();
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
} 