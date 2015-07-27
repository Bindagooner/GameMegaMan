#ifndef _GAMEWINDOWS_
#define _GAMEWINDOWS_

#include <Windows.h>
#include "DefineValue.h"

/*********
windows class
*/
class CGameWindows
{

private:
	HINSTANCE _hInstance; // khai báo biến chứa con trỏ instance (biến thể) của chương trình
	HWND _wndHandle; // biến chứa con trỏ quản lý cửa sổ ứng dụng
	
	static CGameWindows * _instance; // con trỏ đến thực thể duy nhất của lớp
public:
	CGameWindows();
	~CGameWindows();
	bool initWindows(HINSTANCE hInstance);
	void run();
	HINSTANCE getHInstance();
	HWND getHWND();
	static CGameWindows* getInstance();

	static LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

#endif