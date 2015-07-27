#ifndef _DXGRAPHIC_H_
#define _DXGRAPHIC_H_

#include <d3d9.h>
#include <d3dx9.h>
class CDXGraphic
{
private:
	LPDIRECT3D9 _pD3D; //Đối tượng Direct3D
	LPDIRECT3DDEVICE9 _pd3dDevice; //thiết bị hiển thị Direct3D
	LPDIRECT3DSURFACE9 _pBackBuffer; // back buffer ở DXGraphic
	LPD3DXSPRITE _pD3DSprite; //sprite handler
	static CDXGraphic * _instance; // thuc the duy nhat
public:
	/*********************************************************************
	* initDirect3D
	* initializes direct3D
	*********************************************************************/
	bool init(HWND hWnd);

	void beginDraw();

	void endDraw();

	void render( float anim_rate);

	LPDIRECT3DDEVICE9 getDevice();

	LPD3DXSPRITE getSpriteHandle();

	static CDXGraphic* getInstance();

	CDXGraphic();

	~CDXGraphic();
};

#endif
