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
	{ "��Ϊο�ʷѶ���" },
	{ "�����Ѷ��ҷ淶" },
	{ "΢�ֶ��ҷ����Ƕ��� ���ҷ�" },
	{ "EWFE ��ά��Ϊ�Ƕ��ҷ����ҷ� wef	FWE" }
};

//string a::sysmetrics = { "avewfew", "wefwefwef", "wefwefewf" };


//LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);//�ص���������
LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance,
				   HINSTANCE hPrevInstance,
				   PSTR szCmdLine,
				   int iCmdShow)//WinMain��ں���
{
	

	//static TCHAR szAPPName[]=TEXT("HelloWin");
	HWND hwnd;//���ھ��
	MSG msg;//��Ϣ�ṹ��
	WNDCLASS wndclass={};//������
	//�������Ա������ֵ
	wndclass.style 			=CS_HREDRAW |CS_VREDRAW;//��������ˮƽ�ػ�����ֱ�ػ�
	wndclass.lpfnWndProc	=WndProc;//���ڹ��̺���
	wndclass.cbClsExtra		=0;//
	wndclass.cbWndExtra		=0;
	wndclass.hInstance 		=hInstance;//����ʵ�����
	wndclass.hIcon			=LoadIcon(NULL,IDI_APPLICATION);//���ش���ͼ��
	wndclass.hCursor		=LoadCursor(NULL,IDC_ARROW);//���ش��ڹ��
	wndclass.hbrBackground	=(HBRUSH)GetStockObject(LTGRAY_BRUSH);//���ڻ�ˢ���� WHITE_BRUSH ��ɫ
	wndclass.lpszMenuName	=NULL;//�˵�����
	wndclass.lpszClassName	="wef";//��������
	//ע�ᴰ����
	if(!RegisterClass(&wndclass))
	{
		//MessageBox(NULL,TEXT("This program requires Windows NT!"),szAPPName,MB_ICONERROR);//��ע��ʧ�ܣ��򵯳���Ϣ�Ի���
		return 0;
	}
	//��������
	hwnd=CreateWindow(	"wef",
						"The Hello Program",
						WS_OVERLAPPEDWINDOW,
						500,//x
						220,//y
						1000,//��
						700,//��
						NULL,
						NULL,
						hInstance,
						NULL
					);
	//��ʾ����
	ShowWindow(hwnd,iCmdShow);//WinMain���ݸ�iCmdShow��ΪSW_SHOWNORMAL
	UpdateWindow(hwnd);//���´��ڻ����ػ�����,ͨ������WM_PAINT��Ϣ
	//ѭ����ȡ��Ϣ����
	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);//���������Ϣ
		DispatchMessage(&msg);//������Ϣ
	}
	return msg.wParam;
}
//���ڹ��̺���
LRESULT CALLBACK WndProc(HWND hwnd,UINT message,WPARAM wParam,LPARAM lParam)
{
	
	HDC hdc;//�豸���
	PAINTSTRUCT ps;//PAINT�ṹ��
	RECT rect;//RECT�ṹ��
	TEXTMETRIC tm;
	static int cxchar, cychar;
	static int cxClient, cyClient;
	switch (message)//�ж���Ϣ����
	{
		case WM_CREATE://����������Ϣ
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
			 MessageBox(NULL, "��������", "����demo", 0);
			 return 0;*/

		/*case MM_TEXT:
			TEXTMETRIC tm;
			hdc = GetDC(hwnd);
			GetTextMetrics(hdc, &tm);
			
			ReleaseDC(hwnd, hdc);
			return 0;
*/
		case WM_PAINT://PAINT��Ϣ
		{
			//TCHAR szbuffer[40];
			//TextOut(hdc, 0, 0, szbuffer, wsprintf(szbuffer, TEXT("AAAAAAAAA")));
			//CONST CHAR* psTex = "������֪�������Ҹ���Ϊ����·��ͨ��һ�������Ʊ�׾��Ŭ�������ܽ᲻�Ϲ��ɡ�";

			//InvalidateRect(hwnd, NULL, TRUE);
			hdc=BeginPaint(hwnd,&ps);//��ʼPAINT

			

			TCHAR szbuffer[40];
			for (int i = 0; i < size(aa); ++i)
			{
				TextOut(hdc, cxchar, cychar*i+3, aa[i].szLabel,lstrlen(aa[i].szLabel));
			}
			


			
			//TextOut(hdc, 100, 100, psTex, lstrlen(psTex));

			//GetClientRect(hwnd,&rect);//��ÿͻ�����
			//DrawText(hdc,TEXT("Hello,Windows 98!"),-1,&rect,
			//	DT_SINGLELINE|DT_CENTER|DT_VCENTER);//�����ַ���
			EndPaint(hwnd,&ps);//��������
			return 0;
		}
		case WM_DESTROY://������Ϣ
			PostQuitMessage(0);//��������Ϣ������Ϣ����
			return 0;

		default:
			return DefWindowProc(hwnd, message, wParam, lParam);//����ȱʡ�Ĵ��ڹ��̺���
	}
}