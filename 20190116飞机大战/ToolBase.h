#pragma once
#include"sys.h"
class CToolBase
{
public:
	HBITMAP		m_hBmpTool	;
	int			m_nX		;
	int			m_nY		;
	int			m_nHFX		; // 0向左 1向右
	int			m_nVFX		; // 0向上 1向下
	int			m_nStyle	;
public:
	CToolBase(void);
	virtual ~CToolBase(void);

	virtual void ToolShow(HDC hMenDC)	  = 0;
	virtual void ToolInit(HINSTANCE hIns , int x, int y) = 0;
	virtual void ToolMove()
	{
		if( m_nX >= 380 -/*48*/32 ) m_nHFX = 0 ;
		if( m_nX <= 0 ) m_nHFX = 1 ;
		if( m_nY >= 550 -/*48*/32 ) m_nVFX = 0;
		if( m_nY <= 0 ) m_nVFX = 1;
		if( m_nHFX ) m_nX ++;
		else  m_nX --;
		if( m_nVFX ) m_nY ++;
		else m_nY--;
	}
	
};

