#include "Sprite.h"
using namespace std;

/// <summary>
/// Initializes a new instance of the <see cref="CSprite"/> class.
/// </summary>
/// <param name="pD3Ddv">The p d3 DDV.</param>
/// <param name="filepath">The filepath.</param>
/// <param name="cols">The cols.</param>
/// <param name="rows">The rows.</param>
CSprite::CSprite(LPDIRECT3DDEVICE9 pD3Ddv, string filepath, int cols, int rows, float timeAnimation)
{
	_pCTexture = new CTexture(pD3Ddv, cols, rows);
	_pCTexture->loadTexture(filepath);
	_widthSprite = _pCTexture->getOneWidth();
	_heightSprite = _pCTexture->getOneHeight();
	
	// _minIndex = 0;
	_minIndex = 0;

	// _maxIndex = cols * rows - 1; vd: 1*3 = 3 -1 =2 
	_maxIndex = cols * rows - 1;

	// test timeAmination
	_timeAnimation = timeAnimation;
	_timeLocal = 0;
}


CSprite::~CSprite()
{
}

void CSprite::update(float anim_rate)
{
	_timeLocal += anim_rate;
	if (_timeLocal >= _timeAnimation / 1000.0f) {
		_timeLocal = 0;
		this->next();
	}
}


void CSprite::next()
{
	_curIndex++;
	if (_curIndex > _maxIndex)
		_curIndex = _minIndex;
}

void CSprite::reset()
{
	_curIndex = 0;
}

void CSprite::draw(D3DXVECTOR2 position)
{
	RECT rect;
	int cols = _pCTexture->getNumberOfColumn();
	rect.top = (_curIndex / cols) * _heightSprite;
	rect.bottom = rect.top + _heightSprite;
	rect.left = (_curIndex % cols) * _widthSprite;
	rect.right = rect.left + _widthSprite;

	_pCTexture->drawTexture(rect, position, D3DCOLOR_XRGB(255, 255, 255));
}

void CSprite::drawFlipZ(float angle, D3DXVECTOR2 position)
{
	RECT rect;

	int cols = _pCTexture->getNumberOfColumn();
	rect.top = (_curIndex / cols) * _heightSprite;
	rect.bottom = rect.top + _heightSprite;
	rect.left = (_curIndex % cols) * _widthSprite;
	rect.right = rect.left + _widthSprite;

	_pCTexture->drawTextureFlipZ(rect, position, 0.0f, D3DCOLOR_XRGB(255, 255, 255));

}

float CSprite::getWidthSprite()
{
	return _widthSprite;
}

float CSprite::getHeightSprite()
{
	return _heightSprite;
}