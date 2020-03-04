#include "Player.h"


CPlayer::CPlayer(void)
{
	m_hBmpPlayer		= 0 ;
	m_nX				= /*0*/ 380/2 - 60/2 ;
	m_nY				= /*0*/ 550 - 60 ;
	m_nGunnerStyle	= 0 ;
}


CPlayer::~CPlayer(void)
{
	::DeleteObject(m_hBmpPlayer);
}


void CPlayer::PlayerInit(HINSTANCE hIns)
{
	m_hBmpPlayer = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_PLAYER));
}
void CPlayer::PlayerMove(int nFX)
{
	// 考虑边界
	switch(nFX)
	{
	case VK_UP:
		if(m_nY >0)
			m_nY -= 2;
	break;
	case VK_DOWN:
		if(m_nY < 550 - 60 )
			m_nY += 2;
	break;
	case VK_LEFT:
		if( m_nX > 0 )
			m_nX -= 2;
	break;
	case VK_RIGHT:
		if( m_nX < 380 -60 )
			m_nX += 2;
	break;
	}
}
void CPlayer::PlayerShow(HDC hMenDC)
{
	
	//1. 创建目标DC的兼容DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. 将位图传到兼容DC
	::SelectObject(hdc,m_hBmpPlayer);
	//3. 将兼容DC里面的位图传到目标DC  去除图片背景颜色  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY,60, 60,hdc,0,0,/*SRCCOPY*/ SRCAND );//目标DC , 在界面的什么位置贴, 贴多大, 从哪个DC来的(兼容DC) , 从图片的什么位置开始贴(选取部分贴) ,怎么贴
	// 回收资源
	::DeleteDC(hdc);
}
//发射炮弹 1. new 炮弹对象 2. 炮弹初始化 3. 加到Box里管理
void CPlayer::PlayerSendGunner(HINSTANCE hIns, CGunnerBox & GunnerBox)
{
	if( m_nGunnerStyle == 0 )
	{
		CGunner * pGunner = new CGunner;
		if(pGunner)
		{
			pGunner->GunnerInit(hIns,m_nX+ 60/2 -6/2, m_nY);
			GunnerBox.m_lstGunner.push_back(pGunner);
		}
	}
	if( m_nGunnerStyle == 1)
	{
		CGunner * pGunner1 = new CGunner;
		CGunner * pGunner2 = new CGunner;
		
			pGunner1->GunnerInit(hIns,m_nX+ 60/3 -6/2, m_nY );
			GunnerBox.m_lstGunner.push_back(pGunner1);

			pGunner2->GunnerInit(hIns,m_nX+ 60*2/3 -6/2, m_nY );
			GunnerBox.m_lstGunner.push_back(pGunner2);
	}
	if( m_nGunnerStyle == 2)
	{
		CGunner * pGunner1 = new CGunner;
		CGunner * pGunner2 = new CGunner;
		CGunner * pGunner3 = new CGunner;
		
			pGunner1->GunnerInit(hIns,m_nX+ 60/4 -6/2, m_nY );
			GunnerBox.m_lstGunner.push_back(pGunner1);

			pGunner2->GunnerInit(hIns,m_nX+ 60*2/4 -6/2, m_nY );
			GunnerBox.m_lstGunner.push_back(pGunner2);

			pGunner3->GunnerInit(hIns,m_nX+ 60*3/4 -6/2, m_nY );
			GunnerBox.m_lstGunner.push_back(pGunner3);
	}
}

bool CPlayer::IsPlayerEatTool(CToolBase * pTool)
{
	if(!pTool) return false ;
	if( pTool-> m_nX+/*24*/16 >= m_nX  && pTool-> m_nX+/*24*/16 <= m_nX +60 
		&& pTool-> m_nY+/*24*/16 >= m_nY  && pTool-> m_nY+/*24*/16 <= m_nY +60  )
		return true;
	return false;
}