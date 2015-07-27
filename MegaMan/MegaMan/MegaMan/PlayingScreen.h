#pragma once

#include <fstream>
#include <sstream>
#include <map>
#include <vector>

#include "GameObject.h"
#include "QuadNode.h"
#include "Camera.h"
#include "DefineValue.h"
#include "DXGraphic.h"
#include "DXInput.h"
#include "DXSound.h"
#include "Sprite.h"
#include "MegaMan.h"
#include "Block.h"

//
// man hinh luc dang choi
//
class CPlayingScreen
{
private:
	int _countRow, _countColumn, _totalTile; // số hàng , số cột, tổng số tile của ma trận background

	float _mapHeight, _mapWidth;
	vector<vector<int>> _tileMatrix;	// Ma trận lưu các tile background
	CTexture *_textureBackground;
	CMegaMan *_pMegaMan;
	CQuadNode* _quadNodeCollision;		// Cây tứ phân lưu các đối tượng va chạm trên màn hình
	
	vector<CGameObject*> _objectToCollision; // list đối tượng có thể va chạm trong viewport

public:
	void loadMap(int idLevel);
	void update(float anim_rate);
	void draw();
	void drawBackground(RECT viewport);
	CPlayingScreen();
	~CPlayingScreen();
};

