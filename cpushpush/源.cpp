#include <windows.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
using namespace std;

#define NUMLINES ((int) (sizeof aa / sizeof aa [0]))
#define LOWORD() ((WORD)(1))
#define HIWORD() ((WORD)(((DWORD)(1) >> 16)& 0xFFFF))


class sysmetrics
{
public:
	CONST TCHAR* szLabel;
};

sysmetrics aa[]
{
	{ "分为慰问费恩恩" },
	{ "王企鹅费而且锋范" },
	{ "微分而我方而非而非 而我方" },
	{ "EWFE 二维分为非而我方而我方 wef	FWE" }
};

//string a::sysmetrics = { "avewfew", "wefwefwef", "wefwefewf" };


//LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);//回调函数声明
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   PSTR szCmdLine,
				   int iCmdShow)//WinMain入口函数
{
	

	//static TCHAR szAPPName[]=TEXT("HelloWin");
	HWND hwnd;//窗口句柄
	MSG msg;//消息结构体
	WNDCLASS wndclass={};//窗口类
	//窗口类成员变量赋值
	wndclass.style 			=CS_HREDRAW |CS_VREDRAW;//窗口类型水平重画和竖直重画
	wndclass.lpfnWndProc	=WndProc;//窗口过程函数
	wndclass.cbClsExtra		=0;//
	wndclass.cbWndExtra		=0;
	wndclass.hInstance 		=hInstance;//窗口实例句柄
	wndclass.hIcon			=LoadIcon(NULL,IDI_APPLICATION);//加载窗口图标
	wndclass.hCursor		=LoadCursor(NULL,IDC_ARROW);//加载窗口光标
	wndclass.hbrBackground	=(HBRUSH)GetStockObject(LTGRAY_BRUSH);//窗口画刷背景 WHITE_BRUSH 白色
	wndclass.lpszMenuName	=NULL;//菜单名字
	wndclass.lpszClassName	="wef";//窗口名称
	//注册窗口类
	if(!RegisterClass(&wndclass))
	{
		//MessageBox(NULL,TEXT("This program requires Windows NT!"),szAPPName,MB_ICONERROR);//若注册失败，则弹出消息对话框
		return 0;
	}
	//创建窗口
	hwnd=CreateWindow(	"wef",
						"The Hello Program",
						WS_OVERLAPPEDWINDOW,
						500,//x
						220,//y
						1000,//宽
						700,//高
						NULL,
						NULL,
						hInstance,
						NULL
					);
	//显示窗口
	ShowWindow(hwnd,iCmdShow);//WinMain传递给iCmdShow的为SW_SHOWNORMAL
	UpdateWindow(hwnd);//更新窗口或者重画窗口,通过调用WM_PAINT消息
	//循环获取消息队列
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);//翻译键盘消息
		DispatchMessage(&msg);//发送消息
	}
	return msg.wParam;
}
//窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	
	HDC hdc;//设备句柄
	PAINTSTRUCT ps;//PAINT结构体
	RECT rect;//RECT结构体
	TEXTMETRIC tm;
	static int cxchar, cychar;
	static int cxClient, cyClient;
	switch (message)//判断消息类型
	{
		case WM_CREATE://创建窗口消息
			hdc = GetDC(hwnd);

			GetTextMetrics(hdc, &tm);
			cxchar = tm.tmAveCharWidth;
			cychar = tm.tmHeight + tm.tmExternalLeading;

			//TCHAR szbuffer[40];
			//TextOut(hdc, 0, 0, szbuffer, wsprintf(szbuffer, TEXT("AAAAAAAAA")));
			ReleaseDC(hwnd, hdc);

			return 0;
		case WM_SIZE:
			cxClient = LOWORD(lParam);
			cyClient = LOWORD(lParam);
			return 0;
		/*case WM_LBUTTONDOWN:
			 MessageBox(NULL, "测试内容", "标题demo", 0);
			 return 0;*/

		/*case MM_TEXT:
			TEXTMETRIC tm;
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			
			ReleaseDC(hwnd, hdc);
			return 0;
*/
		case WM_PAINT://PAINT消息
		{
			//TCHAR szbuffer[40];
			//TextOut(hdc, 0, 0, szbuffer, wsprintf(szbuffer, TEXT("AAAAAAAAA")));
			//CONST CHAR* psTex = "当你熟知。但是我更认为，套路是通过一步步看似笨拙的努力不断总结不断归纳。";

			//InvalidateRect(hwnd, NULL, TRUE);
			hdc=BeginPaint(hwnd,&ps);//开始PAINT

			

			TCHAR szbuffer[40];
			for (int i = 0; i < size(aa); ++i)
			{
				TextOut(hdc, cxchar, cychar*i+3, aa[i].szLabel,lstrlen(aa[i].szLabel));
			}
			


			
			//TextOut(hdc, 100, 100, psTex, lstrlen(psTex));

			//GetClientRect(hwnd,&rect);//获得客户区域
			//DrawText(hdc,TEXT("Hello,Windows 98!"),-1,&rect,
			//	DT_SINGLELINE|DT_CENTER|DT_VCENTER);//绘制字符串
			EndPaint(hwnd,&ps);//结束绘制
			return 0;
		}
		case WM_DESTROY://销毁消息
			PostQuitMessage(0);//将结束消息加入消息队列
			return 0;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);//返回缺省的窗口过程函数
	}
}