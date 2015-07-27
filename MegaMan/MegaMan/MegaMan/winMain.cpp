
#include "Game.h"

//HINSTANCE hInst; // khai báo biến toàn cục chứa con trỏ instance (biến thể) của chương trình
//HWND wndHandle; // biến toàn cục chứa con trỏ quản lý cửa sổ ứng dụng
//
//// khai báo hàm
//
//bool initWindow(HINSTANCE hInstance);
//LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
//
//bool initWindow(HINSTANCE hInstance)
//{
//	WNDCLASSEX wcex;
//	// Xác lập thuộc tính đối tượng kiểu WNDCLASSEX structure. Các thuộc tính này sẽ tác
//	// động tới cách thể hiện của cửa sổ chương trình
//	wcex.cbSize = sizeof(WNDCLASSEX); // hàm sizeof() trả về kích thước của một đối
//	//tượng kiểu dữ liệu đầu vào – đơn vị tính là byte
//	wcex.style = CS_HREDRAW | CS_VREDRAW; // xác lập kiểu lớp
//	wcex.lpfnWndProc = (WNDPROC)WndProc; // xác lập tên hàm gọi lại callback procedure
//	wcex.cbClsExtra = 0; // xác lập số byte cấp phát thêm cho Class
//	wcex.cbWndExtra = 0; // xác lập số byte cấp phát thêm cho mỗi instance của Class
//	wcex.hInstance = hInstance; // con trỏ (handle) trỏ tới instance của ứng dụng
//	wcex.hIcon = 0; //loại biểu tượng chương trình
//	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);// xác lập kiểu con trỏ chuột mặc định
//	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1); // màu nền của cửa sổ
//	wcex.lpszMenuName  = NULL; // con trỏ trỏ tới object dữ liệu thực đơn ứng dụng
//	wcex.lpszClassName = "DirectXExample"; // tên lớp đăng ký với hệ thống
//	wcex.hIconSm = 0; // con trỏ tới dữ liệu biểu tượng cửa sổ ứng dụng
//	RegisterClassEx(&wcex); //gọi hàm đăng ký lớp với hệ thống
//	// Tạo cửa sổ mới
//	wndHandle = CreateWindow(
//		"DirectXExample", //tên lớp sử dụng đã khai báo và đăng ký ở trên
//		"DirectXExample", //tiêu đề của cửa sổ chương trình
//		WS_OVERLAPPEDWINDOW, //loại của sổ chương trình
//		CW_USEDEFAULT, // toạ độ X của của sổ khi xuất hiện
//		CW_USEDEFAULT, // toạ độ Y của của sổ khi xuất hiện
//		640, // kích thước bề ngang của cửa sổ - đơn vị là pixel
//		480, // kích thước chiều cao của cửa sổ
//		NULL, // con trỏ trỏ tới đối tượng cha ;
//		//NULL = đối tượng quản lý là desktop của Windows
//		NULL, // con trỏ đối tượng menu của chương trình; NULL = không sử dụng
//		hInstance, // con trỏ instance của ứng dụng
//		NULL); // không có giá trị gì được truyền cho cửa sổ
//	// Kiểm tra lại xem quá trinh khởi tạo cửa sổ có thành công hay không
//	if (!wndHandle)
//		return false;
//	// Thể hiện cửa sổ lên màn hình Window
//	ShowWindow(wndHandle, SW_SHOW);
//	UpdateWindow(wndHandle);
//	return true;
//}
//
//LRESULT CALLBACK WndProc(HWND hWnd, UINT message,
//	WPARAM wParam, LPARAM lParam)
//{
//	// Kiểm tra xem có thông điệp nào được gửi tới hàng đợi cửa ứng dụng không
//	switch (message) //lọc các thông điệp
//	{
//	case WM_DESTROY: //bắt thông điệp yêu cầu kết thúc ứng dụng
//		PostQuitMessage(0); //gọi hàm xử lý
//		break;
//	}
//	// Chú ý, hàm này yêu cầu bạn phải cung cấp thông điệp trả về cho quá trình
//	// xứ lý tiếp theo
//	return DefWindowProc(hWnd, message, wParam, lParam);
//}
// Đây là hàm winmain, hàm được gọi đầu tiền của mọi ứng dụng trong window

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{

	//CGameWindows* windows = new CGameWindows();
	//// khởi tạo cửa sổ ứng dụng
	//windows->initWindows(hInstance);
	//windows->run(); 
	
	CGame *pGame = new CGame();

	pGame->initGame(hInstance);
	pGame->run();

	return 1;
}


