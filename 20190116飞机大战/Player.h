#pragma once
#include"sys.h"
#include"gunnerBox.h"
#include"toolBase.h"
class CPlayer
{
public:
	HBITMAP		m_hBmpPlayer	;
	int			m_nX			;
	int			m_nY			;
	int			m_nGunnerStyle;
public:
	CPlayer(void);
	~CPlayer(void);

	void PlayerInit(HINSTANCE hIns);
	void PlayerMove(int nFX);
	void PlayerShow(HDC hMenDC);

	bool IsPlayerEatTool(CToolBase * pTool);
	void ChangeGunnerStyle()
	{
		if( m_nGunnerStyle < 2 )
			m_nGunnerStyle++;
		else 
			m_nGunnerStyle = 0; 
	}
	//Íæ¼Ò·¢ÉäÅÚµ¯
	void PlayerSendGunner(HINSTANCE hIns, CGunnerBox & GunnerBox);
};

