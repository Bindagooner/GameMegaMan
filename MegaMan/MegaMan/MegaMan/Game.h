#ifndef _GAME_H_
#define _GAME_H_

#include "GameWindows.h"
#include "DXGraphic.h"
#include "MegaMan.h"
#include "PlayingScreen.h"
class CGame
{
private:
	//CGameWindows *pGameWindows;
	//CDXGraphic *pDXGraphic;

	// timer stuff
	LARGE_INTEGER timeStart;
	LARGE_INTEGER timeEnd;
	LARGE_INTEGER timerFreq;
	float         anim_rate;
	CMegaMan *pMegaMan;
	//
	// test
	// 
	CPlayingScreen *_playScreen;
public:
	
	bool initGame(HINSTANCE hInstance);
	void run();
	void render(float);
	void update(float);
	CGame();
	~CGame();
	
};

#endif