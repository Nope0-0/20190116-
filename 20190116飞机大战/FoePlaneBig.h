#pragma once
#include "foeplane.h"
class CFoePlaneBig :
	public CFoePlane
{
public:
	CFoePlaneBig(void);
	~CFoePlaneBig(void);

	bool IsHitByGunner(CGunner *pGunner);
	bool IsHitPlayer(CPlayer & Player)	;
	void FoePlaneInit(HINSTANCE hIns)	;
	void FoePlaneMove()				;
	void FoePlaneShow(HDC hMenDC)		; 
};

