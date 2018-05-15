#include<windows.h>

//   HINSTANCE  ʵ���ľ��.  ������Դ��Ҫ�õ�HINSTANCE
//   HWND       ���ھ��     �ʹ�����صĲ���
//   HDC        �豸���     ��ͼ�Ĳ���
LRESULT CALLBACK MyWinMain(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)//�ص���������Ϣ�ģ�
{
	switch (uMsg)
	{
	case WM_CLOSE:          //�Զ��˳�
	{
		::PostQuitMessage(0);
	}
	break;
	}

	return  DefWindowProc(hWnd, uMsg, wParam, lParam); //������Ϣ��Ĭ�ϴ���
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//���û�ˢ
	HBRUSH hBrush = ::CreateSolidBrush(RGB(62, 71, 98));

	//��ƴ���
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = hBrush;
	wndclass.hCursor = 0;
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.lpfnWndProc = MyWinMain;
	wndclass.lpszClassName = "Leo";   //ע�ᴰ��ʱ��Ҫ�����֣���Ϊ����   
	wndclass.lpszMenuName = 0;        //�˵�����
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.hInstance = hInstance;

	//ע�ᴰ��

	if (RegisterClassEx(&wndclass) == false)
	{
		MessageBox(NULL, "ע��ʧ��", "��ʾ", MB_OK);
		return 0;
	}
	//����
	HWND hWnd = ::CreateWindow("Leo", "Small Test", WS_OVERLAPPEDWINDOW, 0, 200, 500, 500, NULL, NULL, hInstance, NULL);


	//��ʾ����

	ShowWindow(hWnd, nCmdShow);

	//��Ϣѭ��
	MSG msg;
	while (::GetMessage(&msg, 0, 0, 0))
	{

		::TranslateMessage(&msg);   //���õ�����Ϣ����
		::DispatchMessage(&msg);    //����������Ϣ����

	}

	return 0;
}