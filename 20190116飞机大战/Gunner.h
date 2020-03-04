#pragma once
#include"sys.h"
class CGunner
{
public:
	HBITMAP		m_hBmpGunner		;
	int			m_nX				;
	int			m_nY				;
public:
	CGunner(void);
	~CGunner(void);

	void GunnerInit(HINSTANCE hIns, int x, int y);
	void GunnerMove();
	void GunnerShow(HDC hMenDC);
};

