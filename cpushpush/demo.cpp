#include<windows.h>

//   HINSTANCE  实例的句柄.  加载资源需要用到HINSTANCE
//   HWND       窗口句柄     和窗口相关的操作
//   HDC        设备句柄     绘图的操作
LRESULT CALLBACK MyWinMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//回调函数（消息的）
{
	switch (uMsg)
	{
	case WM_CLOSE:          //自动退出
	{
		::PostQuitMessage(0);
	}
	break;
	}

	return  DefWindowProc(hWnd, uMsg, wParam, lParam); //返回消息的默认处理
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//设置画刷
	HBRUSH hBrush = ::CreateSolidBrush(RGB(62, 71, 98));

	//设计窗口
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = hBrush;
	wndclass.hCursor = 0;
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.lpfnWndProc = MyWinMain;
	wndclass.lpszClassName = "Leo";   //注册窗口时候要的名字，作为参数   
	wndclass.lpszMenuName = 0;        //菜单名字
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hInstance = hInstance;

	//注册窗口

	if (RegisterClassEx(&wndclass) == false)
	{
		MessageBox(NULL, "注册失败", "提示", MB_OK);
		return 0;
	}
	//创建
	HWND hWnd = ::CreateWindow("Leo", "Small Test", WS_OVERLAPPEDWINDOW, 0, 200, 500, 500, NULL, NULL, hInstance, NULL);


	//显示窗口

	ShowWindow(hWnd, nCmdShow);

	//消息循环
	MSG msg;
	while (::GetMessage(&msg, 0, 0, 0))
	{

		::TranslateMessage(&msg);   //将得到的消息翻译
		::DispatchMessage(&msg);    //翻译来的消息发送

	}

	return 0;
}