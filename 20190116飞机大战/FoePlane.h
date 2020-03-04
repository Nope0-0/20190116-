#pragma once
#include"sys.h"
#include"Player.h"
#include"Gunner.h"
#include"ToolBase.h"
#include"toolstar.h"
#include"toolBoom.h"
class CFoePlane
{
public:
	HBITMAP		m_hBmpFoePlane	;
	int			m_nBlood			;
	int			m_nShowID		;
	int			m_nX				;
	int			m_nY				;
public:
	CFoePlane(void);
	virtual ~CFoePlane(void);

	bool IsBoom()
	{
		if( m_nBlood == 0 ) return true;
		return false;
	}
	void BloodDown()
	{
		--m_nBlood;
	}
	virtual CToolBase* ToolCreate(HINSTANCE hIns)
	{
		CToolBase* pTool = 0;
		int nRand =0;
		nRand = rand()%10 ; 
		if( nRand >=0 && nRand<=2 )
			pTool = new CToolStar;
		if( nRand >=3 && nRand<=5 )
			pTool = new CToolBoom;
		if( pTool)
			 pTool->ToolInit(hIns, m_nX , m_nY);
		return pTool;
	}
	virtual bool IsHitByGunner(CGunner *pGunner)	= 0 ;
	virtual bool IsHitPlayer(CPlayer & Player)		= 0 ;
	virtual void FoePlaneInit(HINSTANCE hIns)		= 0 ;
	virtual void FoePlaneMove()					= 0 ;
	virtual void FoePlaneShow(HDC hMenDC)			= 0 ;
};

