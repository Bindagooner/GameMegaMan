#include "GameObject.h"

int CGameObject::getID()
{
	return _id;
}

int CGameObject::getIDType()
{
	return _idType;
}

void CGameObject::setID(int id)
{
	_id = id;
}

void CGameObject::setIDType(int id)
{
	_idType = id;
}

CStaticGameObject::CStaticGameObject(int id, int idtype, D3DXVECTOR2 size, D3DXVECTOR2 pos)
{
	_id = id;
	_idType = idtype;
	_size = size;
	_position = pos;
}

void CStaticGameObject::updateBox()
{
	_box.x = _position.x - _size.x / 2.0f;
	_box.y = _position.y + _size.y / 2.0f;
	_box.vX = 0;
	_box.vY = 0;
	_box.height = _size.x;
	_box.width = _size.y;
}

void CDynamicGameObject::updateBox()
{

}

D3DXVECTOR2 CGameObject::getPos()
{
	return _position;
}

void CGameObject::setPosition(D3DXVECTOR2 pos)
{
	_position = pos;
}

CGameObject::CGameObject()
{
}

Box CGameObject::getBox()
{
	return _box;
}

CGameObject::~CGameObject()
{
}


void CDynamicGameObject::draw(float anim_rate)
{
	_pSprite->draw(_position);
}

float CDynamicGameObject::checkCollision(CGameObject* gameObj, float& normalX, float& normalY, float anim_rate)
{
	float timeCollision = anim_rate;
	Box mybox = this->getBox();
	Box objbox = gameObj->getBox();

	mybox.vX -= objbox.vX;
	mybox.vY -= objbox.vY;
	objbox.vX = 0.0f;
	objbox.vY = 0.0f;

	Box sweptbroadphasebox = CCollision::getSweptBroadphaseBox(mybox, anim_rate);

	if (CCollision::checkBeforeAABB(sweptbroadphasebox, objbox))
	{
		timeCollision = CCollision::SweepAABB(sweptbroadphasebox, objbox, normalX, normalY, anim_rate);

		if (timeCollision = anim_rate && CCollision::checkBeforeAABB(mybox, objbox))
			return 0;
	}

	return timeCollision;
}