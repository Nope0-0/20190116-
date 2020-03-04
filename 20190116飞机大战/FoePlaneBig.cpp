#include "FoePlaneBig.h"

//大飞机的尺寸 : 108 * 128
CFoePlaneBig::CFoePlaneBig(void)
{
	m_hBmpFoePlane	= 0 ;
	m_nBlood			= 5 ;
	m_nShowID		= 3 ;
	m_nX				= rand()%( 380 - 108 ) ;
	m_nY				= -128 ;
}


CFoePlaneBig::~CFoePlaneBig(void)
{
	::DeleteObject(m_hBmpFoePlane);
}

//判断子弹是否撞到敌人
bool CFoePlaneBig::IsHitByGunner(CGunner *pGunner)
{
	if( pGunner->m_nX >= m_nX && pGunner->m_nX +6 <= m_nX + 108 
		&& pGunner->m_nY >= m_nY && pGunner->m_nY + 9 <= m_nY + 128 )
		return true; 
	return false;
}
bool CFoePlaneBig::IsHitPlayer(CPlayer & Player)	
{
	//( x + 30 , y +30 ) (x+30 , y) ( x, Y+50) (x+60, y+50)
	int x = 0, y = 0 ;
	x= Player.m_nX + 30 ; y = Player.m_nY + 30;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	x= Player.m_nX + 30 ; y = Player.m_nY ;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	x= Player.m_nX ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	x= Player.m_nX +60 ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 108 
		&& y > this->m_nY && y < this->m_nY + 128 )
		return true;

	return false;
}
void CFoePlaneBig::FoePlaneInit(HINSTANCE hIns)	
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_BIG));
}
void CFoePlaneBig::FoePlaneMove()				
{
	//单一职责 只考虑移动 不考虑 出界问题 , 出界由其他位置Box管理
	m_nY += 1;
}
void CFoePlaneBig::FoePlaneShow(HDC hMenDC)		
{
	//1. 创建目标DC的兼容DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. 将位图传到兼容DC
	::SelectObject(hdc,m_hBmpFoePlane);
	//3. 将兼容DC里面的位图传到目标DC  去除图片背景颜色  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY,108, 128,hdc,0, (3 - m_nShowID)*128,/*SRCCOPY*/ SRCAND );//目标DC , 在界面的什么位置贴, 贴多大, 从哪个DC来的(兼容DC) , 从图片的什么位置开始贴(选取部分贴) ,怎么贴
	// 回收资源
	::DeleteDC(hdc);
}