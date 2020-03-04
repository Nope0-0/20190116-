#include "FoePlaneSmall.h"

//С�ɻ��ĳߴ� : 34 * 28
CFoePlaneSmall::CFoePlaneSmall(void)
{
	m_hBmpFoePlane	= 0 ;
	m_nBlood			= 1 ;
	m_nShowID		= 1 ;
	m_nX				= rand()%( 380 - 34 ) ;
	m_nY				= -28 ;
}


CFoePlaneSmall::~CFoePlaneSmall(void)
{
	::DeleteObject(m_hBmpFoePlane);
}


bool CFoePlaneSmall::IsHitByGunner(CGunner *pGunner)
{
	if( pGunner->m_nX >= m_nX && pGunner->m_nX +6 <= m_nX + 34 
	&& pGunner->m_nY >= m_nY && pGunner->m_nY + 9 <= m_nY + 28 )
		return true; 
	return false;
}
bool CFoePlaneSmall::IsHitPlayer(CPlayer & Player)	
{
	//( x + 30 , y +30 ) (x+30 , y) ( x, Y+50) (x+60, y+50)
	int x = 0, y = 0 ;
	x= Player.m_nX + 30 ; y = Player.m_nY + 30;
	if(  x > this->m_nX && x < this->m_nX + 34 
		&& y > this->m_nY && y < this->m_nY + 28 )
		return true;

	x= Player.m_nX + 30 ; y = Player.m_nY ;
	if(  x > this->m_nX && x < this->m_nX + 34 
		&& y > this->m_nY && y < this->m_nY + 28 )
		return true;

	x= Player.m_nX ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 34 
		&& y > this->m_nY && y < this->m_nY + 28 )
		return true;

	x= Player.m_nX +60 ; y = Player.m_nY +50 ;
	if(  x > this->m_nX && x < this->m_nX + 34 
		&& y > this->m_nY && y < this->m_nY + 28 )
		return true;

	return false;
}
void CFoePlaneSmall::FoePlaneInit(HINSTANCE hIns)	
{
	m_hBmpFoePlane = ::LoadBitmap(hIns,MAKEINTRESOURCE(IDB_BMP_SMALL));
}
void CFoePlaneSmall::FoePlaneMove()				
{
	//��һְ�� ֻ�����ƶ� ������ �������� , ����������λ��Box����
	m_nY += 3;
}
void CFoePlaneSmall::FoePlaneShow(HDC hMenDC)		
{
	//1. ����Ŀ��DC�ļ���DC   hdc
	HDC hdc = ::CreateCompatibleDC(hMenDC); 
	//2. ��λͼ��������DC
	::SelectObject(hdc,m_hBmpFoePlane);
	//3. ������DC�����λͼ����Ŀ��DC  ȥ��ͼƬ������ɫ  SRCAND
	::BitBlt(hMenDC,m_nX,m_nY,34, 28,hdc,0, (1 - m_nShowID)*28,/*SRCCOPY*/ SRCAND );//Ŀ��DC , �ڽ����ʲôλ����, �����, ���ĸ�DC����(����DC) , ��ͼƬ��ʲôλ�ÿ�ʼ��(ѡȡ������) ,��ô��
	// ������Դ
	::DeleteDC(hdc);
}