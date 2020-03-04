#pragma once
#include<windows.h>

//������ȷ��
//������������
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

	virtual void onGameCreate(){} //��Ϸ����,������ʼ��,����λͼ :ʵ����� HINSTANCE
	virtual void onGameDraw(){} //��ͼHDC GetDC() ���봰�ھ��: ���ھ��
	virtual void onGameRun( WPARAM nTimerID){} //��ʱ��, �ĸ���ʱ��
	virtual void onKeyDown(WPARAM nKey){} //���°���, ���ĸ���
	virtual void onKeyUp(WPARAM nKey){} // ����̧��,�ĸ���
	virtual void onLButtonDown( POINT point){}// ���������� , ����һ������
	virtual void onLButtonUp(POINT point){}//������̧�� , ����һ������
	virtual void onMouseMove(POINT point){}//����ƶ� , ����һ������
};