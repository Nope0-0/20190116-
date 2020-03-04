#pragma once
#include "foeplane.h"
class CFoePlaneSmall :
	public CFoePlane
{
public:
	CFoePlaneSmall(void);
	~CFoePlaneSmall(void);

	bool IsHitByGunner(CGunner *pGunner);
	bool IsHitPlayer(CPlayer & Player)	;
	void FoePlaneInit(HINSTANCE hIns)	;
	void FoePlaneMove()				;
	void FoePlaneShow(HDC hMenDC)		; 
};

