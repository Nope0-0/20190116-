#pragma once
#include"sys.h"
class CBack
{
public:
	HBITMAP		m_hBmpBackDown	;
	HBITMAP		m_hBmpBackUp		;
	int			m_nX				;
	int			m_nY				;
public:
	CBack(void);
	~CBack(void);

	void BackInit(HINSTANCE hIns);
	void BackMove();
	void BackShow(HDC hMenDC);
};

