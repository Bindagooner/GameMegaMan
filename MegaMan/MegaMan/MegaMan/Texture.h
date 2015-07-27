#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <string>
#include "DXGraphic.h"
#include "Camera.h"

using namespace std;

class CTexture
{
private:
	LPDIRECT3DDEVICE9 _pD3Ddv;

	LPDIRECT3DTEXTURE9 _pTexture; // con tro luu texture hien tai

	int _cols;
	int _rows;
	float _textureWidth;
	float _textureHeight;

public:	
	bool loadTexture(string filepath);	
	CTexture(LPDIRECT3DDEVICE9 pD3Ddv, string filiepath);
	CTexture(LPDIRECT3DDEVICE9 pD3Ddv, int cols, int rows);	
	void drawTexture(D3DXVECTOR2 position, D3DCOLOR color); 	
	void drawTexture(RECT rect, D3DXVECTOR2 position, D3DCOLOR color);
	void drawTextureFlipZ(RECT rect, D3DXVECTOR2 position, float angel, D3DCOLOR color);	
	/// <summary>
	/// Gets the width of the one sprite: texturewidth/cols.
	/// </summary>
	/// <returns></returns>
	float getOneWidth();	
	/// <summary>
	/// Gets the height of the one sprite: textureheight/rows.
	/// </summary>
	/// <returns></returns>
	float getOneHeight();
	int getNumberOfColumn();
	~CTexture();
};

#endif