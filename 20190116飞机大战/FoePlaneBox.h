#pragma once
#include"sys.h"
#include"FoePlane.h"
class CFoePlaneBox
{
public:
	list<CFoePlane*>  m_lstFoePlane;
public:
	CFoePlaneBox(void);
	~CFoePlaneBox(void);

	void AllFoePlaneMove();
	void AllFoePlaneShow(HDC hMenDC);
	void FoePlaneCreate(HINSTANCE hIns);
};

