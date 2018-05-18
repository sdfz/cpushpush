#include <windows.h>
#include<iostream>
#include<cstdio>
#include<string>
#include<cstdlib>
#include<algorithm>
#include<math.h>

#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
using namespace std;

//2018-5-18


#define SB_LINEUP			0
//#define SB_LINELEFT		0
#define SB_LINEDOWN			1
//#define SB_LINERIGHT		1
#define SB_PAGEUP			2
//#define SB_PAGELEFT		2
#define SB_PAGEDOWN			3
//#define SB_PAGERIGHT		3
#define SB_THUMBPOSITION	4
#define SB_THUMBTRACK		5
//#define SB_TOP			6
//#define SB_LEFT			6
//#define SB_BOTTOM			7
//#define SB_RIGHT			7
//#define SB_ENDSCROLL		8

#define NUMLINES ((int) (sizeof aa / sizeof aa [0]))
#define LOWORD1() ((WORD)(1))
#define HIWORD1() ((WORD)(((DWORD)(1) >> 16)& 0xFFFF))

#define NUM    1000
#define TWOPI (2*3.14159)  



//测试是否同步发GV发
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
	WNDCLASS wndclass = {};//窗口类
						   //窗口类成员变量赋值
	wndclass.style = CS_HREDRAW | CS_VREDRAW;//窗口类型水平重画和竖直重画
	wndclass.lpfnWndProc = WndProc;//窗口过程函数
	wndclass.cbClsExtra = 0;//
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;//窗口实例句柄
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//加载窗口图标
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);//加载窗口光标
	wndclass.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);//窗口画刷背景 WHITE_BRUSH 白色
	wndclass.lpszMenuName = NULL;//菜单名字
	wndclass.lpszClassName = "wef";//窗口名称
								   //注册窗口类
	if (!RegisterClass(&wndclass))
	{
		//MessageBox(NULL,TEXT("This program requires Windows NT!"),szAPPName,MB_ICONERROR);//若注册失败，则弹出消息对话框
		return 0;
	}
	//创建窗口
	hwnd = CreateWindow("wef",
		"The Hello Program",
		WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,//WS_VSCROLL
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
	ShowWindow(hwnd, iCmdShow);//WinMain传递给iCmdShow的为SW_SHOWNORMAL
	UpdateWindow(hwnd);//更新窗口或者重画窗口,通过调用WM_PAINT消息
					   //循环获取消息队列
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);//翻译键盘消息
		DispatchMessage(&msg);//发送消息
	}
	return msg.wParam;
}
//窗口过程函数
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	HDC hdc;//设备句柄
	PAINTSTRUCT ps;//PAINT结构体
	RECT rect;//RECT结构体
	TEXTMETRIC tm;
	SCROLLINFO si;
	RECT rt;
	int i;
	POINT apt[NUM];
	static int cxchar, cychar, cxClient, cyClient, iVscrollPos, nMaxWidth;
	int nVertPos, nHorzPos;
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


		SetScrollRange(hwnd, SB_VERT, 0, NUMLINES - 1, FALSE); // 初始化滚条范围，但不要重绘滚条  
		SetScrollPos(hwnd, SB_VERT, iVscrollPos, TRUE); // 等到接下来初始化滚条位置时再重绘滚条以避免不必要的多次重绘  、


														/*si.cbSize = sizeof(si);
														SetScrollInfo(hwnd, iBar, &si, bRedraw);
														GetScrollInfo(hwnd, iBar, &si);*/
		return 0;


	case WM_SIZE:
	{
		// save the width and height of window when changed the size of window  
		cxClient = LOWORD(lParam); // the width  
		cyClient = HIWORD(lParam); // the height  
							   // set vertical scroll bar range and page size  
		si.cbSize = sizeof(SCROLLBARINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = NUMLINES - 1;
		si.nPage = cyClient / cychar;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		// set horizontal scroll bar and page size  
		si.cbSize = sizeof(SCROLLBARINFO);
		si.fMask = SIF_RANGE | SIF_PAGE;
		si.nMin = 0;
		si.nMax = 2 + nMaxWidth / cxchar;
		si.nPage = cxClient / cxchar;
		SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		return 0;
	}
	case WM_VSCROLL:
	{
		// get all vertical scroll bar information  
		si.cbSize = sizeof(SCROLLINFO);
		si.fMask = SIF_ALL;
		::GetScrollInfo(hwnd, SB_VERT, &si);
		// save the position for comparison later on  
		nVertPos = si.nPos;
		switch (LOWORD1(wp))
		{
		case SB_LINEUP:
		{
			si.nPos -= 1;// the height decrease 1 unit  
			break;
		}
		case SB_LINEDOWN:
		{
			si.nPos += 1;// the height increase 1 unit  
			break;
		}
		case SB_PAGEUP:
		{
			// back to prev page, the cyClient/cyChar is the number of row in one page  
			si.nPos -= cyClient / cychar;
			break;
		}
		case SB_PAGEDOWN:
		{
			// back to next page  
			si.nPos += cyClient / cychar;
			break;
		}
		case SB_THUMBPOSITION:
		{
			si.nPos = HIWORD1(wp);
			break;
		}
		default:
			break;
		}
		// set the position and then retrieve it.Due to adjustments  
		// by Windows it may not be the same as the value set.  
		si.fMask = SIF_POS;
		SetScrollInfo(hwnd, SB_VERT, &si, TRUE);
		GetScrollInfo(hwnd, SB_VERT, &si);
		//if the position has changed,scroll the window update it  
		if (si.nPos != nVertPos)
		{
			::ScrollWindow(hwnd, 0, cychar*(nVertPos - si.nPos), NULL, NULL);
			::UpdateWindow(hwnd);
		}
		return 0;
	}
	case WM_HSCROLL:
	{
		// get all the vertical scroll bar information  
		si.cbSize = sizeof(si);
		si.fMask = SIF_ALL;
		// save the position for comparison later on  
		::GetScrollInfo(hwnd, SB_HORZ, &si);
		nHorzPos = si.nPos;
		switch (LOWORD1(wp))
		{
		case SB_LINELEFT:
		{
			si.nPos -= 1;
			break;
		}
		case SB_LINERIGHT:
		{
			si.nPos += 1;
			break;
		}
		case SB_PAGELEFT:
		{
			si.nPos -= si.nPage;
			break;
		}
		case SB_PAGERIGHT:
		{
			si.nPos += si.nPage;
			break;
		}
		case SB_THUMBPOSITION:
		{
			si.nPos = si.nTrackPos;
			break;
		}
		default:
			break;
		}
		// set the position and then retrieve it.due to adjustments  
		// by windows it may not be the same as the value set  
		si.fMask = SIF_POS;
		::SetScrollInfo(hwnd, SB_HORZ, &si, TRUE);
		::GetScrollInfo(hwnd, SB_HORZ, &si);
		// if the postion has changed ,scroll the window  
		if (si.nPos != nHorzPos)
		{
			::ScrollWindow(hwnd, cxchar*(nHorzPos - si.nPos), 0, NULL, NULL);
		}
		return 0;
	}

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
		hdc=BeginPaint(hwnd,&ps);//开始PAINT
		TextOut(hdc, 100, 100, TEXT("wefEgggggggggggggggggWFEW"), 8);

	
		TCHAR szbuffer[40];
		for (int i = 0; i < size(aa); ++i)
		{
			TextOut(hdc, cxchar, cychar*i + 3, aa[i].szLabel, lstrlen(aa[i].szLabel));
		}


		

		MoveToEx(hdc, 0,cyClient / 2, NULL);   
		LineTo(hdc, cxClient, cyClient/2);

		for (i = 0; i <NUM; i++)
		{
			apt[i].x = i * cxClient / NUM;
			//apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI*i / NUM)));
			apt[i].y = (int)(cyClient / 2 * (1 - sin(TWOPI*i / NUM)));
		}

		HPEN hpen1, hpen2, hpen3;
		hpen1 = CreatePen(PS_SOLID, 1, 0);
		hpen2=CreatePen(PS_SOLID, 3, RGB(255, 18, 18));
		hpen3 = CreatePen(PS_DOT, 0, 0);


		SetBkColor(hdc, RGB(123,45,12));
		
		HBRUSH hBrush;
		//hBrush = (HBRUSH)GetStockObject(DKGRAY_BRUSH);
		hBrush = CreateSolidBrush(HS_DIAGCROSS);
		SelectObject(hdc, hBrush);
		//SelectObject(hdc, GetStockObject(NULL_PEN));
		
		//SelectObject(hdc, GetStockObject(NULL_BRUSH));
		RoundRect(hdc, 50, 50, 200, 200, 30, 30);


		SelectObject(hdc, hpen2);

		Polyline(hdc, apt, NUM);
		EndPaint(hwnd, &ps);
		                          

		//TextOut(hdc, 100, 100, psTex, lstrlen(psTex));

		//GetClientRect(hwnd,&rect);//获得客户区域
		//DrawText(hdc,TEXT("Hello,Windows 98!"),-1,&rect,
		//	DT_SINGLELINE|DT_CENTER|DT_VCENTER);//绘制字符串
		//EndPaint(hwnd, &ps);//结束绘制
		return 0;
	}
	case WM_DESTROY://销毁消息
		PostQuitMessage(0);//将结束消息加入消息队列
		return 0;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);//返回缺省的窗口过程函数
	}
}