#include "MegaMan.h"


CMegaMan::CMegaMan()
{
	/*_pCSpriteRun = new CSprite(CDXGraphic::getInstance()->getDevice(), FILEPATH_MEGAMAN_RUN, 3, 1);
	_pCSpriteStand = new CSprite(CDXGraphic::getInstance()->getDevice(), FILEPATH_MEGAMAN_STAND, 3, 1);
	_pCSpriteJump = new CSprite(CDXGraphic::getInstance()->getDevice(), FILEPATH_MEGAMAN_JUMP, 1, 1);*/

	_mapSprite[ID_MEGAMAN_RUN] = new CSprite(CDXGraphic::getInstance()->getDevice(), FILEPATH_MEGAMAN_RUN, 3, 1, 100);
	_mapSprite[ID_MEGAMAN_STAND] = new CSprite(CDXGraphic::getInstance()->getDevice(), FILEPATH_MEGAMAN_STAND, 3, 1, 200);
	_mapSprite[ID_MEGAMAN_JUMP] = new CSprite(CDXGraphic::getInstance()->getDevice(), FILEPATH_MEGAMAN_JUMP, 1, 1, 100);

	_isRight = true;
	_1stTime = true;
	_direction = Direction::None;
	_status = Status::Start;
	_a.x = 0.0f;
	_a.y = -GRAVITY;
	_v.x = 0.0f;
	_v.y = -MEGAMAN_VELOCITY_Y;
}


CMegaMan::~CMegaMan()
{
}



void CMegaMan::update(float anim_rate)
{
	updateStatus(anim_rate);
	updateKeyboard(anim_rate);
	updateAnimation(anim_rate);
	_pSprite->update(anim_rate);
	updateBox(anim_rate);
}

void CMegaMan::updateKeyboard(float anim_rate)
{
	CDXInput *input = CDXInput::getInstance();
	if (input->isKeyDown(DIK_RIGHT))
	{
		_direction = Direction::Forward;
		_isRight = true;
		_v.x = MEGAMAN_VELOCITY_X;
		
	}
	else if (input->isKeyDown(DIK_LEFT))
	{
		_direction = Direction::Forward;
		_isRight = false;
		_v.x = -MEGAMAN_VELOCITY_X;
		
	}
	else
	{
		_direction = Direction::None;
		_v.x = 0;
	}

	if (input->isKeyDown(DIK_X))
	{
		if (_status == Status::Stand)
		{
			_status = Status::Jump;
			_v.x = MEGAMAN_VELOCITY_Y;
		}
	}
}

void CMegaMan::updateAnimation(float anim_rate)
{
	switch (_status)
	{
	case CMegaMan::Stand:
		if (_direction == Direction::None)
			_pSprite = _mapSprite[ID_MEGAMAN_STAND];
		else if (_direction == Direction::Forward)
			_pSprite = _mapSprite[ID_MEGAMAN_RUN];
		break;
	case CMegaMan::Jump:
		_pSprite = _mapSprite[ID_MEGAMAN_JUMP];
		break;
	default:
		break;
	}
}

void CMegaMan::updateBox(float anim_rate)
{
	_box.x = _position.x - _box.width / 2;
	_box.y = _position.y + _box.height / 2;
	_box.width = 16.0f;
	_box.height = 24.0f;

	if (!_isRight)
	{
		float x = _box.x - (_box.x - _pSprite->getWidthSprite() / 2.0f);
		_box.x = _box.x + _pSprite->getWidthSprite() / 2.0f - x - _box.width;
	}

	_box.vX = _v.x;
	_box.vY = _v.y;
}

void CMegaMan::updateStatus(float anim_rate)
{

}

void CMegaMan::updateCollision(vector<CGameObject*> objectsToCollision, float anim_rate)
{
	float timeCollision = anim_rate;
	float normalX = 0.0f, normalY = 0.0f;

#pragma region xét va chạm trong quadtree
	float topTime, rightTime, leftTime, botTime;
	topTime = rightTime = leftTime = botTime = anim_rate;
	CGameObject* topObj = NULL;
	CGameObject* rightObj = NULL;
	CGameObject* leftObj = NULL;
	CGameObject* botObj = NULL;

	for (int i = 0; i < objectsToCollision.size(); i++)
	{
		CGameObject* gameObj = objectsToCollision[i];
		normalX = normalY = 0.0f;

		float t = checkCollision(gameObj, normalX, normalY, anim_rate);

		if (t < anim_rate) // có xảy ra va chạm
		{
			/*switch (gameObj->getIDType())
			{
			case ID_BLOCK:*/
			if (normalY == 1 && t < botTime) // Va chạm từ trên xuống.
			{
				botTime = t;
				botObj = gameObj;
			}
			else if (normalY == -1 && t < topTime) // Va chạm từ dưới lên.
			{
				topTime = t;
				topObj = gameObj;
			}
			else if (normalX == 1 && t < rightTime) // Va chạm từ phải qua trái.
			{
				rightTime = t;
				rightObj = gameObj;
			}
			else if (normalX == -1 && t < leftTime) // Va chạm từ trái qua phải.
			{
				leftTime = t;
				leftObj = gameObj;
			}
			if (topObj != NULL)
				RespondTopCollision(topObj, topTime);
			if (botObj != NULL)
				RespondBotCollision(botObj, botTime);
			if (leftObj != NULL)
				RespondLeftCollision(leftObj, leftTime);
			if (rightObj != NULL)
				RespondRightCollision(rightObj, rightTime);
		}
	}

	/*if (topObj != NULL)
		RespondTopCollision(topObj, topTime);
	if (botObj != NULL)
		RespondBotCollision(botObj, botTime);
	if (leftObj != NULL)
		RespondLeftCollision(leftObj, leftTime);
	if (rightObj != NULL)
		RespondRightCollision(rightObj, rightTime);*/

#pragma endregion


	// update vị trí
	_position += _v * anim_rate;
	_v += _a *anim_rate;
}

void CMegaMan::RespondBotCollision(CGameObject* botObj, float botTime)
{
	switch (botObj->getIDType())
	{
	case ID_BLOCK:
		if (_status == Status::Jump)
		{
			_status = Status::Stand;
		}
		_position.y += _v.y * botTime;
		_v.y = 0.0f;
		break;
	case ID_FALLING_POINT:
		if (_status == Status::Start)
		{
			if (_1stTime)
			{
				_status = Status::Stand;
				_a.x = 0;
				_a.y = 0;
			}
		}
		else {
			_status = Status::Jump;
			_a.y = -GRAVITY;
		}
		break;
	default:
		break;
	}
}

void CMegaMan::RespondTopCollision(CGameObject* topObj, float topTime)
{

}

void CMegaMan::RespondRightCollision(CGameObject* rightObj, float rightTime)
{

}

void CMegaMan::RespondLeftCollision(CGameObject* leftObj, float leftTime)
{

}

void CMegaMan::draw(float anim_rate)
{
	//D3DXVECTOR2 pos = CCamera::getInstance()->transform(_position);
	/*if (_isStand && _isRight) 
		_pCSpriteStand->draw(_position);
	else if (_isStand && !_isRight)
		_pCSpriteStand->drawFlipZ(0.0f, _position);
	else
		if (!_isStand && _isRight) _pCSpriteRun->draw(_position);
		else _pCSpriteRun->drawFlipZ(0.0f, _position);*/

	if (_isRight)
		_pSprite->draw(_position);
	else _pSprite->drawFlipZ(0.0f, _position);

}