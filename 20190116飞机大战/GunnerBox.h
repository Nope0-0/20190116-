#pragma once
#include"sys.h"
#include"Gunner.h"
class CGunnerBox
{
public:
	list<CGunner * > m_lstGunner;
public:
	CGunnerBox(void);
	~CGunnerBox(void);

	void AllGunnerMove();
	void AllGunnerShow(HDC hMenDC);
};

