#ifndef _DXINPUT_H_
#define _DXINPUT_H_

#include <dinput.h>

#define KEYBOARD_BUFFER_SIZE 1024

class CDXInput
{
private:
	LPDIRECTINPUT8 _pInput;
	LPDIRECTINPUTDEVICE8 _pInputDdv;	
	BYTE _key_buffer[256]; // buffer lưu dữ liệu từ bàn phím
	
	DIDEVICEOBJECTDATA _keyEvents[KEYBOARD_BUFFER_SIZE];

	DWORD _dwElements;

	static CDXInput * _instance;

public:
	bool initInput(HINSTANCE hIns, HWND hwnd);

	void getState();

	int isKeyDown(int key, bool isFromBuffer = false);

	int isKeyRelease(int key, bool isFromBuffer = false);

	static CDXInput* getInstance();

	CDXInput();
	~CDXInput();
};

#endif