#pragma once
#include "DefineValue.h"
#include "DXGraphic.h"
#include "DXInput.h"
#include "Sprite.h"
#include "Texture.h"
#include "GameObject.h"
#include "Camera.h"

#include <map>
using namespace std;

class CMegaMan : public CDynamicGameObject
{
private:
	// trạng thái megaman
	enum Status
	{
		Ground, // đứng trên mặt đất
		Jump,	// nhảy
	};

	// hướng của megaman
	enum Direction
	{
		None, // khong bam gi
		Forward, // bam sang phai, trai
		Up,		// bam phim len
		Down,	// bam phim xuong
	};

	Status _status; // trạng thái megaman
	Direction _direction; // hướng di chuyển megaman
	/*CSprite *_pCSpriteRun;
	CSprite *_pCSpriteStand;
	CSprite *_pCSpriteJump;*/

	map<int, CSprite*> _mapSprite; // map luu tat ca sprite cua megaman;
	bool _isRight = true;
	bool _isStand = true;

	void RespondTopCollision(CGameObject* topObj,float topTime);
	void RespondBotCollision(CGameObject* botObj, float botTime);
	void RespondLeftCollision(CGameObject* leftObj, float leftTime);
	void RespondRightCollision(CGameObject* rightObj, float rightTime);
public:
	Status getStatus()
	{
		return _status;
	};
	void update(float anim_rate);
	void updateKeyboard(float anim_rate);
	void updateStatus(float anim_rate);
	void updateAnimation(float anim_rate);
	void updateBox(float anim_rate);

	void updateCollision(vector<CGameObject*>, float anim_rate);

	void draw(float anim_rate);
	CMegaMan();
	~CMegaMan();
};

