#pragma once
#include "foeplane.h"
class CFoePlaneMid :
	public CFoePlane
{
public:
	CFoePlaneMid(void);
	~CFoePlaneMid(void);

	bool IsHitByGunner(CGunner *pGunner);
	bool IsHitPlayer(CPlayer & Player)	;
	void FoePlaneInit(HINSTANCE hIns)	;
	void FoePlaneMove()				;
	void FoePlaneShow(HDC hMenDC)		; 
};

