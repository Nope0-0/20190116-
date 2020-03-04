#include "FoePlaneMid.h"

//�зɻ��ĳߴ� : 70 * 90
CFoePlaneMid::CFoePlaneMid(void)
{
	m_hBmpFoePlane	= 0 ;
	m_nBlood			= 3 ;
	m_nShowID		= 2 ;
	m_nX				= rand()%( 380 - 70 ) ;
	m_nY				= -90 ;
}


CFoePlaneMid::~CFoePlaneMid(void)
{
	::DeleteObject(m_hBmpFoePlane);
}


bool CFoePlaneMid::IsHitByGunner(CGunner *pGunner)
{
	if( pGunner->m_nX >= m_nX && pGunner->m_nX +6 <= m_nX + 70 
	&& pGunner->m_nY >= m_nY && pGunner->m_nY + 9 <= m_nY + 90 )
		return true; 
	return false;
}
bool CFoePlaneMid::IsHitPlayer(CPlayer & Player)	
{
	//( x + 30 , y +30 ) (x+30 , y) ( x, Y+50) (x+60, y+50)
	int x = 0, y = 0 ;
	x= Player.m_nX + 30 ; y = Player.m_nY + 30;
	if(  x > this->m_nX && x < this->m_nX + 70 
		&& y > this->m_nY && y < this->m_nY + 90 )
		return true;

	x= Player.m_nX + 30 ; y = Player.m_nY ;
	if(  x > this->m_nX && x < this->m_nX + 70 
		&& y > this->m_nY && y < this->m_nY + 90 )
		return true;

	x= Player.m_nX ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 70 
		&& y > this->m_nY && y < this->m_nY + 90 )
		return true;

	x= Player.m_nX +60 ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 70 
		&& y > this->m_nY && y < this->m_nY + 90 )
		return true;

	return false;
}
void CFoePlaneMid::FoePlaneInit(HINSTANCE hIns)	
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_MID));
}
void CFoePlaneMid::FoePlaneMove()				
{
	//��һְ�� ֻ�����ƶ� ������ �������� , ����������λ��Box����
	m_nY += 2;
}
void CFoePlaneMid::FoePlaneShow(HDC hMenDC)		
{
	//1. ����Ŀ��DC�ļ���DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. ��λͼ��������DC
	::SelectObject(hdc,m_hBmpFoePlane);
	//3. ������DC�����λͼ����Ŀ��DC  ȥ��ͼƬ������ɫ  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY,70, 90,hdc,0, (2 - m_nShowID)*90,/*SRCCOPY*/ SRCAND );//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��
	// ������Դ
	::DeleteDC(hdc);
}