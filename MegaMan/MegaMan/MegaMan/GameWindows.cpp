#include "GameWindows.h"

CGameWindows* CGameWindows::_instance = NULL;

CGameWindows::CGameWindows()
{
}


CGameWindows::~CGameWindows()
{
}

bool CGameWindows::initWindows(HINSTANCE hInstance)
{
	_hInstance = hInstance;
	WNDCLASSEX wcex;
	// Xác lập thuộc tính đối tượng kiểu WNDCLASSEX structure. Các thuộc tính này sẽ tác
	// động tới cách thể hiện của cửa sổ chương trình
	wcex.cbSize = sizeof(WNDCLASSEX); // hàm sizeof() trả về kích thước của một đối
	//tượng kiểu dữ liệu đầu vào – đơn vị tính là byte
	wcex.style = CS_HREDRAW | CS_VREDRAW; // xác lập kiểu lớp
	wcex.lpfnWndProc = (WNDPROC)CGameWindows::WinProc; // xác lập tên hàm gọi lại callback procedure
	wcex.cbClsExtra = 0; // xác lập số byte cấp phát thêm cho Class
	wcex.cbWndExtra = 0; // xác lập số byte cấp phát thêm cho mỗi instance của Class
	wcex.hInstance = _hInstance; // con trỏ (handle) trỏ tới instance của ứng dụng
	wcex.hIcon = 0; //loại biểu tượng chương trình
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// xác lập kiểu con trỏ chuột mặc định
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // màu nền của cửa sổ
	wcex.lpszMenuName = NULL; // con trỏ trỏ tới object dữ liệu thực đơn ứng dụng
	wcex.lpszClassName = GAME_NAME; // tên lớp đăng ký với hệ thống
	wcex.hIconSm = 0; // con trỏ tới dữ liệu biểu tượng cửa sổ ứng dụng
	
	RegisterClassEx(&wcex); //gọi hàm đăng ký lớp với hệ thống
	
	// Tạo cửa sổ mới
	_wndHandle = CreateWindow(
		GAME_NAME, //tên lớp sử dụng đã khai báo và đăng ký ở trên
		GAME_NAME, //tiêu đề của cửa sổ chương trình
		WS_OVERLAPPEDWINDOW, //loại của sổ chương trình
		CW_USEDEFAULT, // toạ độ X của của sổ khi xuất hiện
		CW_USEDEFAULT, // toạ độ Y của của sổ khi xuất hiện
		SCREEN_WIDTH, // kích thước bề ngang của cửa sổ - đơn vị là pixel
		SCREEN_HEIGHT, // kích thước chiều cao của cửa sổ
		NULL, // con trỏ trỏ tới đối tượng cha ;
		//NULL = đối tượng quản lý là desktop của Windows
		NULL, // con trỏ đối tượng menu của chương trình; NULL = không sử dụng
		_hInstance, // con trỏ instance của ứng dụng
		NULL); // không có giá trị gì được truyền cho cửa sổ
	
	// Kiểm tra lại xem quá trinh khởi tạo cửa sổ có thành công hay không
	if (!_wndHandle)
		return false;
	// Thể hiện cửa sổ lên màn hình Window
	ShowWindow(_wndHandle, SW_SHOWNORMAL);
	UpdateWindow(_wndHandle);
	return true;
}


LRESULT CALLBACK CGameWindows::WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	// Kiểm tra xem có thông điệp nào được gửi tới hàng đợi cửa ứng dụng không
	switch (message) //lọc các thông điệp
	{
	case WM_DESTROY: //bắt thông điệp yêu cầu kết thúc ứng dụng
		PostQuitMessage(0); //gọi hàm xử lý
		break;
	}
	// Chú ý, hàm này yêu cầu bạn phải cung cấp thông điệp trả về cho quá trình
	// xứ lý tiếp theo
	return DefWindowProc(hWnd, message, wParam, lParam);
}

HINSTANCE CGameWindows::getHInstance()
{
	return this->_hInstance;
}

HWND CGameWindows::getHWND()
{
	return _wndHandle;
}

CGameWindows * CGameWindows::getInstance()
{
	if (_instance == NULL)
		_instance = new CGameWindows();
	return _instance;
}

void CGameWindows::run()
{
	MSG msg;
	int done = 0;
	//m_pTimer->StartCount();

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		//else
		//{
		//	if (m_pTimer->GetTime() < 1.0f)
		//	{
		//		m_pTimer->EndCount();
		//		// Get Stage hiện tại và run.
		//		CGameStateManager::GetInstance()->GetCurrentState()->Run(m_pTimer->GetTime());
		//	}
		//}
	}
}