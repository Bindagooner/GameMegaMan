#include "Texture.h"
using namespace std;

/// <summary>
/// Initializes a new instance of the <see cref="CTexture" ( use for sprite )/> class.
/// </summary>
/// <param name="pD3Ddv">The p d3 DDV.</param>
/// <param name="cols">The cols.</param>
/// <param name="rows">The rows.</param>
CTexture::CTexture(LPDIRECT3DDEVICE9 pD3Ddv, int cols, int rows)
{
	this->_pD3Ddv = pD3Ddv;
	_cols = cols;
	_rows = rows;
}

/// <summary>
/// Initializes a new instance of the <see cref="CTexture" ( load background, columns = rows = 1 )/> class.
/// </summary>
/// <param name="pD3Ddv">The p d3 DDV.</param>
/// <param name="filepath">The filepath.</param>
CTexture::CTexture(LPDIRECT3DDEVICE9 pD3Ddv, string filepath)
{
	this->_pD3Ddv = pD3Ddv;
	this->loadTexture(filepath);
	_cols = 1;
	_rows = 1;
}


CTexture::~CTexture()
{

}
/// <summary>
/// Loads the texture.
/// </summary>
/// <param name="filepath">The filepath.</param>
/// <returns></returns>
bool CTexture::loadTexture(string filepath)
{
	
	D3DXIMAGE_INFO imgInfo;
	HRESULT hr;
	ZeroMemory(&imgInfo, sizeof(imgInfo));
	//lấy thông tin về hình ảnh
	
	hr = D3DXGetImageInfoFromFile(filepath.c_str(), &imgInfo);
	if (hr != D3D_OK) return false;

	//tạo texture
	hr = D3DXCreateTextureFromFileEx(
		this->_pD3Ddv,
		filepath.c_str(),
		imgInfo.Width,
		imgInfo.Height,
		1,
		D3DUSAGE_DYNAMIC,
		D3DFMT_UNKNOWN,// tự động chọn format phù hợp
		D3DPOOL_DEFAULT, //Chọn bộ nhớ để lưu tự động
		D3DX_DEFAULT,//Chọn tham số mặc định
		D3DX_DEFAULT,//Chọn tham số mặc định
		D3DCOLOR_XRGB(255, 255, 255), // màu để tẩy
		&imgInfo,
		NULL,
		&_pTexture);

	if (hr != D3D_OK) return false;

	_textureWidth = imgInfo.Width;
	_textureHeight = imgInfo.Height;

	return true;
}

float CTexture::getOneWidth()
{
	return _textureWidth / _cols;
}

float CTexture::getOneHeight()
{
	return _textureHeight / _rows;
}

int CTexture::getNumberOfColumn()
{
	return _cols;
}

/// <summary>
/// Draws the full of texture.
/// </summary>
/// <param name="position">The vector position.</param>
/// <param name="color">The color.</param>
void CTexture::drawTexture(D3DXVECTOR2 position, D3DCOLOR color)
{
	LPD3DXSPRITE spritehandle = CDXGraphic::getInstance()->getSpriteHandle();

	D3DXVECTOR2 posToDraw = CCamera::getInstance()->transform(position);

	spritehandle->Draw(_pTexture,
		NULL,
		NULL,
		&D3DXVECTOR3(posToDraw.x, posToDraw.y, 0),
		color
		);
}

/// <summary>
/// ve mot phan texture.
/// </summary>
/// <param name="rect">The rect.</param>
/// <param name="position">The position.</param>
/// <param name="color">The color.</param>
void CTexture::drawTexture(RECT rect, D3DXVECTOR2 position, D3DCOLOR color)
{
	LPD3DXSPRITE spritehandle = CDXGraphic::getInstance()->getSpriteHandle();

	D3DXVECTOR3 center;
	center.x = (rect.right - rect.left) / 2;
	center.y = (rect.bottom - rect.top) / 2;
	center.z = 0;

	D3DXVECTOR2 posToDraw = CCamera::getInstance()->transform(position);

	spritehandle->Draw(_pTexture,
		&rect,
		&center,
		&D3DXVECTOR3(posToDraw.x, posToDraw.y, 0),
		color
		);

	
}

/// <summary>
/// Draws the texture flip ( vd dùng để vẽ megaman lúc quay sang trái ).
/// </summary>
/// <param name="rect">The rect.</param>
/// <param name="position">The position.</param>
/// <param name="angle">The angel.</param>
/// <param name="color">The color.</param>
void CTexture::drawTextureFlipZ(RECT rect, D3DXVECTOR2 position, float angle, D3DCOLOR color)
{
	D3DXVECTOR2 posToDraw = CCamera::getInstance()->transform(position);
	LPD3DXSPRITE spritehandle = CDXGraphic::getInstance()->getSpriteHandle();

	D3DXVECTOR3 center((rect.right - rect.left) / 2,
		(rect.bottom - rect.top) / 2, 
		0.0f);

	D3DXVECTOR2 scaling( -1.0f, 1.0f);

	D3DXMATRIX oldMatrix;
	spritehandle->GetTransform(&oldMatrix);
	D3DXMATRIX newMatrix;

	D3DXMatrixTransformation2D(&newMatrix, NULL, NULL, &scaling, NULL, angle, &posToDraw);

	spritehandle->SetTransform(&newMatrix);

	spritehandle->Draw(_pTexture, &rect, &center, NULL, color);

	D3DXMatrixRotationZ(&newMatrix, angle);
	
	spritehandle->SetTransform(&oldMatrix);
}

