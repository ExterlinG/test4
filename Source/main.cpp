#include <DxLib.h>
#include "App.h"
#include "Game.h"

// ƒvƒƒOƒ‰ƒ€‚Í WinMain ‚©‚çŽn‚Ü‚è‚Ü‚·
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	SetGraphMode(800, 600, 32);
	SetOutApplicationLogValidFlag(FALSE); // ƒƒO‚ðo‚³‚È‚¢
#if _DEBUG // ƒfƒoƒbƒOƒrƒ‹ƒh‚Ì‚Æ‚«‚¾‚¯
	SetMainWindowText("ƒfƒoƒbƒOƒEƒBƒ“ƒhƒE");
	SetWindowSizeExtendRate(1.0);
	ChangeWindowMode(TRUE); // Windowƒ‚[ƒh‚Ìê‡
#endif
	if (DxLib_Init() == -1)		// ‚c‚wƒ‰ƒCƒuƒ‰ƒŠ‰Šú‰»ˆ—
	{
		return -1;			// ƒGƒ‰[‚ª‹N‚«‚½‚ç’¼‚¿‚ÉI—¹
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
	//AppInit();	//‰Šú‰»
	int mStartTime = GetNowCount();
	while (ProcessMessage() >= 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0 ) {
		int cur = GetNowCount();
		if (cur < mStartTime + 16) //120fps‘Îô
			continue;
		mStartTime = cur;
		//AppUpdate();	//ˆ—
		ClearDrawScreen();
		game.HandleInput(); // „O„q„‚„p„q„€„„„{„p „r„r„€„t„p
		game.Update();      // „O„q„~„€„r„|„u„~„y„u „ƒ„€„ƒ„„„€„‘„~„y„‘
		game.Render();      // „O„„„‚„y„ƒ„€„r„{„p
		//AppDraw();	//•`‰æ
		ScreenFlip();
	}
	//AppRelease();
	game.Cleanup();
	DxLib_End();				// ‚c‚wƒ‰ƒCƒuƒ‰ƒŠŽg—p‚ÌI—¹ˆ—

	return 0;				// ƒ\ƒtƒg‚ÌI—¹ 
} 