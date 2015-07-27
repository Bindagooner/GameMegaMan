#include "DXGraphic.h"
#include "DefineValue.h"

CDXGraphic::CDXGraphic()
{
}

CDXGraphic* CDXGraphic::_instance = NULL;

CDXGraphic::~CDXGraphic()
{
	if (_pD3D) delete _pD3D;
	if (_pd3dDevice) delete _pd3dDevice;
	if (_pD3DSprite) delete _pD3DSprite;

}

bool CDXGraphic::init(HWND hWnd)
{
	_pD3D = NULL;
	_pd3dDevice = NULL;
	_pD3DSprite = NULL;

	// create the directX object
	if ((_pD3D = Direct3DCreate9(D3D_SDK_VERSION)) == NULL) return false;

	// fill the presentation parameters structure
	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));
	
	// Khởi tạo các thuộc tính cho d3dpp.
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_X8R8G8B8;
	d3dpp.BackBufferCount = 1;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	
	if (FAILED(_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &_pd3dDevice) ) )
		return false;
	if (FAILED(_pd3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &_pBackBuffer))) return false;

	if (FAILED(D3DXCreateSprite(_pd3dDevice, &_pD3DSprite))) return false;

	return true;

}

LPD3DXSPRITE CDXGraphic::getSpriteHandle()
{
	return _pD3DSprite;
}

void CDXGraphic::beginDraw()
{
	if (NULL == _pd3dDevice)
		return;

	if (_pd3dDevice->BeginScene())
		return;
	// Xoá toàn bộ bộ đệm màn hình về trạng thái mầu đen
	_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,
		D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	// đổ màu
	_pd3dDevice->ColorFill(_pBackBuffer, NULL, D3DCOLOR_XRGB(151, 255, 232));
	_pD3DSprite->Begin(D3DXSPRITE_ALPHABLEND);
}

void CDXGraphic::endDraw()
{
	_pD3DSprite->End();
	_pd3dDevice->EndScene();
	_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}

void CDXGraphic::render(float anim_rate)
{
	// Kiểm tra xem chắc chắn thiết bị Direct3D đã được tạo hay chưa
	if (NULL == _pd3dDevice)
		return;
	//// Xoá toàn bộ bộ đệm màn hình về trạng thái mầu đen
	//_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET,
	//	D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	
	// Thể hiện dữ liệu bộ đệm lên màn hình
	//_pd3dDevice->Present(NULL, NULL, NULL, NULL);

}

CDXGraphic * CDXGraphic::getInstance()
{
	if (_instance == NULL) _instance = new CDXGraphic();
	return _instance;
}

LPDIRECT3DDEVICE9 CDXGraphic::getDevice()
{ 
	return _pd3dDevice;
}