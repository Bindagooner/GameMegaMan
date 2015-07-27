#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "DefineValue.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"

using namespace std;

class CSprite
{
private:
	CTexture * _pCTexture;
	LPDIRECT3DTEXTURE9 *_lpTexture;
	float _anim_rate;
	int _curIndex;
	int _minIndex;
	int _maxIndex;
	float _widthSprite;
	float _heightSprite;

	float _timeAnimation;			/*Thời gian của hiệu ứng chuyển frame*/
	float _timeLocal;				/*Thời gian tính hiệu ứng chuyển frame*/
public:
	
	void update(float anim_rate);
	void draw(D3DXVECTOR2 position);		
	/// <summary>
	/// hàm vẽ lật sprite theo trục Z. 
	/// </summary>
	/// <param name="angle">The angle.</param>
	/// <param name="position">The position.</param>
	void drawFlipZ(float angle, D3DXVECTOR2 position);

	
	/// <summary>
	/// make sprite moving
	/// </summary>
	void next();	
	
	/// <summary>
	/// Reset curIndex to startIndex.
	/// </summary>
	void reset();

	float getWidthSprite();
	float getHeightSprite();

	CSprite(LPDIRECT3DDEVICE9 pD3Ddv, string filepath, int cols, int rows, float timeAnimation);
	~CSprite();
};

#endif
