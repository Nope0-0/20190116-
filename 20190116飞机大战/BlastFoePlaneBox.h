#pragma once
#include"sys.h"
#include"FoePlane.h"
class CBlastFoePlaneBox
{
public:
	list<CFoePlane * > m_lstBlastPlane;
public:
	CBlastFoePlaneBox(void);
	~CBlastFoePlaneBox(void);

	void AllBlastPlaneShow(HDC hMenDC);
	void ChangeShowID();
};

