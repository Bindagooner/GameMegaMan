#include "DXInput.h"

CDXInput* CDXInput::_instance = NULL;

CDXInput::CDXInput()
{
	this->_pInput = NULL;
	this->_pInputDdv = NULL;
}


CDXInput::~CDXInput()
{
	if (_pInput) delete _pInput;
	if (_pInputDdv) delete _pInputDdv;
}

CDXInput* CDXInput::getInstance(){
	if (_instance == NULL)
		_instance = new CDXInput();
	return _instance;
}

bool CDXInput::initInput(HINSTANCE hIns, HWND hwnd)
{
	ZeroMemory(_key_buffer, sizeof(_key_buffer));
	HRESULT result;
	result = DirectInput8Create(
		hIns,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&_pInput,
		NULL);
	if (FAILED(result)) return false;

	//tạo bàn phím. GUID_SysKeyboard là chỉ bàn phím. Nếu bạn có một thiết bị cho riêng mình thì bạn phải định nghĩa nó trước
	result = _pInput->CreateDevice(
		GUID_SysKeyboard,
		&_pInputDdv,
		NULL);

	if (FAILED(result)) return false;

	//dạng dữ liệu sẽ được nhận
	result = this->_pInputDdv->SetDataFormat(&c_dfDIKeyboard);

	if (FAILED(result)) return false;

	//loại hoạt động. DISCL_FOREGROUND nghĩa là chỉ hoạt động khi của sổ hWnd đang được handle
	result = this->_pInputDdv->SetCooperativeLevel(hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(result))
		return false;

	DIPROPDWORD dipdw;

	dipdw.diph.dwSize = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj = 0;
	dipdw.diph.dwHow = DIPH_DEVICE;
	dipdw.dwData = KEYBOARD_BUFFER_SIZE; // Arbitary buffer size

	result = this->_pInputDdv->SetProperty(DIPROP_BUFFERSIZE, &dipdw.diph);
	if (FAILED(result)) return false;

	//Yêu cầu thiết bị
	result = this->_pInputDdv->Acquire();
	if (FAILED(result))
		return false;
	return true;

}

void CDXInput::getState()
{
	HRESULT hr = this->_pInputDdv->GetDeviceState(sizeof(_key_buffer), &_key_buffer);
	if (FAILED(hr)) {
		//nếu bàn phím đang bị nhả ra thì yêu cầu lại
		while (this->_pInputDdv->Acquire() == DIERR_INPUTLOST)
		{
			this->_pInputDdv->Acquire();
			this->_pInputDdv->GetDeviceState(sizeof(_key_buffer), &_key_buffer);
		}

	}

	_dwElements = KEYBOARD_BUFFER_SIZE;
	this->_pInputDdv->GetDeviceData(sizeof(DIDEVICEOBJECTDATA), _keyEvents, &_dwElements, 0);
}

int CDXInput::isKeyDown(int key, bool isFromBuffer)
{
	if(isFromBuffer) // lấy trong hàng đợi
	{
		for (DWORD i = 0; i < _dwElements; i++)
		{
			int keyCodeBuffer = _keyEvents[i].dwOfs;
			int keyState = _keyEvents[i].dwData;

			if ((keyCodeBuffer == key) && (keyState & 0x80) > 0)
				return 1;
		}
	}
	else // lấy tức thời
		return ((_key_buffer[key]) & 0x80) > 0;
	return 0;
}

int CDXInput::isKeyRelease(int key, bool isFromBuffer)
{
	if (isFromBuffer) // lấy trong hàng đợi
	{
		for (DWORD i = 0; i < _dwElements; i++)
		{
			int keyCodeBuffer = _keyEvents[i].dwOfs;
			int keyState = _keyEvents[i].dwData;

			if ((keyCodeBuffer == key) && (keyState & 0x80) == 0)
				return 1;
		}
	}
	else // lấy tức thời
		return _key_buffer[key] & 0x80 == 0;
	return 0;
}