#pragma once
#include<windows.h>

//参数的确定
//子类对象的问题
#define CREATE(THISCLASS)\
CGameApp * CreateObject()\
{\
	return new THISCLASS;\
}

#define WINDOW_HEIGHT( a )\
int GetWindowHeight()\
{\
	int nVal = (a);\
	return nVal;\
}

#define WINDOW_WIDTH( a )\
int GetWindowWidth()\
{\
	int nVal = (a);\
	return nVal;\
}

class CGameApp
{
public:
	HINSTANCE	m_hIns		;
	HWND			m_hMainWnd	;
public:
	CGameApp()
	{
		m_hIns		=	0 ;
		m_hMainWnd	=	0 ;
	}
	virtual ~CGameApp(){}
	void SetHandle(HINSTANCE	hIns,HWND  hMainWnd)
	{
		m_hIns		= hIns	;
		m_hMainWnd	= hMainWnd;
	}

	virtual void onGameCreate(){} //游戏创建,包含初始化,加载位图 :实例句柄 HINSTANCE
	virtual void onGameDraw(){} //绘图HDC GetDC() 传入窗口句柄: 窗口句柄
	virtual void onGameRun( WPARAM nTimerID){} //定时器, 哪个定时器
	virtual void onKeyDown(WPARAM nKey){} //按下按键, 按哪个键
	virtual void onKeyUp(WPARAM nKey){} // 按键抬起,哪个键
	virtual void onLButtonDown( POINT point){}// 鼠标左键按下 , 参数一个坐标
	virtual void onLButtonUp(POINT point){}//鼠标左键抬起 , 参数一个坐标
	virtual void onMouseMove(POINT point){}//鼠标移动 , 参数一个坐标
};