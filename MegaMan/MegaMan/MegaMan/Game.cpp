#include "Game.h"


CGame::CGame()
{
}


CGame::~CGame()
{
}

bool CGame::initGame(HINSTANCE hInstance)
{
	
	CGameWindows *pGameWindows = CGameWindows::getInstance();

	if (!pGameWindows->initWindows(hInstance)) return false;

	if (!CDXGraphic::getInstance()->init(pGameWindows->getHWND())) return false;

	if (!CDXInput::getInstance()->initInput(hInstance, pGameWindows->getHWND())) return false;

	_playScreen = new CPlayingScreen();

	return true;
}



void CGame::run()
{
	MSG msg;
	int done = 0;
	
	pMegaMan = new CMegaMan();

	QueryPerformanceFrequency(&timerFreq);
	float cycles_count_per_second = 1.0f / timerFreq.QuadPart;
	anim_rate = 0;
	float frame_rate = 1.0f / FRAME_RATE_MAX;
	QueryPerformanceCounter(&timeStart);

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			QueryPerformanceCounter(&timeEnd);
			anim_rate = ((float)timeEnd.QuadPart - (float)timeStart.QuadPart) * cycles_count_per_second;
			if (anim_rate >= frame_rate)
			{
				timeStart = timeEnd;
				update(anim_rate);
				render(anim_rate);
			}
		}

	}

}

void CGame::update(float anim_rate)
{
	CDXInput::getInstance()->getState();
	// test
	_playScreen->update(anim_rate);
	/*pMegaMan->update(CDXInput::getInstance(), anim_rate);*/
}

void CGame::render(float anim_rate)
{
	CDXGraphic::getInstance()->beginDraw();
//	CDXGraphic::getInstance()->render(anim_rate);
	_playScreen->draw();
///	pMegaMan->draw(anim_rate);
	CDXGraphic::getInstance()->endDraw();
}