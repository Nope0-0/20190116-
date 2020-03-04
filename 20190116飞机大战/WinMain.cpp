#include<windows.h>
#include"GameApp.h"
#include<time.h>
// HINSTANCE ʵ�����           ����һ���ⲿ����Դ��Ҫ��
// HWND      ������           �ʹ�����صĲ���
// HDC       �����豸���       ��ͼ�Ĳ���

// Window Message
// WM_LBUTTONDOWN
// WM_KEYDOWN
// WM_PAINT
// WM_TIMER
// ........

LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam);

HINSTANCE g_hIns;
int GetWindowWidth();
int GetWindowHeight();

int CALLBACK WinMain(HINSTANCE hInstance,HINSTANCE hPreInstance,LPSTR pCmdLine,int nCmdShow)
{
	g_hIns = hInstance;
	srand((unsigned int )time(NULL));
	//  1. ���
	WNDCLASSEX wndclass;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wndclass.hCursor = ::LoadCursor(0,MAKEINTRESOURCE(IDC_ARROW));
	wndclass.hIcon = 0;
	wndclass.hIconSm = 0;
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = "��Ϸ";
	wndclass.lpszMenuName = 0;
	wndclass.style = CS_VREDRAW|CS_HREDRAW;
	//  2. ע��
	if( ::RegisterClassEx(&wndclass)==FALSE)
	{
		::MessageBox(0,"ע��ʧ��","��ʾ",MB_OK);
		return 0;
	}
	//  3. ����
	HWND hwnd = ::CreateWindow("��Ϸ","O(��_��)O����~",WS_OVERLAPPEDWINDOW,0,0,GetWindowWidth()+ 16/*500*//*380+16*/ ,GetWindowHeight()+38/*500*//*550+38*/,0,0,hInstance,0); // 16 38 ���ڱ߿�
	if(hwnd == 0)
	{
		::MessageBox(0,"����ʧ��","��ʾ",MB_OK);
		return 0;		
	}
	//  4. ��ʾ
	::ShowWindow(hwnd,SW_SHOW);
	//  5. ��Ϣѭ��
	MSG msg;
	while(::GetMessage(&msg,0,0,0))
	{
		//  ����
		::TranslateMessage(&msg);
		//  �ַ�
		::DispatchMessage(&msg);
	}

	return 0;
}
CGameApp * g_pApp = 0;
CGameApp * CreateObject();

//  ��Ϣ�Ĵ�����
LRESULT CALLBACK WndProc(HWND hwnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CREATE:
		//g_pApp = new ������� ?;
		//g_pApp = new CSnakeApp;
		g_pApp = CreateObject();
		if( g_pApp )
		{
			g_pApp->SetHandle(g_hIns,hwnd);
			g_pApp->onGameCreate();
		}
		break;
	case WM_PAINT:
		if( g_pApp )
			g_pApp->onGameDraw();
		break;
	case WM_TIMER:
		if( g_pApp )
			g_pApp->onGameRun(wParam);
		break;
	case WM_KEYDOWN:
		if( g_pApp )
			g_pApp->onKeyDown(wParam);
		break;
	case WM_KEYUP:
		if( g_pApp )
			g_pApp->onKeyUp(wParam);
		break;
	case WM_LBUTTONDOWN:
		if( g_pApp )
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			g_pApp->onLButtonDown(point);
		}
		break;
	case WM_LBUTTONUP:
		if( g_pApp )
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			g_pApp->onLButtonUp(point);
		}

		break;
	case WM_MOUSEMOVE:
		if( g_pApp )
		{
			POINT point;
			point.x = LOWORD(lParam);
			point.y = HIWORD(lParam);
			g_pApp->onMouseMove(point);
		}
		break;
	case WM_CLOSE:
		delete g_pApp;
		::PostQuitMessage(0);
		break;
	}
	return ::DefWindowProc( hwnd, uMsg, wParam, lParam);
}