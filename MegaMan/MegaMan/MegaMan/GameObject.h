#pragma once

#include "DefineValue.h"
#include "DXGraphic.h"
#include "DXInput.h"
#include "Sprite.h"
#include "Texture.h"
#include "Collision.h"

class CGameObject
{
protected:	
	CSprite *_pSprite;
	D3DXVECTOR2 _position; // vi tri cua moi doi tuong game. (CGameObejct)
	//RECT _rect; // hinh chu nhat ve doi tuong.
	Box _box; // box bao đối tượng để xét va chạm.
	int _id; // id doi tuong
	int _idType; // id loai doi tuong
	D3DXVECTOR2 _size; // kich thuoc doi tuong
	
public:
	void setID(int id);
	void setIDType(int idtype);
	int getID();
	int getIDType();
	CGameObject();
	virtual ~CGameObject();
	D3DXVECTOR2 getPos();
	void setPosition(D3DXVECTOR2);
	Box getBox();
	virtual void updateBox() = 0;
	/*virtual void update(float anim_rate);
	virtual void draw();*/
};


class CDynamicGameObject : public CGameObject
{
protected:	
	D3DXVECTOR2 _v; // van toc
	D3DXVECTOR2 _a; // gia toc
public:
	void updateBox() override;
	float checkCollision(CGameObject*, float& normalX, float& normalY, float anim_rate);

	void update(float anim_rate);
	void draw(float anim_rate);
};


class CStaticGameObject : public CGameObject
{
public:
	CStaticGameObject(int id, int idtype, D3DXVECTOR2 size, D3DXVECTOR2 pos);
	void draw();
	void updateBox() override;
};