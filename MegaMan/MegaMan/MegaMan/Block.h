#pragma once

#include "Collision.h"
#include "GameObject.h"
class CBlock : public CStaticGameObject
{
public:
	CBlock(int id, int idType, D3DXVECTOR2 size, D3DXVECTOR2 pos);
	~CBlock();
};

